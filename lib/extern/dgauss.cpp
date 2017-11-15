/*
 * Copyright (c) 2017 Artem Lipatov <artem.lipatov@mail.ru>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

// Unit name: dgauss.cpp
// Last modified: 28.08.2013
// Description:
//   A CERNLIB gauss-based method C++ integrating routine translated from FORTRAN code

#include <iostream>
#include <math.h>
#include "dgauss.h"

using namespace std;

double dgauss(double (*f)(double), double a, double b, double eps)
{ 
  double x[13] = {0.0, 9.6028985649753623e-01, 7.9666647741362674e-01, 
    5.2553240991632899e-01, 1.8343464249564980e-01, 9.8940093499164993e-01,
    9.4457502307323258e-01, 8.6563120238783174e-01, 7.5540440835500303e-01,
    6.1787624440264375e-01, 4.5801677765722739e-01, 2.8160355077925891e-01, 
    9.5012509837637440e-02};

  double w[13] = {0.0, 1.0122853629037626e-01, 2.2238103445337447e-01,
    3.1370664587788729e-01, 3.6268378337836198e-01, 2.7152459411754095e-02,
    6.2253523938647893e-02, 9.5158511682492785e-02, 1.2462897125553387e-01,
    1.4959598881657673e-01, 1.6915651939500254e-01, 1.8260341504492359e-01,
    1.8945061045506850e-01};

  double tgral; 
  double a1, b1, c, c1, c2, s8, s16, u;

  tgral = 0.0;
  if (b == a) return tgral;
  c = 0.005/(b - a);
  b1 = a;

label1: 
  a1 = b1;
  b1 = b;
label2:
  c1 = 0.5*(b1 + a1);
  c2 = 0.5*(b1 - a1);

  s8 = 0.0;
  for (int i = 1; i <= 4; i++)
  { 
    u = c2*x[i];
    s8 = s8 + w[i]*(f(c1 + u) + f(c1 - u));
  }

  s8 = c2*s8;
  s16 = 0.0;
  for (int i = 5; i <= 12; i++)
  { 
    u = c2*x[i];
    s16 = s16 + w[i]*(f(c1 + u) + f(c1 - u));
  }

  s16 = c2*s16;
  if ( fabs(s16 - s8) <= eps*(1.0 + fabs(s16)) ) goto label3;

  b1 = c1;
  if ( 1.0 + fabs(c*c2) != 1.0 ) goto label2;

  tgral = 0.0;
  cout << "Warning ('dgauss' function): too high accuracy required. Zero result returned.\n";
  return tgral;

label3:
  tgral = tgral + s16;
  if (b1 != b) goto label1;

  return tgral;
}

