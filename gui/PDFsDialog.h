#include <QDialog>
#include <QModelIndex>

namespace Ui {
  class PDFsDialog;
}

class PDFsDialog : public QDialog
{
  Q_OBJECT

public:
  explicit PDFsDialog(QWidget *parent = 0);
  ~PDFsDialog();

  void setToStock(void);

private:
  Ui::PDFsDialog *ui;
};
