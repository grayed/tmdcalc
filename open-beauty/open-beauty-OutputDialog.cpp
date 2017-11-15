/*
 * (c) Artem Lipatov, 2017
 */

#include "open-beauty-OutputDialog.h"
#include "ui_open-beauty-OutputDialog.h"

#include <QStringList>
#include <QStandardItem>

#include "lib/common/histogram.h"

extern THistogram hbTransverseMomentum;
extern THistogram hbRapidity;
extern THistogram hbbInvariantMass;
extern THistogram hbbAzimuthalAngle;

OpenBeautyOutputDialog::OpenBeautyOutputDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::OpenBeautyOutputDialog)
{
  ui->setupUi(this);

  connect(ui->TransverseMomentumLineEdit1, SIGNAL(editingFinished()), this, SLOT(onTransverseMomentumTableModified()));
  connect(ui->TransverseMomentumLineEdit2, SIGNAL(editingFinished()), this, SLOT(onTransverseMomentumTableModified()));
  connect(ui->TransverseMomentumSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onTransverseMomentumTableModified()));
  connect(ui->TransverseMomentumUpdateButton, SIGNAL(clicked()), this, SLOT(onTransverseMomentumUpdateButtonClicked()));

  connect(ui->RapidityLineEdit1, SIGNAL(editingFinished()), this, SLOT(onRapidityTableModified()));
  connect(ui->RapidityLineEdit2, SIGNAL(editingFinished()), this, SLOT(onRapidityTableModified()));
  connect(ui->RapiditySpinBox, SIGNAL(valueChanged(int)), this, SLOT(onRapidityTableModified()));
  connect(ui->RapidityUpdateButton, SIGNAL(clicked()), this, SLOT(onRapidityUpdateButtonClicked()));

  connect(ui->InvariantMassLineEdit1, SIGNAL(editingFinished()), this, SLOT(onInvariantMassTableModified()));
  connect(ui->InvariantMassLineEdit2, SIGNAL(editingFinished()), this, SLOT(onInvariantMassTableModified()));
  connect(ui->InvariantMassSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onInvariantMassTableModified()));
  connect(ui->InvariantMassUpdateButton, SIGNAL(clicked()), this, SLOT(onInvariantMassUpdateButtonClicked()));

  connect(ui->AzimuthalAngleLineEdit1, SIGNAL(editingFinished()), this, SLOT(onAzimuthalAngleTableModified()));
  connect(ui->AzimuthalAngleLineEdit2, SIGNAL(editingFinished()), this, SLOT(onAzimuthalAngleTableModified()));
  connect(ui->AzimuthalAngleSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onAzimuthalAngleTableModified()));
  connect(ui->AzimuthalAngleUpdateButton, SIGNAL(clicked()), this, SLOT(onAzimuthalAngleUpdateButtonClicked()));

  TransverseMomentumModel = new QStandardItemModel;
  RapidityModel = new QStandardItemModel;
  InvariantMassModel = new QStandardItemModel;
  AzimuthalAngleModel = new QStandardItemModel;

  showTransverseMomentumTable();
  showRapidityTable();
  showInvariantMassTable();
  showAzimuthalAngleTable();

  TranverseMomentumTableStatus = Fixed;
  RapidityTableStatus = Fixed;
  InvariantMassTableStatus = Fixed;
  AzimuthalAngleTableStatus = Fixed;

  setControlStatus();
}

OpenBeautyOutputDialog::~OpenBeautyOutputDialog()
{
  delete ui;
}

void OpenBeautyOutputDialog::setControlStatus(void)
{
  switch (TranverseMomentumTableStatus)
  {
    case Fixed:    ui->TransverseMomentumUpdateButton->setDisabled(true);
                   break;
    case Modified: ui->TransverseMomentumUpdateButton->setEnabled(true);
                   break;
  }

  switch (RapidityTableStatus)
  {
    case Fixed:    ui->RapidityUpdateButton->setDisabled(true);
                   break;
    case Modified: ui->RapidityUpdateButton->setEnabled(true);
                   break;
  }

  switch (InvariantMassTableStatus)
  {
    case Fixed:    ui->InvariantMassUpdateButton->setDisabled(true);
                   break;
    case Modified: ui->InvariantMassUpdateButton->setEnabled(true);
                   break;
  }

  switch (AzimuthalAngleTableStatus)
  {
    case Fixed:    ui->AzimuthalAngleUpdateButton->setDisabled(true);
                   break;
    case Modified: ui->AzimuthalAngleUpdateButton->setEnabled(true);
                   break;
  }
}

void OpenBeautyOutputDialog::showTransverseMomentumTable(void)
{
  QStringList VerticalHeader;
  QStringList HorizontalHeader;

  HorizontalHeader.append("from");
  HorizontalHeader.append("to");

  QStandardItem *TableItem;
  for (unsigned short int i = 0; i < hbTransverseMomentum.size(); i++)
  {
    VerticalHeader.append("bin #" + QString::number(i + 1));

    TableItem = new QStandardItem(QString::number(hbTransverseMomentum.entry[i].lowerborder));
    TransverseMomentumModel->setItem(i,0,TableItem);

    TableItem = new QStandardItem(QString::number(hbTransverseMomentum.entry[i].upperborder));
    TransverseMomentumModel->setItem(i,1,TableItem);
  }

  TransverseMomentumModel->setHorizontalHeaderLabels(HorizontalHeader);
  TransverseMomentumModel->setVerticalHeaderLabels(VerticalHeader);

  for (unsigned short int i = 0; i < TransverseMomentumModel->rowCount(); i++)
    for (unsigned short int j = 0; j < TransverseMomentumModel->columnCount(); j++)
      TransverseMomentumModel->item(i,j)->setTextAlignment(Qt::AlignCenter);

  ui->TransverseMomentumTableView->setModel(TransverseMomentumModel);
  ui->TransverseMomentumTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->TransverseMomentumTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  ui->TransverseMomentumLineEdit1->setText(QString::number(hbTransverseMomentum.entry[0].lowerborder));
  ui->TransverseMomentumLineEdit2->setText(QString::number(hbTransverseMomentum.entry[hbTransverseMomentum.size() - 1].upperborder));
  ui->TransverseMomentumSpinBox->setValue(hbTransverseMomentum.size());
}

void OpenBeautyOutputDialog::showRapidityTable(void)
{
  QStringList VerticalHeader;
  QStringList HorizontalHeader;

  HorizontalHeader.append("from");
  HorizontalHeader.append("to");

  QStandardItem *TableItem;
  for (unsigned short int i = 0; i < hbRapidity.size(); i++)
  {
    VerticalHeader.append("bin #" + QString::number(i + 1));

    TableItem = new QStandardItem(QString::number(hbRapidity.entry[i].lowerborder));
    RapidityModel->setItem(i,0,TableItem);

    TableItem = new QStandardItem(QString::number(hbRapidity.entry[i].upperborder));
    RapidityModel->setItem(i,1,TableItem);
  }

  RapidityModel->setHorizontalHeaderLabels(HorizontalHeader);
  RapidityModel->setVerticalHeaderLabels(VerticalHeader);

  for (unsigned short int i = 0; i < RapidityModel->rowCount(); i++)
    for (unsigned short int j = 0; j < RapidityModel->columnCount(); j++)
      RapidityModel->item(i,j)->setTextAlignment(Qt::AlignCenter);

  ui->RapidityTableView->setModel(RapidityModel);
  ui->RapidityTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->RapidityTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  ui->RapidityLineEdit1->setText(QString::number(hbRapidity.entry[0].lowerborder));
  ui->RapidityLineEdit2->setText(QString::number(hbRapidity.entry[hbRapidity.size() - 1].upperborder));
  ui->RapiditySpinBox->setValue(hbRapidity.size());
}

void OpenBeautyOutputDialog::showInvariantMassTable(void)
{
  QStringList VerticalHeader;
  QStringList HorizontalHeader;

  HorizontalHeader.append("from");
  HorizontalHeader.append("to");

  QStandardItem *TableItem;
  for (unsigned short int i = 0; i < hbbInvariantMass.size(); i++)
  {
    VerticalHeader.append("bin #" + QString::number(i + 1));

    TableItem = new QStandardItem(QString::number(hbbInvariantMass.entry[i].lowerborder));
    InvariantMassModel->setItem(i,0,TableItem);

    TableItem = new QStandardItem(QString::number(hbbInvariantMass.entry[i].upperborder));
    InvariantMassModel->setItem(i,1,TableItem);
  }

  InvariantMassModel->setHorizontalHeaderLabels(HorizontalHeader);
  InvariantMassModel->setVerticalHeaderLabels(VerticalHeader);

  for (unsigned short int i = 0; i < InvariantMassModel->rowCount(); i++)
    for (unsigned short int j = 0; j < InvariantMassModel->columnCount(); j++)
      InvariantMassModel->item(i,j)->setTextAlignment(Qt::AlignCenter);

  ui->InvariantMassTableView->setModel(InvariantMassModel);
  ui->InvariantMassTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->InvariantMassTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  ui->InvariantMassLineEdit1->setText(QString::number(hbbInvariantMass.entry[0].lowerborder));
  ui->InvariantMassLineEdit2->setText(QString::number(hbbInvariantMass.entry[hbbInvariantMass.size() - 1].upperborder));
  ui->InvariantMassSpinBox->setValue(hbbInvariantMass.size());
}

void OpenBeautyOutputDialog::showAzimuthalAngleTable(void)
{
  QStringList VerticalHeader;
  QStringList HorizontalHeader;

  HorizontalHeader.append("from");
  HorizontalHeader.append("to");

  QStandardItem *TableItem;
  for (unsigned short int i = 0; i < hbbAzimuthalAngle.size(); i++)
  {
    VerticalHeader.append("bin #" + QString::number(i + 1));

    TableItem = new QStandardItem(QString::number(hbbAzimuthalAngle.entry[i].lowerborder));
    AzimuthalAngleModel->setItem(i,0,TableItem);

    TableItem = new QStandardItem(QString::number(hbbAzimuthalAngle.entry[i].upperborder));
    AzimuthalAngleModel->setItem(i,1,TableItem);
  }

  AzimuthalAngleModel->setHorizontalHeaderLabels(HorizontalHeader);
  AzimuthalAngleModel->setVerticalHeaderLabels(VerticalHeader);

  for (unsigned short int i = 0; i < AzimuthalAngleModel->rowCount(); i++)
    for (unsigned short int j = 0; j < AzimuthalAngleModel->columnCount(); j++)
      AzimuthalAngleModel->item(i,j)->setTextAlignment(Qt::AlignCenter);

  ui->AzimuthalAngleTableView->setModel(AzimuthalAngleModel);
  ui->AzimuthalAngleTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->AzimuthalAngleTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  ui->AzimuthalAngleLineEdit1->setText(QString::number(hbbAzimuthalAngle.entry[0].lowerborder));
  ui->AzimuthalAngleLineEdit2->setText(QString::number(hbbAzimuthalAngle.entry[hbbAzimuthalAngle.size() - 1].upperborder));
  ui->AzimuthalAngleSpinBox->setValue(hbbAzimuthalAngle.size());
}

void OpenBeautyOutputDialog::onTransverseMomentumTableModified()
{
  TranverseMomentumTableStatus = Modified;
  setControlStatus();
}

void OpenBeautyOutputDialog::onRapidityTableModified()
{
  RapidityTableStatus = Modified;
  setControlStatus();
}

void OpenBeautyOutputDialog::onInvariantMassTableModified()
{
  InvariantMassTableStatus = Modified;
  setControlStatus();
}

void OpenBeautyOutputDialog::onAzimuthalAngleTableModified()
{
  AzimuthalAngleTableStatus = Modified;
  setControlStatus();
}

void OpenBeautyOutputDialog::onTransverseMomentumUpdateButtonClicked()
{
  TransverseMomentumModel->clear();
  ui->TransverseMomentumTableView->setFocus();

  hbTransverseMomentum.update(QString(ui->TransverseMomentumLineEdit1->text()).toDouble(), QString(ui->TransverseMomentumLineEdit2->text()).toDouble(), ui->TransverseMomentumSpinBox->value());
  showTransverseMomentumTable();

  TranverseMomentumTableStatus = Fixed;
  setControlStatus();
}

void OpenBeautyOutputDialog::onRapidityUpdateButtonClicked()
{
  RapidityModel->clear();
  ui->RapidityTableView->setFocus();

  hbRapidity.update(QString(ui->RapidityLineEdit1->text()).toDouble(), QString(ui->RapidityLineEdit2->text()).toDouble(), ui->RapiditySpinBox->value());
  showRapidityTable();

  RapidityTableStatus = Fixed;
  setControlStatus();
}

void OpenBeautyOutputDialog::onInvariantMassUpdateButtonClicked()
{
  InvariantMassModel->clear();
  ui->InvariantMassTableView->setFocus();

  hbbInvariantMass.update(QString(ui->InvariantMassLineEdit1->text()).toDouble(), QString(ui->InvariantMassLineEdit2->text()).toDouble(), ui->InvariantMassSpinBox->value());
  showInvariantMassTable();

  InvariantMassTableStatus = Fixed;
  setControlStatus();
}

void OpenBeautyOutputDialog::onAzimuthalAngleUpdateButtonClicked()
{
  AzimuthalAngleModel->clear();
  ui->AzimuthalAngleTableView->setFocus();

  hbbAzimuthalAngle.update(QString(ui->AzimuthalAngleLineEdit1->text()).toDouble(), QString(ui->AzimuthalAngleLineEdit2->text()).toDouble(), ui->AzimuthalAngleSpinBox->value());
  showAzimuthalAngleTable();

  AzimuthalAngleTableStatus = Fixed;
  setControlStatus();
}

void OpenBeautyOutputDialog::setToStock(void)
{
  for (unsigned short int i = 0; i < hbTransverseMomentum.size(); i++)
    hbTransverseMomentum.format(i, QString(TransverseMomentumModel->item(i,0)->text()).toDouble(), QString(TransverseMomentumModel->item(i,1)->text()).toDouble());

  for (unsigned short int i = 0; i < hbRapidity.size(); i++)
    hbRapidity.format(i, QString(RapidityModel->item(i,0)->text()).toDouble(), QString(RapidityModel->item(i,1)->text()).toDouble());

  for (unsigned short int i = 0; i < hbbInvariantMass.size(); i++)
    hbbInvariantMass.format(i, QString(InvariantMassModel->item(i,0)->text()).toDouble(), QString(InvariantMassModel->item(i,1)->text()).toDouble());

  for (unsigned short int i = 0; i < hbbAzimuthalAngle.size(); i++)
    hbbAzimuthalAngle.format(i, QString(AzimuthalAngleModel->item(i,0)->text()).toDouble(), QString(AzimuthalAngleModel->item(i,1)->text()).toDouble());
}
