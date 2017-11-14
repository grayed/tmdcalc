// HEPVector4.h
// Last modified 14.09.2017 by Artem Lipatov

#ifndef HEPVECTOR4_H
#define HEPVECTOR4_H

#include "utils.h"

using namespace std;

class THEPVector4 {
public:
  THEPVector4(void);

  double get(unsigned short int i);
  void set(unsigned short int i, double store);

  double totalmomentum(void);
  double totalmomentum2(void);
  double transverseenergy(void);
  double transversemomentum(void);
  double transversemomentum2(void);
  double rapidity(void);
  double pseudorapidity(void);

  void rotatearoundX(double costheta, double sintheta);
  void rotatearoundY(double costheta, double sintheta);
  void rotatearoundZ(double costheta, double sintheta);

  void boostalongX(double beta);
  void boostalongY(double beta);
  void boostalongZ(double beta);

  THEPVector4 & operator = (const THEPVector4 & other);
  THEPVector4 operator + (const THEPVector4 & other) const;
  THEPVector4 operator - (const THEPVector4 & other) const;

private:
  double entry[4];
};

extern double dot(THEPVector4 p1, THEPVector4 p2);
extern double polarangle(THEPVector4 p1, THEPVector4 p2);
extern double azimuthalangle(THEPVector4 p1, THEPVector4 p2);
extern double invariantmass(THEPVector4 p1, THEPVector4 p2);
extern double separation(THEPVector4 p1, THEPVector4 p2);

extern void chooseleading(THEPVector4 p1, THEPVector4 p2, THEPVector4& pl);
extern void chooseleading(THEPVector4 p1, THEPVector4 p2, THEPVector4 p3, THEPVector4& pl);
extern void chooseleading(THEPVector4 p1, THEPVector4 p2, THEPVector4 p3, THEPVector4 p4, THEPVector4& pl);
extern void chooseleading2(THEPVector4 p1, THEPVector4 p2, THEPVector4& pl, THEPVector4& pnl);
extern void chooseleading3(THEPVector4 p1, THEPVector4 p2, THEPVector4 p3, THEPVector4 p4, THEPVector4& pl, THEPVector4& pnl, THEPVector4& pnnl);

extern void chooseclosest2(THEPVector4 p, THEPVector4 p1, THEPVector4 p2, THEPVector4& k1, THEPVector4& k2);

extern void times(THEPVector4 p1, THEPVector4 p2, THEPVector4& k);
extern void lc3(THEPVector4 p1, THEPVector4 p2, THEPVector4 p3, THEPVector4& k);

extern bool isseparated(THEPVector4 p1, THEPVector4 p2, double R);
extern bool isisolated(THEPVector4 p1, THEPVector4 p2, double R, double Emax);
extern bool isequal(THEPVector4 p1, THEPVector4 p2);

#endif

