#include <QObject>

extern "C"
{
  #include "lib/extern/vegas.h"
}


class VegasRunner : public QObject {
  Q_OBJECT

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
    vegas(regn, ndim, fxn, init, calls, itmx, tgral, sd, chi2a, updateIntegrationStatus, this);
    emit stopped();
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
  void stopped();
};
