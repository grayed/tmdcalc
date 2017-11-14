#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
  class OpenBeautyPhaseSpaceDialog;
}

class OpenBeautyPhaseSpaceDialog : public QDialog
{
  Q_OBJECT

public:
  explicit OpenBeautyPhaseSpaceDialog(QWidget *parent = 0);
  ~OpenBeautyPhaseSpaceDialog();

  void setToStock(void);

private:
  Ui::OpenBeautyPhaseSpaceDialog *ui;

  QStandardItemModel *PhaseSpaceModel;
};
