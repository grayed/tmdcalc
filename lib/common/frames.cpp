/*
 * (c) Artem Lipatov, 2017
 */

// frames.cpp
// Last modified 04.09.2017 by Artem Lipatov

#include <cmath>

#include "utils.h"
#include "frames.h"

THEPVector4 H;
THEPVector4 beam1;
THEPVector4 beam2;

void cm2hl(THEPVector4 pcm, THEPVector4& phl)
{
  THEPVector4 p, q, k;
  THEPVector4 p1, p2;

  p = pcm;
  q = H;

  p1 = beam1;
  p2 = beam2;

  const double cosphi = q.get(1)/q.transversemomentum();
  const double sinphi = q.get(2)/q.transversemomentum();

// rotation in XY plane by - phi

  p.rotatearoundZ(cosphi,-sinphi);
  q.rotatearoundZ(cosphi,-sinphi);
  p1.rotatearoundZ(cosphi,-sinphi);
  p2.rotatearoundZ(cosphi,-sinphi);

  const double costheta = q.get(1)/q.totalmomentum();
  const double sintheta = q.get(3)/q.totalmomentum();

// rotation in XZ plane by theta - PI/2

  p.rotatearoundY(-sintheta,costheta);
  q.rotatearoundY(-sintheta,costheta);
  p1.rotatearoundY(-sintheta,costheta);
  p2.rotatearoundY(-sintheta,costheta);

  const double beta = q.totalmomentum()/q.get(0);

// Lorents boost along Z axis

  p.boostalongZ(beta);
  q.boostalongZ(beta);
  p1.boostalongZ(beta);
  p2.boostalongZ(beta);

  phl = p;
}

void cm2tg(THEPVector4 pcm, THEPVector4& ptg)
{
  THEPVector4 p, q, l, k;
  THEPVector4 p1, p2;

  p = pcm;
  q = H;

  p1 = beam1;
  p2 = beam2;

  const double cosphi = q.get(1)/q.transversemomentum();
  const double sinphi = q.get(2)/q.transversemomentum();

// rotation in XY plane by - phi

  p.rotatearoundZ(cosphi,-sinphi);
  q.rotatearoundZ(cosphi,-sinphi);
  p1.rotatearoundZ(cosphi,-sinphi);
  p2.rotatearoundZ(cosphi,-sinphi);

  const double costheta = q.get(1)/q.totalmomentum();
  const double sintheta = q.get(3)/q.totalmomentum();

// rotation in XZ plane by theta

  p.rotatearoundY(costheta,sintheta);
  q.rotatearoundY(costheta,sintheta);
  p1.rotatearoundY(costheta,sintheta);
  p2.rotatearoundY(costheta,sintheta);

  const double beta = q.totalmomentum()/q.get(0);

// Lorents boost along X axis

  p.boostalongX(beta);
  p1.boostalongX(beta);
  p2.boostalongX(beta);

  l.set(0,0.0);
  l.set(1,- p1.get(1));
  l.set(2,- p1.get(2));
  l.set(3,- p1.get(3));

// definition of Z' axis along vector l
// note l lies in XZ plane

  const double cosdelta = l.get(1)/l.totalmomentum();
  const double sindelta = l.get(3)/l.totalmomentum();

// rotation in XZ plane by delta - PI/2

  p.rotatearoundY(-sindelta,cosdelta);
  p1.rotatearoundY(-sindelta,cosdelta);
  p2.rotatearoundY(-sindelta,cosdelta);

// definition of Y' axis along vector k

  times(p1,p2,k);

  const double cospsi = k.get(1)/k.transversemomentum();
  const double sinpsi = k.get(2)/k.transversemomentum();

// rotation in XY plane by - psi

  p.rotatearoundZ(cospsi,-sinpsi);

  ptg = p;
}

void cm2cs(THEPVector4 pcm, THEPVector4& pcs)
{
  THEPVector4 p, q, k, l;
  THEPVector4 n1, n2, n3;
  THEPVector4 p1, p2;

  p = pcm;
  q = H;

  p1 = beam1;
  p2 = beam2;

  const double cosphi = q.get(1)/q.transversemomentum();
  const double sinphi = q.get(2)/q.transversemomentum();

// rotation in XY plane by - phi

  p.rotatearoundZ(cosphi,-sinphi);
  q.rotatearoundZ(cosphi,-sinphi);
  p1.rotatearoundZ(cosphi,-sinphi);
  p2.rotatearoundZ(cosphi,-sinphi);

  const double costheta = q.get(1)/q.totalmomentum();
  const double sintheta = q.get(3)/q.totalmomentum();

// rotation in XZ plane by theta

  p.rotatearoundY(costheta,sintheta);
  q.rotatearoundY(costheta,sintheta);
  p1.rotatearoundY(costheta,sintheta);
  p2.rotatearoundY(costheta,sintheta);

  const double beta = q.totalmomentum()/q.get(0);

// Lorents boost along X axis

  p.boostalongX(beta);
  q.boostalongX(beta);
  p1.boostalongX(beta);
  p2.boostalongX(beta);

  double norm1 = p1.totalmomentum();
  double norm2 = p2.totalmomentum();

  n1.set(0,0.0);
  n1.set(1,p1.get(1)/norm1);
  n1.set(2,p1.get(2)/norm1);
  n1.set(3,p1.get(3)/norm1);

  n2.set(0,0.0);
  n2.set(1,p2.get(1)/norm2);
  n2.set(2,p2.get(2)/norm2);
  n2.set(3,p2.get(3)/norm2);

  n3.set(0,0.0);
  n3.set(1,n1.get(1) - n2.get(1));
  n3.set(2,n1.get(2) - n2.get(2));
  n3.set(3,n1.get(3) - n2.get(3));

// definition of Z' axis along vector n3 (bisector of proton1 and - proton2 momenta)
// note n3 lies in XZ plane

  const double cosdelta = n3.get(1)/n3.totalmomentum();
  const double sindelta = n3.get(3)/n3.totalmomentum();

// rotation in XZ plane delta - PI/2
// note n3 lies in XZ plane

  p.rotatearoundY(-sindelta,cosdelta);
  p1.rotatearoundY(-sindelta,cosdelta);
  p2.rotatearoundY(-sindelta,cosdelta);

  pcs = p;
}

void cm2pl(THEPVector4 pcm, THEPVector4& ppl)
{
  THEPVector4 p, q, k, l;
  THEPVector4 n1, n2, n3;
  THEPVector4 p1, p2;

  p = pcm;
  q = H;

  p1 = beam1;
  p2 = beam2;

  const double cosphi = q.get(1)/q.transversemomentum();
  const double sinphi = q.get(2)/q.transversemomentum();

// rotation in XY plane by - phi

  p.rotatearoundZ(cosphi,-sinphi);
  q.rotatearoundZ(cosphi,-sinphi);
  p1.rotatearoundZ(cosphi,-sinphi);
  p2.rotatearoundZ(cosphi,-sinphi);

  const double costheta = q.get(1)/q.totalmomentum();
  const double sintheta = q.get(3)/q.totalmomentum();

// rotation in XZ plane by theta

  p.rotatearoundY(costheta,sintheta);
  q.rotatearoundY(costheta,sintheta);
  p1.rotatearoundY(costheta,sintheta);
  p2.rotatearoundY(costheta,sintheta);

  const double beta = q.totalmomentum()/q.get(0);

// Lorents boost along X axis

  p.boostalongX(beta);
  q.boostalongX(beta);
  p1.boostalongX(beta);
  p2.boostalongX(beta);

  double norm1 = p1.totalmomentum();
  double norm2 = p2.totalmomentum();

  n1.set(0,0.0);
  n1.set(1,p1.get(1)/norm1);
  n1.set(2,p1.get(2)/norm1);
  n1.set(3,p1.get(3)/norm1);

  n2.set(0,0.0);
  n2.set(1,p2.get(1)/norm2);
  n2.set(2,p2.get(2)/norm2);
  n2.set(3,p2.get(3)/norm2);

  n3.set(0,0.0);
  n3.set(1,n1.get(1) - n2.get(1));
  n3.set(2,n1.get(2) - n2.get(2));
  n3.set(3,n1.get(3) - n2.get(3));

// definition of Z' axis along vector n3 (bisector of proton1 and - proton2 momenta)
// note n3 lies in XZ plane

  const double cosdelta = n3.get(1)/n3.totalmomentum();
  const double sindelta = n3.get(3)/n3.totalmomentum();

// rotation in XZ plane by delta - PI/2
// note n3 lies in XZ plane

  p.rotatearoundY(-sindelta,cosdelta);
  p1.rotatearoundY(-sindelta,cosdelta);
  p2.rotatearoundY(-sindelta,cosdelta);

// rotation in XZ plane by PI/2

  p.rotatearoundY(0.0,1.0);
  p1.rotatearoundY(0.0,1.0);
  p2.rotatearoundY(0.0,1.0);

  ppl = p;
}

void cm2z(THEPVector4 pcm, THEPVector4& pz)
{
  THEPVector4 p, q;

  p = pcm;
  q = H;

  const double cosphi = q.get(1)/q.transversemomentum();
  const double sinphi = q.get(2)/q.transversemomentum();

// rotation in XY plane by - phi

  p.rotatearoundZ(cosphi,-sinphi);
  q.rotatearoundZ(cosphi,-sinphi);

  const double costheta = q.get(1)/q.totalmomentum();
  const double sintheta = q.get(3)/q.totalmomentum();

// rotation in XZ plane by theta - PI/2

  p.rotatearoundY(-sintheta,costheta);

  pz = p;
}

void z2cm(THEPVector4 pz, THEPVector4& pcm)
{
  THEPVector4 p, q;

  p = pz;
  q = H;

  const double cosphi = q.get(1)/q.transversemomentum();
  const double sinphi = q.get(2)/q.transversemomentum();

// rotation in XY plane by - phi

  q.rotatearoundZ(cosphi,-sinphi);

  const double costheta = q.get(1)/q.totalmomentum();
  const double sintheta = q.get(3)/q.totalmomentum();

// rotation in XZ plane by theta - PI/2

  p.rotatearoundY(-sintheta,costheta);

// rotation in XY plane by PI + phi

  p.rotatearoundZ(-cosphi,-sinphi);

  pcm = p;
}

void cm2rf(THEPVector4 pcm, THEPVector4& prf)
{
  THEPVector4 p, q;

  p = pcm;
  q = H;

  const double cosphi = q.get(1)/q.transversemomentum();
  const double sinphi = q.get(2)/q.transversemomentum();

// rotation in XY plane by - phi

  p.rotatearoundZ(cosphi,-sinphi);
  q.rotatearoundZ(cosphi,-sinphi);

  const double costheta = q.get(1)/q.totalmomentum();
  const double sintheta = q.get(3)/q.totalmomentum();

// rotation in XZ plane by theta

  p.rotatearoundY(costheta,sintheta);
  q.rotatearoundY(costheta,sintheta);

  const double beta = q.totalmomentum()/q.get(0);

// Lorents boost along X axis

  p.boostalongX(beta);

  prf = p;
}

void rf2cm(THEPVector4 prf, THEPVector4& pcm)
{
  THEPVector4 q, p;

  p = prf;
  q = H;

  const double beta = - q.totalmomentum()/q.get(0);

// Lorents boost along X axis

  p.boostalongX(beta);

  const double cosphi = q.get(1)/q.transversemomentum();
  const double sinphi = q.get(2)/q.transversemomentum();

  q.rotatearoundZ(cosphi,-sinphi);

  const double costheta = q.get(1)/q.totalmomentum();
  const double sintheta = q.get(3)/q.totalmomentum();

  p.rotatearoundY(costheta,-sintheta);
  p.rotatearoundZ(cosphi,sinphi);

  pcm = p;
}

