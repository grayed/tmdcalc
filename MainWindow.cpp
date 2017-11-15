/*
 * Copyright (c) 2017 Artem Lipatov <artem.lipatov@mail.ru>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <cmath>
#include "MainWindow.h"
#include "ui_MainWindow.h"

extern "C"
{
  #include "lib/extern/vegas.h"
}

#include <QString>
#include <QDebug>
#include <QRunnable>
#include <QThread>

#include "gui/PDFsDialog.h"
#include "gui/ScopeDialog.h"
#include "open-beauty/open-beauty-OutputDialog.h"
#include "open-beauty/open-beauty-PhaseSpaceDialog.h"

#include "lib/common/SM.h"
#include "lib/common/utils.h"
#include "lib/tmdpdfs/tmdpdf.h"

tmdpdf A0;
extern double calcgg2bb(double x[], double wgt);
extern void saveOpenBeautyOutput(void);

using namespace std;


//class VegasRunner : public QThread {
class VegasRunner : public QObject {
  double *regn;
  int ndim;
  double (*fxn)(double [], double);
  int init;
  unsigned long ncall;
  int itmx;
  double *tgral;
  double *sd;
  double *chi2a;
  void(*callback)(unsigned int, void *);
  void *pointer;

  // QRunnable interface
public:
  VegasRunner(double regn[], int ndim, double (*fxn)(double [], double), int init,
              unsigned long ncall, int itmx, double *tgral, double *sd, double *chi2a,
              QObject *parent = NULL)
    : QObject(parent)
    , regn(regn)
    , ndim(ndim)
    , fxn(fxn)
    , init(init)
    , ncall(ncall)
    , itmx(itmx)
    , tgral(tgral)
    , sd(sd)
    , chi2a(chi2a)
  {

  }

public slots:
  void run() {
    vegas(regn, ndim, calcgg2bb, init, calls, itmx, tgral, sd, chi2a,
          updateIntegrationStatus, this);
  }

  void stop() {
    // TODO: добавить в vegas проверку флага (в виде переменной типа volatile int или volatile bool)
    // и тогда в этой функции его взводить.
  }

private:
  // callback-функция, периодически вызываемая из vegas()
  static void updateIntegrationStatus(unsigned int status, void *pointer)
  {
    VegasRunner *vr = (VegasRunner*)pointer;
    emit vr->progress(status);
  }

signals:
  void progress(int param);
};


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->TaskListWidget, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTaskListWidgetClicked(const QModelIndex &)));
  connect(ui->CollisionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onCollisionComboBoxCurrentIndexChanged(int)));
  connect(ui->FactorizationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onFactorizationComboBoxCurrentIndexChanged(int)));
  connect(ui->PDFsButton, SIGNAL(clicked()), this, SLOT(onPDFsButtonClicked()));
  connect(ui->ScopeSetupButton, SIGNAL(clicked()), this, SLOT(onScopeSetupButtonClicked()));
  connect(ui->PhaseSpaceSetupButton, SIGNAL(clicked()), this, SLOT(onPhaseSpaceSetupButtonClicked()));
  connect(ui->OutputSetupButton, SIGNAL(clicked()), this, SLOT(onOutputSetupButtonClicked()));
  connect(ui->StartButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));

  assist();
  setControlStatus();
  setStatusBarMessage();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::setControlStatus(void)
{
  switch (Factorization)
  {
    case TMD:  ui->FactorizationComboBox->setCurrentIndex(0);
               break;

    case COLL: ui->FactorizationComboBox->setCurrentIndex(1);
               break;
  }

  switch (Collision)
  {
    case pp:    ui->CollisionComboBox->setCurrentIndex(0);
                break;

    case ppbar: ui->CollisionComboBox->setCurrentIndex(1);
                break;
  }

  switch (TaskStatus)
  {
    case UnSpecified: ui->PDFsButton->setDisabled(true);
                      ui->ScopeSetupButton->setDisabled(true);
                      ui->PhaseSpaceSetupButton->setDisabled(true);
                      ui->OutputSetupButton->setDisabled(true);

                      ui->StartButton->setDisabled(true);
                      ui->PauseButton->setDisabled(true);
                      ui->CancelButton->setDisabled(true);
                      ui->SaveOutputButton->setDisabled(true);
                      ui->ClearOutputButton->setDisabled(true);

                      ui->SaveButton->setDisabled(true);
                      ui->LoadButton->setEnabled(true);
                      ui->CancelButton->setDisabled(true);
                      ui->SaveOutputButton->setDisabled(true);
                      ui->ClearOutputButton->setDisabled(true);

                      ui->FactorizationComboBox->setEnabled(true);
                      ui->CollisionComboBox->setEnabled(true);

                      ui->TaskListWidget->setEnabled(true);
                      break;

    case Specified:   ui->PDFsButton->setEnabled(true);
                      ui->ScopeSetupButton->setEnabled(true);
                      ui->PhaseSpaceSetupButton->setEnabled(true);
                      ui->OutputSetupButton->setEnabled(true);

                      ui->StartButton->setEnabled(true);
                      ui->PauseButton->setDisabled(true);
                      ui->CancelButton->setDisabled(true);
                      ui->SaveOutputButton->setDisabled(true);
                      ui->ClearOutputButton->setDisabled(true);

                      ui->SaveButton->setEnabled(true);
                      ui->LoadButton->setEnabled(true);

                      ui->FactorizationComboBox->setEnabled(true);
                      ui->CollisionComboBox->setEnabled(true);

                      ui->TaskListWidget->setEnabled(true);
                      break;

    case Running:     ui->PDFsButton->setDisabled(true);
                      ui->ScopeSetupButton->setDisabled(true);
                      ui->PhaseSpaceSetupButton->setDisabled(true);
                      ui->OutputSetupButton->setDisabled(true);

                      ui->StartButton->setDisabled(true);
                      ui->PauseButton->setEnabled(true);
                      ui->CancelButton->setEnabled(true);
                      ui->SaveOutputButton->setDisabled(true);
                      ui->ClearOutputButton->setDisabled(true);

                      ui->SaveButton->setDisabled(true);
                      ui->LoadButton->setDisabled(true);

                      ui->FactorizationComboBox->setDisabled(true);
                      ui->CollisionComboBox->setDisabled(true);

                      ui->TaskListWidget->setDisabled(true);
                      break;

    case Paused:      ui->PDFsButton->setDisabled(true);
                      ui->ScopeSetupButton->setDisabled(true);
                      ui->PhaseSpaceSetupButton->setDisabled(true);
                      ui->OutputSetupButton->setDisabled(true);

                      ui->StartButton->setEnabled(true);
                      ui->PauseButton->setDisabled(true);
                      ui->CancelButton->setEnabled(true);
                      ui->SaveOutputButton->setDisabled(true);
                      ui->ClearOutputButton->setDisabled(true);

                      ui->SaveButton->setDisabled(true);
                      ui->LoadButton->setDisabled(true);

                      ui->FactorizationComboBox->setDisabled(true);
                      ui->CollisionComboBox->setDisabled(true);

                      ui->TaskListWidget->setDisabled(true);
                      break;

    case Evaluated:   ui->PDFsButton->setDisabled(true);
                      ui->ScopeSetupButton->setDisabled(true);
                      ui->PhaseSpaceSetupButton->setDisabled(true);
                      ui->OutputSetupButton->setDisabled(true);

                      ui->StartButton->setDisabled(true);
                      ui->PauseButton->setDisabled(true);
                      ui->CancelButton->setDisabled(true);
                      ui->SaveOutputButton->setEnabled(true);
                      ui->ClearOutputButton->setEnabled(true);

                      ui->SaveButton->setDisabled(true);
                      ui->LoadButton->setDisabled(true);

                      ui->FactorizationComboBox->setDisabled(true);
                      ui->CollisionComboBox->setDisabled(true);

                      ui->TaskListWidget->setDisabled(true);
                      break;
  }
}

void MainWindow::setStatusBarMessage(void)
{
  QString StatusMessage = "PDF: ";

  switch (PDF)
  {
    case AZERO:       StatusMessage.append("A0");
                      break;
    case JH2013set1:  StatusMessage.append("JH'2013 (set 1)");
                      break;
    case JH2013set2:  StatusMessage.append("JH'2013 (set 2)");
                      break;
    case KMR:         StatusMessage.append("KMR");
                      break;
    case GRV94LO:     StatusMessage.append("GRV'94 (LO)");
                      break;
    case MSTW2008LO:  StatusMessage.append("MSTW'2008 (LO)");
                      break;
    case MSTW2008NLO: StatusMessage.append("MSTW'2008 (NLO)");
                      break;
    case CTEQ66:      StatusMessage.append("CTEQ66");
                      break;
  }

  StatusMessage.append("    total c.m. energy [TeV]: ");
  StatusMessage.append(QString::number(Ecm*GeV2TeV));
  StatusMessage.append("    active quark flavors: ");
  StatusMessage.append(QString::number(NF));
  StatusMessage.append("    QCD scale [GeV]: ");
  StatusMessage.append(QString::number(LQCD));
  StatusMessage.append("    strong coupling constant: ");

  if (isaQCDHO) StatusMessage.append("two-loop");
    else StatusMessage.append("one-loop");

  ui->StatusBar->showMessage(StatusMessage);
}

void MainWindow::onTaskListWidgetClicked(const QModelIndex &index)
{
  switch (index.row())
  {
    case 0: Task = OpenBeauty;
  }

  TaskStatus = Specified;

  setControlStatus();
  setStatusBarMessage();
}

void MainWindow::onFactorizationComboBoxCurrentIndexChanged(int index)
{
  switch (index)
  {
    case 0: Factorization = TMD;
            RenormalizationScale = SubprocessEnergy;
            FactorizationScale = SubprocessEnergyPlusPairTransverseMomentum;
            PDF = AZERO;
            break;

    case 1: Factorization = COLL;
            RenormalizationScale = SubprocessEnergy;
            FactorizationScale = SubprocessEnergy;
            PDF = MSTW2008LO;
            break;
  }

  assist();
  setStatusBarMessage();
}

void MainWindow::onCollisionComboBoxCurrentIndexChanged(int index)
{
  if (index == 0) Collision = pp;
    else Collision = ppbar;
}

void MainWindow::onPDFsButtonClicked()
{
  PDFsDialog Dialog(this);

  if ( Dialog.exec() == QDialog::Accepted )
  {
    Dialog.setToStock();
    assist();
    setStatusBarMessage();
  }
}

void MainWindow::onScopeSetupButtonClicked()
{
  ScopeDialog Dialog(this);

  if ( Dialog.exec() == QDialog::Accepted )
  {
    Dialog.setToStock();
    setStatusBarMessage();
  }
}

void MainWindow::onPhaseSpaceSetupButtonClicked()
{
  OpenBeautyPhaseSpaceDialog Dialog(this);

  if ( Dialog.exec() == QDialog::Accepted )
    Dialog.setToStock();
}

void MainWindow::onOutputSetupButtonClicked()
{
  OpenBeautyOutputDialog Dialog(this);

  if ( Dialog.exec() == QDialog::Accepted )
    Dialog.setToStock();
}

void MainWindow::onProgress(int param)
{
  ui->ProgressBar->setValue(param);
}

void MainWindow::onStartButtonClicked()
{
  A0.LoadFromFile("A0.dat");
  if (A0.isDataFileLoaded == true) ui->LogTextBrowser->insertPlainText("data file is loaded");

  if (Factorization == COLL)
  {
    ndim = 5;

    regn[1] = log(1.0e-03);    regn[6] = log(1.0e+03);
    regn[2] = - 7.5;           regn[7] = 7.5;
    regn[3] = - 7.5;           regn[8] = 7.5;
    regn[4] = 0.0;             regn[9] = 2.0*PI;
    regn[5] = 0.0;             regn[10] = 2.0*PI;
  }

  if (Factorization == TMD)
  {
    ndim = 7;

    regn[1] = log(1.0e-03);    regn[8] = log(1.0e+03);
    regn[2] = - 7.5;           regn[9] = 7.5;
    regn[3] = - 7.5;           regn[10] = 7.5;
    regn[4] = 0.0;             regn[11] = 2.0*PI;
    regn[5] = 0.0;             regn[12] = 2.0*PI;
    regn[6] = log(0.001);      regn[13] = log(1.0e+03);
    regn[7] = log(0.001);      regn[14] = log(1.0e+03);
  }

  init = 0;
  itmx = 20;
  calls = 20000;

  ui->LogTextBrowser->append("VEGAS is adjusting integration grid...");

//   vegas(regn,ndim,calcgg2bb,init,calls,itmx,&tgral,&sd,&chi2a, VegasRunner::updateIntegrationStatus,this);

  ui->LogTextBrowser->append("finished");

  init = 1;
  itmx = nIterations;
  calls = nEventsPerIteration;

  ui->LogTextBrowser->append("Starting VEGAS integration...");

  VegasRunner *vr = new VegasRunner(regn,ndim,calcgg2bb,init,calls,itmx,&tgral,&sd,&chi2a);
  connect(vr, SIGNAL(progress(int)), this, SLOT(onProgress(int)));
  vegasThread = new QThread(this);
  connect(vegasThread, SIGNAL(started()), vr, SLOT(start()));
  connect(vr, SIGNAL(stopped()), vegasThread, SLOT(quit()));    // CHECKME: is quit() approirate?
  vegasThread->start();

  ui->LogTextBrowser->append("finished");
  saveOpenBeautyOutput();
}
