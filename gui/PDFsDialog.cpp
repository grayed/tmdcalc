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

#include "PDFsDialog.h"
#include "ui_PDFsDialog.h"

#include "lib/common/utils.h"

PDFsDialog::PDFsDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::PDFsDialog)
{
  ui->setupUi(this);

  switch (Factorization)
  {
    case TMD:  ui->PDFsListWidget->addItem("A0");
               ui->PDFsListWidget->addItem("JH'2013 set 1");
               ui->PDFsListWidget->addItem("JH'2013 set 2");

               if (PDF == AZERO) ui->PDFsListWidget->item(0)->setSelected(true);
               if (PDF == JH2013set1) ui->PDFsListWidget->item(1)->setSelected(true);
               if (PDF == JH2013set2) ui->PDFsListWidget->item(2)->setSelected(true);

               break;

    case COLL: ui->PDFsListWidget->addItem("MSTW'2008 (LO)");
               ui->PDFsListWidget->addItem("MSTW'2008 (NLO)");
               ui->PDFsListWidget->addItem("CTEQ66");
               ui->PDFsListWidget->addItem("GRV'94 (LO)");

               if (PDF == MSTW2008LO) ui->PDFsListWidget->item(0)->setSelected(true);
               if (PDF == MSTW2008NLO) ui->PDFsListWidget->item(1)->setSelected(true);
               if (PDF == CTEQ66) ui->PDFsListWidget->item(2)->setSelected(true);
               if (PDF == GRV94LO) ui->PDFsListWidget->item(3)->setSelected(true);

               break;
  }
}

PDFsDialog::~PDFsDialog()
{
  delete ui;
}

void PDFsDialog::setToStock(void)
{
  if (Factorization == TMD)
    switch (ui->PDFsListWidget->currentRow())
    {
      case 0: PDF = AZERO;
              break;
      case 1: PDF = JH2013set1;
              break;
      case 2: PDF = JH2013set2;
              break;
    }

  if (Factorization == COLL)
    switch (ui->PDFsListWidget->currentRow())
    {
      case 0: PDF = MSTW2008LO;
              break;
      case 1: PDF = MSTW2008NLO;
              break;
      case 2: PDF = CTEQ66;
              break;
      case 3: PDF = GRV94LO;
              break;
    }
}
