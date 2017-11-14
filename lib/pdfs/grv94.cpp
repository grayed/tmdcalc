// grv94.cpp
// Last modified 29.08.2017 by Artem Lipatov

#include <cmath>
#include "../common/utils.h"

double grv94gLO(double x, double q2)
{
  if ( (x >= 1.0) or (x <= 0.0 ) ) return 0.0;

  double s = log(log(q2/sqr(0.2322))/log(0.23/sqr(0.2322)));
  double s2 = sqr(s);

  double a = 7.486 - 2.185*s;
  double b = 16.69 - 22.74*s + 5.779*s2;
  double c = - 25.59 + 29.71*s - 7.296*s2;
  double d = 2.792 + 2.215*s + 0.422*s2 - 0.104*s2*s;
  double e = 0.807 + 2.005*s;
  double f = 3.841 + 0.316*s;
  double l = log(1.0/x);

  return (pow(x, 1.742 - 0.930*s)*(a + x*(b + x*c))*pow(l, - 0.399*s2) +
    pow(s, 0.524)*exp( - e + sqrt(f*pow(s, 1.088)*l)))*pow(1.0 - x, d);
}

double grv94uvLO(double x, double q2)
{
  if ( (x >= 1.0) or (x <= 0.0) ) return 0.0;

  double s = log(log(q2/sqr(0.2322))/log(0.23/sqr(0.2322)));
  double s2 = sqr(s);

  double a = - 0.449 - 0.138*s - 0.076*s2;
  double b = 0.213 + 2.669*s - 0.728*s2;
  double c = 8.854 - 9.135*s + 1.979*s2;
  double d = 2.997 + 0.753*s - 0.076*s2;

  return (2.284 + 0.802*s + 0.055*s2)*pow(x, 0.590 - 0.024*s)*(1.0 + a*pow(x, 0.131 + 0.063*s) +
    x*(b + c*sqrt(x)))*pow(1.0 - x, d);
}

double grv94dvLO(double x, double q2)
{
  if ( (x >= 1.0) or (x <= 0.0) ) return 0.0;

  double s = log(log(q2/sqr(0.2322))/log(0.23/sqr(0.2322)));
  double s2 = sqr(s);

  double a = - 0.509 + 3.310*s - 1.248*s2;
  double b = 12.41 - 10.52*s + 2.267*s2;
  double c = 6.373 - 6.208*s + 1.418*s2;
  double d = 3.691 + 0.799*s - 0.071*s2;

  return (0.371 + 0.083*s + 0.039*s2)*pow(x, 0.376)*(1.0 + a*pow(x, 0.486 + 0.062*s) +
    x*(b + c*sqrt(x)))*pow(1.0 - x, d);
}

double grv94delLO(double x, double q2)
{
  if ( (x >= 1.0) or (x <= 0.0) ) return 0.0;

  double s = log(log(q2/sqr(0.2322))/log(0.23/sqr(0.2322)));
  double s2 = sqr(s);

  double a = - 38.07 + 36.13*s - 0.656*s2;
  double b = 90.31 - 74.15*s + 7.645*s2;
  double c = 0.0;
  double d = 7.486 + 1.217*s - 0.159*s2;

  return (0.082 + 0.014*s + 0.008*s2)*pow(x, 0.409 - 0.005*s)*(1.0 + a*pow(x, 0.799 + 0.071*s) +
    x*(b + c*sqrt(x)))*pow(1.0 - x, d);
}

double grv94udbLO(double x, double q2)
{
  if ( (x >= 1.0) or (x <= 0.0) ) return 0.0;

  double s = log(log(q2/sqr(0.2322))/log(0.23/sqr(0.2322)));
  double s2 = sqr(s);

  double a = 0.890 - 0.140*s;
  double b = - 0.981;
  double c = 0.320 + 0.683*s;
  double d = 4.752 + 1.164*s + 0.286*s2;
  double e = 4.119 + 1.713*s;
  double f = 0.682 + 2.978*s;
  double l = log(1.0/x);

  return (pow(x, 0.410 - 0.232*s)*(a + x*(b + x*c))*pow(l, 0.534 - 0.457*s) +
    pow(s, 1.451)*exp( - e + sqrt(f*pow(s, 0.271)*l)))*pow(1.0 - x, d);
}

double grv94sLO(double x, double q2)
{
  if ( (x >= 1.0) or (x <= 0.0) ) return 0.0;

  double s = log(log(q2/sqr(0.2322))/log(0.23/sqr(0.2322)));
  double s2 = sqr(s);

  double a = - 5.548 + 3.669*sqrt(s) - 0.616*s;
  double b = 18.92 - 16.73*sqrt(s) + 5.168*s;
  double d = 6.379 - 0.350*s + 0.142*s2;
  double e = 3.981 + 1.638*s;
  double f = 6.402;
  double l = log(1.0/x);

  return (pow(s, 0.914)/pow(l, 1.798 - 0.596*s))*(1.0 + a*sqrt(x) +
    b*x)*pow(1.0 - x, d)*exp( - e + sqrt(f*pow(s, 0.577)*l));
}

double grv94cLO(double x, double q2)
{
  if ( (x >= 1.0) or (x <= 0.0) ) return 0.0;

  double s = log(log(q2/sqr(0.232))/log(0.25/sqr(0.232)));

  if (s < 0.888) return 0.0;

  double a = 0.0;
  double b = 4.24 - 0.804*s;
  double d = 3.46 + 1.076*s;
  double e = 4.61 + 1.490*s;
  double f = 2.555 + 1.961*s;
  double l = log(1.0/x);

  return (pow(s - 0.888, 1.01)/pow(l, 0.0))*(1.0 + a*sqrt(x) +
    b*x)*pow(1.0 - x, d)*exp( - e + sqrt(f*pow(s, 0.37)*l));
}

double grv94bLO(double x, double q2)
{
  if ( (x >= 1.0) or (x <= 0.0) ) return 0.0;

  double s = log(log(q2/sqr(0.232))/log(0.25/sqr(0.232)));
  if (s < 1.351) return 0.0;

  double a = 0.0;
  double b = 1.848;
  double d = 2.929 + 1.396*s;
  double e = 4.71 + 1.514*s;
  double f = 4.02 + 1.239*s;
  double l = log(1.0/x);

  return (pow(s - 1.351, 1.00)/pow(l, 0.0))*(1.0 + a*sqrt(x) +
    b*x)*pow(1.0 - x, d)*exp( - e + sqrt(f*pow(s, 0.51)*l));
}
