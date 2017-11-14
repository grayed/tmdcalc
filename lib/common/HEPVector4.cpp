// HEPVector4.cpp
// Last modified 14.09.2017 by Artem Lipatov

#include <iostream>
#include <cmath>

#include "utils.h"
#include "HEPVector4.h"

using namespace std;

THEPVector4::THEPVector4(void)
{
  for (short int i = 0; i < 4; i++)
    entry[i] = 0.0;
}

double THEPVector4::get(unsigned short int i)
{
  return entry[i];
}

void THEPVector4::set(unsigned short int i, double store)
{
  entry[i] = store;
}

void THEPVector4::rotatearoundX(double costheta, double sintheta)
{
// positive rotation direction from Y axis to Z axis
  double y = entry[2];
  double z = entry[3];

  entry[2] = y*costheta - z*sintheta;
  entry[3] = y*sintheta + z*costheta;
}

void THEPVector4::rotatearoundY(double costheta, double sintheta)
{
// positive rotation direction from Z axis to X axis
  double x = entry[1];
  double z = entry[3];

  entry[3] = z*costheta - x*sintheta;
  entry[1] = z*sintheta + x*costheta;
}

void THEPVector4::rotatearoundZ(double costheta, double sintheta)
{
// positive direction from X axis to Y axis

  double x = entry[1];
  double y = entry[2];

  entry[1] = x*costheta - y*sintheta;
  entry[2] = x*sintheta + y*costheta;
}

void THEPVector4::boostalongX(double beta)
{
  double gamma = 1.0/sqrt(1.0 - sqr(beta));

  double t = entry[0];
  double x = entry[1];

  entry[1] = x*gamma - t*gamma*beta;
  entry[0] = t*gamma - x*gamma*beta;
}

void THEPVector4::boostalongY(double beta)
{
  double gamma = 1.0/sqrt(1.0 - sqr(beta));

  double t = entry[0];
  double y = entry[2];

  entry[2] = y*gamma - t*gamma*beta;
  entry[0] = t*gamma - y*gamma*beta;
}

void THEPVector4::boostalongZ(double beta)
{
  double gamma = 1.0/sqrt(1.0 - sqr(beta));

  double t = entry[0];
  double z = entry[3];

  entry[3] = z*gamma - t*gamma*beta;
  entry[0] = t*gamma - z*gamma*beta;
}

THEPVector4 & THEPVector4::operator = (const THEPVector4 & other)
{
  if (this != &other)
  {
    for (short int i = 0; i < 4; i++)
      entry[i] = other.entry[i];
  }

  return *this;
}

THEPVector4 THEPVector4::operator + (const THEPVector4 & other) const
{
  THEPVector4 HEPVector;

  for (unsigned short int i = 0; i < 4; i++)
    HEPVector.set(i, entry[i] + other.entry[i]);

  return HEPVector;
}

THEPVector4 THEPVector4::operator - (const THEPVector4 & other) const
{
  THEPVector4 HEPVector;

  for (unsigned short int i = 0; i < 4; i++)
    HEPVector.set(i, entry[i] - other.entry[i]);

  return HEPVector;
}

double THEPVector4::totalmomentum(void)
{
  return sqrt(totalmomentum2());
}

double THEPVector4::totalmomentum2(void)
{
  return sqr(entry[1]) + sqr(entry[2]) + sqr(entry[3]);
}

double THEPVector4::transversemomentum(void)
{
  return sqrt(transversemomentum2());
}

double THEPVector4::transversemomentum2(void)
{
  return sqr(entry[1]) + sqr(entry[2]);
}

double THEPVector4::transverseenergy(void)
{
  return entry[0]*transversemomentum()/totalmomentum();
}

double THEPVector4::rapidity(void)
{
  return 0.5*log((entry[0] + entry[3])/(entry[0] - entry[3]));
}

double THEPVector4::pseudorapidity(void)
{
  return ( - log(tan(0.5*acos(entry[3]/totalmomentum()))) );
}

double dot(THEPVector4 p1, THEPVector4 p2)
{
  return ( p1.get(0)*p2.get(0) - p1.get(1)*p2.get(1) - p1.get(2)*p2.get(2) - p1.get(3)*p2.get(3) );
}

double polarangle(THEPVector4 p1, THEPVector4 p2)
{
  double costheta = (p1.get(1)*p2.get(1) + p1.get(2)*p2.get(2) + p1.get(3)*p2.get(3))/(p1.totalmomentum()*p2.totalmomentum());

  if (costheta > 1.0) costheta = 1.0;
  if (costheta < - 1.0) costheta = - 1.0;

  return acos(costheta);
}

double azimuthalangle(THEPVector4 p1, THEPVector4 p2)
{
  double cosphi = (p1.get(1)*p2.get(1) + p1.get(2)*p2.get(2))/(p1.transversemomentum()*p2.transversemomentum());

  if (cosphi > 1.0) cosphi = 1.0;
  if (cosphi < - 1.0) cosphi = - 1.0;

  return acos(cosphi);
}

double invariantmass(THEPVector4 p1, THEPVector4 p2)
{
  return sqrt( dot(p1,p1) + dot(p2,p2) + 2.0*dot(p1,p2) );
}

double separation(THEPVector4 p1, THEPVector4 p2)
{
  return sqrt( sqr(p1.pseudorapidity() - p2.pseudorapidity()) + sqr(azimuthalangle(p1,p2)) );
}

void times(THEPVector4 p1, THEPVector4 p2, THEPVector4& k)
{
  k.set(0,0.0);
  k.set(1,p1.get(2)*p2.get(3) - p1.get(3)*p2.get(2));
  k.set(2,p1.get(3)*p2.get(1) - p1.get(1)*p2.get(3));
  k.set(3,p1.get(1)*p2.get(2) - p1.get(2)*p2.get(1));
}

void lc3(THEPVector4 p1, THEPVector4 p2, THEPVector4 p3, THEPVector4& k)
{
  double e0123 = 1.0;

  k.set(0,e0123*(p1.get(1)*p2.get(2)*p3.get(3) - p1.get(1)*p2.get(3)*p3.get(2) - p1.get(2)*p2.get(1)*p3.get(3) +
    p1.get(2)*p2.get(3)*p3.get(1) + p1.get(3)*p2.get(1)*p3.get(2) - p1.get(3)*p2.get(2)*p3.get(1)));

  k.set(1, - e0123*( - p1.get(0)*p2.get(2)*p3.get(3) + p1.get(0)*p2.get(3)*p3.get(2) + p1.get(2)*p2.get(0)*p3.get(3) -
    p1.get(2)*p2.get(3)*p3.get(0) - p1.get(3)*p2.get(0)*p3.get(2) + p1.get(3)*p2.get(2)*p3.get(0)));

  k.set(2, - e0123*(p1.get(0)*p2.get(1)*p3.get(3) - p1.get(0)*p2.get(3)*p3.get(1) - p1.get(1)*p2.get(0)*p3.get(3) +
    p1.get(1)*p2.get(3)*p3.get(0) + p1.get(3)*p2.get(0)*p3.get(1) - p1.get(3)*p2.get(1)*p3.get(0)));

  k.set(3, - e0123*( - p1.get(0)*p2.get(1)*p3.get(2) + p1.get(0)*p2.get(2)*p3.get(1) + p1.get(1)*p2.get(0)*p3.get(2) -
    p1.get(1)*p2.get(2)*p3.get(0) - p1.get(2)*p2.get(0)*p3.get(1) + p1.get(2)*p2.get(1)*p3.get(0)));
}

void chooseleading(THEPVector4 p1, THEPVector4 p2, THEPVector4& pl)
{
  pl = p1;

  if ( p1.transversemomentum() < p2.transversemomentum() ) pl = p2;
}

void chooseleading(THEPVector4 p1, THEPVector4 p2, THEPVector4 p3, THEPVector4& pl)
{
  THEPVector4 k;

  chooseleading(p1,p2,k);
  chooseleading(k,p3,pl);
}

void chooseleading(THEPVector4 p1, THEPVector4 p2, THEPVector4 p3, THEPVector4 p4, THEPVector4& pl)
{
  THEPVector4 k;

  chooseleading(p1,p2,p3,k);
  chooseleading(k,p4,pl);
}

void chooseleading2(THEPVector4 p1, THEPVector4 p2, THEPVector4& pl, THEPVector4& pnl)
{
  pl = p1;
  pnl = p2;

  if ( p1.transversemomentum() < p2.transversemomentum() )
  {
    pl = p2;
    pnl = p1;
  }
}

void chooseleading3(THEPVector4 p1, THEPVector4 p2, THEPVector4 p3, THEPVector4 p4, THEPVector4& pl, THEPVector4& pnl, THEPVector4& pnnl)
{
  chooseleading(p1,p2,p3,p4,pl);

  THEPVector4 k1, k2, k3;

  if (isequal(pl,p1) == true)
  {
    k1 = p2;
    k2 = p3;
    k3 = p4;
  }

  if (isequal(pl,p2) == true)
  {
    k1 = p1;
    k2 = p3;
    k3 = p4;
  }

  if (isequal(pl,p3) == true)
  {
    k1 = p1;
    k2 = p2;
    k3 = p4;
  }

  if (isequal(pl,p4) == true)
  {
    k1 = p1;
    k2 = p2;
    k3 = p3;
  }

  chooseleading(k1,k2,k3,pnl);

  THEPVector4 q1, q2;

  if (isequal(pnl,k1) == true)
  {
    q1 = k2;
    q2 = k3;
  }

  if (isequal(pnl,k2) == true)
  {
    q1 = k1;
    q2 = k3;
  }

  if (isequal(pnl,k3) == true)
  {
    q1 = k1;
    q2 = k2;
  }

  chooseleading(q1,q2,pnnl);
}

void chooseclosest2(THEPVector4 p, THEPVector4 p1, THEPVector4 p2, THEPVector4& k1, THEPVector4& k2)
{
  k1 = p1;
  k2 = p2;

  if ( separation(p,p1) > separation(p,p2) )
  {
    k1 = p2;
    k2 = p1;
  }
}

bool isisolated(THEPVector4 p1, THEPVector4 p2, double R, double Emax)
{
  if ( (separation(p1,p2) < R) and (p2.transverseenergy() > Emax) ) return false;
    else return true;
}

bool isseparated(THEPVector4 p1, THEPVector4 p2, double R)
{
  if (separation(p1,p2) < R) return false;
    else return true;
}

bool isequal(THEPVector4 p1, THEPVector4 p2)
{
  if ( (fabs(p1.get(0) - p2.get(0)) <= ZERO) and
       (fabs(p1.get(1) - p2.get(1)) <= ZERO) and
       (fabs(p1.get(2) - p2.get(2)) <= ZERO) and
       (fabs(p1.get(3) - p2.get(3)) <= ZERO) ) return true;
  else return false;
}
