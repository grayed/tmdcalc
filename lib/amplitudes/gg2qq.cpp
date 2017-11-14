/*
 * (c) Artem Lipatov, 2017
 */

#include <cmath>
#include "../common/SM.h"
#include "../common/utils.h"
#include "../common/HEPVector4.h"

using namespace std;

double gg2qq(THEPVector4 k1, THEPVector4 k2, THEPVector4 p1, THEPVector4 p2, THEPVector4 e1, THEPVector4 e2, double m2, double muR2)
{
  double M2gg2qq = 0.0;
  double m = sqrt(m2);

  THEPVector4 K, Q;

  times(p1,p2,K);
  lc3(p1,p2,K,Q);

  double p1p2 = dot(p1,p2);
  double p1k1 = dot(p1,k1);
  double p1k2 = dot(p1,k2);
  double p2k1 = dot(p2,k1);
  double p2k2 = dot(p2,k2);
  double k1k1 = dot(k1,k1);
  double k2k2 = dot(k2,k2);
  double k1k2 = dot(k1,k2);

  double p1e1 = dot(p1,e1);
  double p1e2 = dot(p1,e2);
  double p2e1 = dot(p2,e1);
  double p2e2 = dot(p2,e2);
  double k1e1 = dot(k1,e1);
  double k2e1 = dot(k2,e1);
  double k1e2 = dot(k1,e2);
  double k2e2 = dot(k2,e2);

  double KK = dot(K,K);
  double QQ = dot(Q,Q);

  double k1K = dot(k1,K);
  double k2K = dot(k2,K);

  double k1Q = dot(k1,Q);
  double k2Q = dot(k2,Q);

  double e1K = dot(e1,K);
  double e2K = dot(e2,K);
  double e1Q = dot(e1,Q);
  double e2Q = dot(e2,Q);

  double e1e2 = dot(e1,e2);

  double den1 = 2*p1k1 - k1k1;
  double den2 = 2*p1k2 - k2k2;
  double den3 = k1k1 + 2*k1k2 + k2k2;

  double norm1 = - 4*m2 + 4*p1p2;
  double norm2 = - 4*p1p2*KK - 4*KK*m2;
  double norm3 = - 4*p1p2*QQ - 4*QQ*m2;
  double norm4 = 4*p1p2*KK*QQ - 4*KK*QQ*m2;

  double c11 = 4.0, c21 = 4.0, c31 = 0.0;
  double c12 = 6.0, c22 = - 6.0, c32 = 12.0;
  double c13 = 10.0/3.0, c23 = 10.0/3.0, c33 = 0.0;

  double t11 = - 4*p1k1*e1e2*m - 8*p1e1*p1e2*m + 8*p1e1*p2e2*m + 4*p1e1*
    k1e2*m + 4*p1e2*k1e1*m + 4*p2k1*e1e2*m - 4*p2e1*k1e2*m - 4
    *p2e2*k1e1*m;

  double t12 = - 8*p1p2*p1e1*e2K + 4*p1p2*k1e1*e2K + 4*p1p2*k1e2*e1K
    - 4*p1p2*k1K*e1e2 - 4*p1k1*p2e1*e2K + 4*p1k1*p2e2*e1K
    + 4*p1e1*p2k1*e2K - 4*p1e1*p2e2*k1K - 8*p1e1*e2K*m2 - 4*
    p1e2*p2k1*e1K + 4*p1e2*p2e1*k1K + 4*k1e1*e2K*m2 + 4*k1e2
    *e1K*m2 - 4*k1K*e1e2*m2;

  double t13 = - 8*p1p2*p1e1*e2Q + 4*p1p2*k1e1*e2Q + 4*p1p2*k1e2*e1Q
    - 4*p1p2*k1Q*e1e2 - 4*p1k1*p2e1*e2Q + 4*p1k1*p2e2*e1Q
    + 4*p1e1*p2k1*e2Q - 4*p1e1*p2e2*k1Q - 8*p1e1*e2Q*m2 - 4*
    p1e2*p2k1*e1Q + 4*p1e2*p2e1*k1Q + 4*k1e1*e2Q*m2 + 4*k1e2
    *e1Q*m2 - 4*k1Q*e1e2*m2;

  double t14 = - 4*p1k1*e1K*e2Q*m + 4*p1k1*e1Q*e2K*m + 4*p1e1*k1K*e2Q*
    m - 4*p1e1*k1Q*e2K*m - 4*p1e2*k1K*e1Q*m + 4*p1e2*k1Q*e1K
    *m + 4*p2k1*e1K*e2Q*m - 4*p2k1*e1Q*e2K*m - 4*p2e1*k1K*
    e2Q*m + 4*p2e1*k1Q*e2K*m + 4*p2e2*k1K*e1Q*m - 4*p2e2*k1Q
    *e1K*m;

  double t21 = - 4*p1k2*e1e2*m - 8*p1e1*p1e2*m + 4*p1e1*k2e2*m + 8*p1e2*
    p2e1*m + 4*p1e2*k2e1*m + 4*p2k2*e1e2*m - 4*p2e1*k2e2*m - 4
    *p2e2*k2e1*m;

  double t22 = - 8*p1p2*p1e2*e1K + 4*p1p2*k2e1*e2K + 4*p1p2*k2e2*e1K
    - 4*p1p2*k2K*e1e2 + 4*p1k2*p2e1*e2K - 4*p1k2*p2e2*e1K
    - 4*p1e1*p2k2*e2K + 4*p1e1*p2e2*k2K + 4*p1e2*p2k2*e1K
    - 4*p1e2*p2e1*k2K - 8*p1e2*e1K*m2 + 4*k2e1*e2K*m2 + 4*
    k2e2*e1K*m2 - 4*k2K*e1e2*m2;

  double t23 = - 8*p1p2*p1e2*e1Q + 4*p1p2*k2e1*e2Q + 4*p1p2*k2e2*e1Q
    - 4*p1p2*k2Q*e1e2 + 4*p1k2*p2e1*e2Q - 4*p1k2*p2e2*e1Q
    - 4*p1e1*p2k2*e2Q + 4*p1e1*p2e2*k2Q + 4*p1e2*p2k2*e1Q
    - 4*p1e2*p2e1*k2Q - 8*p1e2*e1Q*m2 + 4*k2e1*e2Q*m2 + 4*
    k2e2*e1Q*m2 - 4*k2Q*e1e2*m2;

  double t24 = 4*p1k2*e1K*e2Q*m - 4*p1k2*e1Q*e2K*m - 4*p1e1*k2K*e2Q*m
    + 4*p1e1*k2Q*e2K*m + 4*p1e2*k2K*e1Q*m - 4*p1e2*k2Q*e1K*
    m - 4*p2k2*e1K*e2Q*m + 4*p2k2*e1Q*e2K*m + 4*p2e1*k2K*e2Q
    *m - 4*p2e1*k2Q*e2K*m - 4*p2e2*k2K*e1Q*m + 4*p2e2*k2Q*
    e1K*m;

  double t31 = 4*p1k1*e1e2*m - 4*p1k2*e1e2*m - 8*p1e1*k1e2*m - 4*p1e1*
    k2e2*m + 4*p1e2*k1e1*m + 8*p1e2*k2e1*m - 4*p2k1*e1e2*m + 4
    *p2k2*e1e2*m + 8*p2e1*k1e2*m + 4*p2e1*k2e2*m - 4*p2e2*
    k1e1*m - 8*p2e2*k2e1*m;

  double t32 = 4*p1p2*k1e1*e2K - 8*p1p2*k1e2*e1K + 4*p1p2*k1K*e1e2 + 8*
    p1p2*k2e1*e2K - 4*p1p2*k2e2*e1K - 4*p1p2*k2K*e1e2 + 4*
    k1e1*e2K*m2 - 8*k1e2*e1K*m2 + 4*k1K*e1e2*m2 + 8*k2e1*e2K*
    m2 - 4*k2e2*e1K*m2 - 4*k2K*e1e2*m2;

  double t33 = 4*p1p2*k1e1*e2Q - 8*p1p2*k1e2*e1Q + 4*p1p2*k1Q*e1e2 + 8*
    p1p2*k2e1*e2Q - 4*p1p2*k2e2*e1Q - 4*p1p2*k2Q*e1e2 + 4*
    k1e1*e2Q*m2 - 8*k1e2*e1Q*m2 + 4*k1Q*e1e2*m2 + 8*k2e1*e2Q*
    m2 - 4*k2e2*e1Q*m2 - 4*k2Q*e1e2*m2;

  double t34 = 0;

  double term11 = c11*t11/den1 + c21*t21/den2 + c31*t31/den3;
  double term21 = c11*t12/den1 + c21*t22/den2 + c31*t32/den3;
  double term31 = c11*t13/den1 + c21*t23/den2 + c31*t33/den3;
  double term41 = c11*t14/den1 + c21*t24/den2 + c31*t34/den3;

  double term12 = c12*t11/den1 + c22*t21/den2 + c32*t31/den3;
  double term22 = c12*t12/den1 + c22*t22/den2 + c32*t32/den3;
  double term32 = c12*t13/den1 + c22*t23/den2 + c32*t33/den3;
  double term42 = c12*t14/den1 + c22*t24/den2 + c32*t34/den3;

  double term13 = c13*t11/den1 + c23*t21/den2 + c33*t31/den3;
  double term23 = c13*t12/den1 + c23*t22/den2 + c33*t32/den3;
  double term33 = c13*t13/den1 + c23*t23/den2 + c33*t33/den3;
  double term43 = c13*t14/den1 + c23*t24/den2 + c33*t34/den3;

  M2gg2qq = ( sqr(term11)/24.0 + sqr(term12)/12.0 + sqr(term13)/(20.0/3.0) )/norm1 +
            ( sqr(term21)/24.0 + sqr(term22)/12.0 + sqr(term23)/(20.0/3.0) )/norm2 +
            ( sqr(term31)/24.0 + sqr(term32)/12.0 + sqr(term33)/(20.0/3.0) )/norm3 +
            ( sqr(term41)/24.0 + sqr(term42)/12.0 + sqr(term43)/(20.0/3.0) )/norm4;

  M2gg2qq = sqr(4.0*PI*aQCD(muR2))*M2gg2qq/64.0;

  return max(M2gg2qq,0.0);
}
