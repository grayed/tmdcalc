/*
 * (c) Artem Lipatov, 2017
 */

// utils.cpp
// Last modified 07.11.2017 by Artem Lipatov

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include "SM.h"
#include "utils.h"

using namespace std;

TFactorization Factorization = TMD;
TCollision Collision = pp;
THardScale FactorizationScale = SubprocessEnergy;
THardScale RenormalizationScale = SubprocessEnergy;
TScaleRate ScaleRate = DefaultScale;
TPDF PDF = AZERO;

double Ecm = 7000.0;  // [GeV]

double g[4][4] = { 1.0, 0.0, 0.0, 0.0,
                   0.0,-1.0, 0.0, 0.0,
                   0.0, 0.0,-1.0, 0.0,
                   0.0, 0.0, 0.0,-1.0 };

unsigned long int nIterations = 20;
unsigned long int nEventsPerIteration = 600000;

double aQED(void)
{
  return 1.0/137.0;
}

double aQED(double q2)
{
  if (isaQEDrun == false) return aQED();
    else return 3.0/(3.0/(5.0*aQED()) - (41.0/10.0)*log(q2/sqr(mE))/(4.0*PI))/5.0;
}

double aQCD(double q2)
{
  if (isaQCDHO == false) return aQCDLO(q2);
    else return aQCDHO(q2);
}

double aQCDSS(double q2)
{
  double b0 = 11.0 - 2.0*NF/3.0;
  double LQCD2 = sqr(LQCD);

  return (4.0*PI/b0)*(1.0/log(q2/LQCD2) + LQCD2/(LQCD2 - q2));
}

double aQCDLO(double q2)
{
  return 4.0*PI/((11.0 - 2.0*NF/3.0)*log(q2/sqr(LQCD)));
}

double aQCDHO(double q2)
{
  double b0 = (33.0 - 2.0*NF)/(12.0*PI);
  double b1 = (153.0 - 19.0*NF)/(24.0*sqr(PI));
  double b2 = 0.0;
  double b3 = 0.0;

  double t = log(q2/sqr(LQCD));

  return (1.0/(b0*t))*( 1.0 - (b1/sqr(b0))*log(t)/t +
    (sqr(b1)*(sqr(log(t)) - log(t) - 1.0) + b0*b2)/(pow(b0,4)*sqr(t)) -
    (pow(b1,3)*(pow(log(t),3) - 2.5*sqr(log(t)) - 2.0*log(t) + 0.5) + 3*b0*b1*b2*log(t) - 0.5*sqr(b0)*b3)/(pow(b0,6)*pow(t,3)) );
}

double L(double x, double y, double z)
{
  return x*x + y*y + z*z - 2.0*x*y - 2.0*x*z - 2.0*y*z;
}

double G(double x, double y, double z, double u, double v, double w)
{
  return x*z*w + x*u*v + y*z*v + y*u*w - x*y*(z + u + v + w - x - y) -
    z*u*(x + y + v + w - z - u) - v*w*(x + y + z + u - v - w);
}

double Pgg(double z)
{
  return 2.0*NC*(z/(1.0 - z) - 1.0 + 1.0/z + z*(1.0 - z));
}

double Pgq(double z)
{
  return (4.0/3.0)*(1.0 + sqr(1.0 - z))/z;
}

double Pqg(double z)
{
  return (sqr(z) + sqr(1.0 - z))/2.0;
}

double Pqq(double z)
{
  return (4.0/3.0)*(1.0 + sqr(z))/(1.0 - z);
}

double zPgg(double z)
{
  return z*Pgg(z);
}

double sqr(double x)
{
  return x*x;
}

double max(double x, double y)
{
  double z = x;
  if (y > x) z = y;

  return z;
}

double min(double x, double y)
{
  double z = x;
  if (y < x) z = y;

  return z;
}

double heaviside(double x)
{
 if (x >= 0.0) return 1.0;
   else return 0.0;
}

double approximatedeulergamma(double x)
{
  double p[] = { -1.71618513886549492533811e+0,
                 2.47656508055759199108314e+1,
                 -3.79804256470945635097577e+2,
                 6.29331155312818442661052e+2,
                 8.66966202790413211295064e+2,
                 -3.14512729688483675254357e+4,
                 -3.61444134186911729807069e+4,
                 6.64561438202405440627855e+4 };

  double q[] = { -3.08402300119738975254353e+1,
                 3.15350626979604161529144e+2,
                 -1.01515636749021914166146e+3,
                 -3.10777167157231109440444e+3,
                 2.25381184209801510330112e+4,
                 4.75584627752788110767815e+3,
                 -1.34659959864969306392456e+5,
                 -1.15132259675553483497211e+5 };

  double z = x - 1.0;
  double a = 0.0;
  double b = 1.0;

  for(unsigned short int i = 0; i < 8; i++)
  {
    a = ( a + p[i])*z;
    b = b*z + q[i];
  }

  return (a/b + 1.0);
}

double eulergamma(double x)
{

  if ( (x > 0.0) and (x < 1.0)) return eulergamma(x + 1.0)/x;
  if (x > 2.0) return (x - 1.0)*eulergamma(x - 1.0);
  if (x <= 0.0) return PI/(sin(PI*x)*eulergamma(1.0 - x));

  return approximatedeulergamma(x);
}

void randomize(void)
{
  srand(time(NULL));
}

double random(double x, double y)
{
  return (y - x)*rand()/RAND_MAX + x;
}

void assist(void)
{
  switch (PDF)
  {
    case GRV94LO:     NF = 4;
                      LQCD = 0.2;
                      isaQCDHO = false;
                      break;

    case MSTW2008LO:  NF = 4;
                      LQCD = 0.2;
                      isaQCDHO = false;
                      break;

    case MSTW2008NLO: NF = 5;
                      LQCD = 0.2262;
                      isaQCDHO = true;
                      break;

    case CTEQ66:      NF = 5;
                      LQCD = 0.2262;
                      isaQCDHO = true;
                      break;

    case AZERO:       NF = 4;
                      LQCD = 0.2;
                      isaQCDHO = false;
                      FactorizationScale = SubprocessEnergyPlusPairTransverseMomentum;
                      break;

    case JH2013set1:  NF = 4;
                      LQCD = 0.2;
                      isaQCDHO = true;
                      FactorizationScale = SubprocessEnergyPlusPairTransverseMomentum;
                      break;

    case JH2013set2:  NF = 4;
                      LQCD = 0.2;
                      isaQCDHO = true;
                      FactorizationScale = SubprocessEnergyPlusPairTransverseMomentum;
                      break;

    case KMR:         NF = 4;
                      LQCD = 0.2;
                      isaQCDHO = false;
                      break;
  }
}
