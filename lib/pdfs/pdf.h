// pdf.h
// Last modified 04.09.2017 by Artem Lipatov

#ifndef PDF_H
#define PDF_H

#include <string>

#include "../common/utils.h"
#include "../extern/mstwpdf.h"
#include "../extern/ct11pdf.h"

using namespace std;

class pdf {
public:
  pdf(TPDF id);
  pdf(TPDF id, string filename);
  ~pdf(void);

  double gluon(double x, double q2);

  double u(double x, double q2);
  double d(double x, double q2);
  double s(double x, double q2);
  double c(double x, double q2);
  double b(double x, double q2);
  double ubar(double x, double q2);
  double dbar(double x, double q2);

  double uv(double x, double q2);
  double dv(double x, double q2);

  bool isFileLoaded;

private:
  TPDF pdfset;

  cteqpdf cteq66;
  c_mstwpdf* mstw;
};

#endif // PDF_H
