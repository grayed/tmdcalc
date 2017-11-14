#include <QDialog>

namespace Ui {
  class ScopeDialog;
}

class ScopeDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ScopeDialog(QWidget *parent = 0);
  ~ScopeDialog();

  void setToStock(void);

private:
  Ui::ScopeDialog *ui;
};
