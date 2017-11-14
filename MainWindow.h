#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

enum TTask { unknown, OpenBeauty };
enum TTaskStatus { UnSpecified, Specified, Running, Paused, Evaluated };
class QThread;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void onIntegrationStatusChanged(unsigned int status);

private slots:
  void onTaskListWidgetClicked(const QModelIndex &index);
  void onFactorizationComboBoxCurrentIndexChanged(int index);
  void onCollisionComboBoxCurrentIndexChanged(int index);

  void onPDFsButtonClicked();
  void onScopeSetupButtonClicked();
  void onPhaseSpaceSetupButtonClicked();
  void onOutputSetupButtonClicked();

  void onStartButtonClicked();

  void onProgress(int param);

private:
  Ui::MainWindow *ui;

  TTask Task = unknown;
  TTaskStatus TaskStatus = UnSpecified;
  QThread *vegasThread;

  void setControlStatus(void);
  void setStatusBarMessage(void);
};

#endif // MAINWINDOW_H
