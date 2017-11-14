#ifndef TMDPDF_H
#define TMDPDF_H

#include <QVector>
#include <QString>

class tmdpdf {
public:
  tmdpdf(void);
  ~tmdpdf(void);

  double getTMD(double x, double k2, double q);

  void LoadFromFile(QString FileName);
  bool isDataFileLoaded;

private:
  QVector <double> entry1;
  QVector <double> entry2;
  QVector <double> entry3;

  QVector <double> store;
};

#endif // TMDPDF_H
