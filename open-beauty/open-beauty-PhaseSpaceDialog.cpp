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

#include "open-beauty-PhaseSpaceDialog.h"
#include "ui_open-beauty-PhaseSpaceDialog.h"

#include <QString>
#include <QStringList>
#include <QStandardItem>

extern double minlBeautyTransverseMomentum;
extern double maxlBeautyTransverseMomentum;
extern double minlBeautyRapidity;
extern double maxlBeautyRapidity;
extern double minlBeautyPseudoRapidity;
extern double maxlBeautyPseudoRapidity;

extern double minnlBeautyTransverseMomentum;
extern double maxnlBeautyTransverseMomentum;
extern double minnlBeautyRapidity;
extern double maxnlBeautyRapidity;
extern double minnlBeautyPseudoRapidity;
extern double maxnlBeautyPseudoRapidity;

extern double minBeautyPairInvariantMass;
extern double maxBeautyPairInvariantMass;

extern double minBeautyPairAzimuthalAngle;
extern double maxBeautyPairAzimuthalAngle;

OpenBeautyPhaseSpaceDialog::OpenBeautyPhaseSpaceDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::OpenBeautyPhaseSpaceDialog)
{
  ui->setupUi(this);

  QStringList VerticalHeader;
  QStringList HorizontalHeader;

  HorizontalHeader.append("from");
  HorizontalHeader.append("to");

  VerticalHeader.append("First b-quark transverse momentum [GeV]");
  VerticalHeader.append("First b-quark rapidity");
  VerticalHeader.append("First b-quark pseudo-rapidity");
  VerticalHeader.append("Second b-quark transverse momentum [GeV]");
  VerticalHeader.append("Second b-quark rapidity");
  VerticalHeader.append("Second b-quark pseudo-rapidity");
  VerticalHeader.append("Invariant mass of bb pair [GeV]");
  VerticalHeader.append("Azimuthal angle difference [rad]");

  PhaseSpaceModel = new QStandardItemModel;
  PhaseSpaceModel->setHorizontalHeaderLabels(HorizontalHeader);
  PhaseSpaceModel->setVerticalHeaderLabels(VerticalHeader);

  QStandardItem *TableItem;

  TableItem = new QStandardItem(QString::number(minlBeautyTransverseMomentum));
  PhaseSpaceModel->setItem(0,0,TableItem);

  TableItem = new QStandardItem(QString::number(maxlBeautyTransverseMomentum));
  PhaseSpaceModel->setItem(0,1,TableItem);

  TableItem = new QStandardItem(QString::number(minlBeautyRapidity));
  PhaseSpaceModel->setItem(1,0,TableItem);

  TableItem = new QStandardItem(QString::number(maxlBeautyRapidity));
  PhaseSpaceModel->setItem(1,1,TableItem);

  TableItem = new QStandardItem(QString::number(minlBeautyPseudoRapidity));
  PhaseSpaceModel->setItem(2,0,TableItem);

  TableItem = new QStandardItem(QString::number(maxlBeautyPseudoRapidity));
  PhaseSpaceModel->setItem(2,1,TableItem);

  TableItem = new QStandardItem(QString::number(minnlBeautyTransverseMomentum));
  PhaseSpaceModel->setItem(3,0,TableItem);

  TableItem = new QStandardItem(QString::number(maxnlBeautyTransverseMomentum));
  PhaseSpaceModel->setItem(3,1,TableItem);

  TableItem = new QStandardItem(QString::number(minnlBeautyRapidity));
  PhaseSpaceModel->setItem(4,0,TableItem);

  TableItem = new QStandardItem(QString::number(maxnlBeautyRapidity));
  PhaseSpaceModel->setItem(4,1,TableItem);

  TableItem = new QStandardItem(QString::number(minnlBeautyPseudoRapidity));
  PhaseSpaceModel->setItem(5,0,TableItem);

  TableItem = new QStandardItem(QString::number(maxnlBeautyPseudoRapidity));
  PhaseSpaceModel->setItem(5,1,TableItem);

  TableItem = new QStandardItem(QString::number(minBeautyPairInvariantMass));
  PhaseSpaceModel->setItem(6,0,TableItem);

  TableItem = new QStandardItem(QString::number(maxBeautyPairInvariantMass));
  PhaseSpaceModel->setItem(6,1,TableItem);

  TableItem = new QStandardItem(QString::number(minBeautyPairAzimuthalAngle));
  PhaseSpaceModel->setItem(7,0,TableItem);

  TableItem = new QStandardItem(QString::number(maxBeautyPairAzimuthalAngle));
  PhaseSpaceModel->setItem(7,1,TableItem);

  for (unsigned short int i = 0; i < PhaseSpaceModel->rowCount(); i++)
    for (unsigned short int j = 0; j < PhaseSpaceModel->columnCount(); j++)
      PhaseSpaceModel->item(i,j)->setTextAlignment(Qt::AlignCenter);

  ui->TableView->setModel(PhaseSpaceModel);
  ui->TableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->TableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

OpenBeautyPhaseSpaceDialog::~OpenBeautyPhaseSpaceDialog()
{
  delete ui;
}

void OpenBeautyPhaseSpaceDialog::setToStock(void)
{
  minlBeautyTransverseMomentum = QString(PhaseSpaceModel->item(0,0)->text()).toDouble();
  maxlBeautyTransverseMomentum = QString(PhaseSpaceModel->item(0,1)->text()).toDouble();
  minlBeautyRapidity = QString(PhaseSpaceModel->item(1,0)->text()).toDouble();
  maxlBeautyRapidity = QString(PhaseSpaceModel->item(1,1)->text()).toDouble();
  minlBeautyPseudoRapidity = QString(PhaseSpaceModel->item(2,0)->text()).toDouble();
  maxlBeautyPseudoRapidity = QString(PhaseSpaceModel->item(2,1)->text()).toDouble();

  minnlBeautyTransverseMomentum = QString(PhaseSpaceModel->item(3,0)->text()).toDouble();
  maxnlBeautyTransverseMomentum = QString(PhaseSpaceModel->item(3,1)->text()).toDouble();
  minnlBeautyRapidity = QString(PhaseSpaceModel->item(4,0)->text()).toDouble();
  maxnlBeautyRapidity = QString(PhaseSpaceModel->item(4,1)->text()).toDouble();
  minnlBeautyPseudoRapidity = QString(PhaseSpaceModel->item(5,0)->text()).toDouble();
  maxnlBeautyPseudoRapidity = QString(PhaseSpaceModel->item(5,1)->text()).toDouble();

  minBeautyPairInvariantMass = QString(PhaseSpaceModel->item(6,0)->text()).toDouble();
  maxBeautyPairInvariantMass = QString(PhaseSpaceModel->item(6,1)->text()).toDouble();

  minBeautyPairAzimuthalAngle = QString(PhaseSpaceModel->item(7,0)->text()).toDouble();
  maxBeautyPairAzimuthalAngle = QString(PhaseSpaceModel->item(7,1)->text()).toDouble();
}
