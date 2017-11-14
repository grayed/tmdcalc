#ifndef OPEN_BEAUTY_OUTPUTDIALOG_H
#define OPEN_BEAUTY_OUTPUTDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

enum TOpenBeautyOutputStatus { Fixed, Modified };

namespace Ui {
  class OpenBeautyOutputDialog;
}

class OpenBeautyOutputDialog : public QDialog
{
  Q_OBJECT

public:
  explicit OpenBeautyOutputDialog(QWidget *parent = 0);
  ~OpenBeautyOutputDialog();

  void setToStock(void);

private slots:
  void onTransverseMomentumTableModified();
  void onTransverseMomentumUpdateButtonClicked();

  void onRapidityTableModified();
  void onRapidityUpdateButtonClicked();

  void onInvariantMassTableModified();
  void onInvariantMassUpdateButtonClicked();

  void onAzimuthalAngleTableModified();
  void onAzimuthalAngleUpdateButtonClicked();

private:
  Ui::OpenBeautyOutputDialog *ui;

  QStandardItemModel *TransverseMomentumModel;
  QStandardItemModel *RapidityModel;
  QStandardItemModel *InvariantMassModel;
  QStandardItemModel *AzimuthalAngleModel;

  TOpenBeautyOutputStatus TranverseMomentumTableStatus = Fixed;
  TOpenBeautyOutputStatus RapidityTableStatus = Fixed;
  TOpenBeautyOutputStatus InvariantMassTableStatus = Fixed;
  TOpenBeautyOutputStatus AzimuthalAngleTableStatus = Fixed;

  void showTransverseMomentumTable(void);
  void showRapidityTable(void);
  void showInvariantMassTable(void);
  void showAzimuthalAngleTable(void);

  void setControlStatus(void);
};

#endif
