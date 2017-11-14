#include <cmath>
#include "../lib/common/SM.h"
#include "../lib/common/frames.h"
#include "../lib/common/utils.h"
#include "../lib/common/HEPVector4.h"
#include "../lib/pdfs/pdf.h"
#include "../lib/tmdpdfs/tmdpdf.h"
#include "../lib/extern/vegas.h"

extern TFactorization Factorization;
extern TScaleRate ScaleRate;
extern TPDF PDF;

extern double Ecm;
extern THEPVector4 H, beam1, beam2;

extern tmdpdf A0;

extern void putOpenBeautyEvent(THEPVector4 p1, THEPVector4 p2, double store);
extern void saveOpenBeautyOutput(void);

extern double gg2qq(THEPVector4 k1, THEPVector4 k2, THEPVector4 p1, THEPVector4 p2, THEPVector4 e1, THEPVector4 e2, double m2, double muR2);

double calcgg2bb(double x[], double wgt)
{
  double muR2, muF2, J, gluon1, gluon2;
  double pt12, y1, mt1, phi1;
  double pt22, y2, mt2;
  double kt12, theta1;
  double kt22, theta2;
  double s, t, u;
  double x1, x2;
  THEPVector4 p1, p2, k1, k2, e1, e2, Q;

  double dsigma = 0.0;
  double S = sqr(Ecm);
  double m2 = sqr(mB);

  pt12 = sqr(exp(x[1]));
  y1 = x[2];
  y2 = x[3];
  theta1 = x[4];
  theta2 = x[5];

  kt12 = ZERO;
  kt22 = ZERO;
  J = 2.0*pt12;

  if (Factorization == TMD)
  {
    kt12 = sqr(exp(x[6]));
    kt22 = sqr(exp(x[7]));

    J = 4.0*kt12*kt22*J;
  }

  mt1 = sqrt(m2 + pt12);
  phi1 = random(0.0,2.0*PI);

  p1.set(0,mt1*cosh(y1));
  p1.set(1,sqrt(pt12)*cos(phi1));
  p1.set(2,sqrt(pt12)*sin(phi1));
  p1.set(3,mt1*sinh(y1));

  k1.set(1,sqrt(kt12)*cos(theta1));
  k1.set(2,sqrt(kt12)*sin(theta1));

  k2.set(1,sqrt(kt22)*cos(theta2));
  k2.set(2,sqrt(kt22)*sin(theta2));

  p2.set(1,k1.get(1) + k2.get(1) - p1.get(1));
  p2.set(2,k1.get(2) + k2.get(2) - p1.get(2));

  pt22 = p2.transversemomentum2();
  mt2 = sqrt(m2 + pt22);

  p2.set(0,mt2*cosh(y2));
  p2.set(3,mt2*sinh(y2));

  x1 = ( mt1*exp(y1) + mt2*exp(y2) )/sqrt(S); if (x1 >= 1.0) goto Exit;
  x2 = ( mt1*exp( - y1) + mt2*exp( - y2) )/sqrt(S); if (x2 >= 1.0) goto Exit;

  k1.set(0,x1*sqrt(S)/2.0);
  k1.set(3,x1*sqrt(S)/2.0);

  k2.set(0,x2*sqrt(S)/2.0);
  k2.set(3, - x2*sqrt(S)/2.0);

  beam1.set(0,0.5*sqrt(S));
  beam1.set(1,0.0);
  beam1.set(2,0.0);
  beam1.set(3,0.5*sqrt(S));

  beam2.set(0,0.5*sqrt(S));
  beam2.set(1,0.0);
  beam2.set(2,0.0);
  beam2.set(3, - 0.5*sqrt(S));

  e1.set(0,0.0);
  e1.set(1,cos(theta1));
  e1.set(2,sin(theta1));
  e1.set(3,0.0);

  e2.set(0,0.0);
  e2.set(1,cos(theta2));
  e2.set(2,sin(theta2));
  e2.set(3,0.0);

  t = dot(k2,k2) + dot(p2,p2) - 2.0*dot(k2,p2);
  u = dot(k2,k2) + dot(p1,p1) - 2.0*dot(k2,p1);
  s = dot(k1,k1) + dot(k2,k2) + 2.0*dot(k1,k2);

  if ( G(s,t,dot(p2,p2),dot(k1,k1),dot(k2,k2),dot(p1,p1)) > 0.0 ) goto Exit;
  if ( L(s,dot(k1,k1),dot(k2,k2)) < 0.0 ) goto Exit;
  if ( L(s,dot(p1,p1),dot(p2,p2)) < 0.0 ) goto Exit;

  Q = k1 + k2;
  muR2 = m2 + 0.5*(pt12 + pt22);
  muF2 = s + Q.transversemomentum2();

  if (PDF == AZERO)
  {
    gluon1 = A0.getTMD(x1,kt12,sqrt(muF2));
    gluon2 = A0.getTMD(x2,kt22,sqrt(muF2));
  }

  dsigma = J*gluon1*gluon2*gg2qq(k1,k2,p1,p2,e1,e2,m2,muR2)/(16.0*PI*sqr(x1*x2*S)*sqr(2.0*PI));

  if ( dsigma <= 0.0) goto Exit;

  dsigma = GeV2nb*dsigma;

  if (init > 0)
  {
    putOpenBeautyEvent(p1,p2,wgt*dsigma/itmx);
  }

Exit:
  return dsigma;
}
