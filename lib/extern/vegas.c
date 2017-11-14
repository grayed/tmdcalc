// Program name: vegas.c
// Last modified: 04.04.2017
// Description: 
//   VEGAS integrating routine; G.P. Lepage; sept. 1976/(rev) apr. 1978
//   updated for Qt

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "nrutil.h"

#define ALPH 1.5
#define NDMX 50
#define MXDIM 10
#define TINY 1.0e-30

int ndim;                 // dimension
int itmx;                 // number of iterations
int init = 0;
unsigned long int calls;  // number of calls
double regn[2*MXDIM + 1]; // integration region
double tgral;             // best estimate of the integral
double chi2a;             // \xi^2 per degree of freedom
double sd;                // standard deviation

void vegas(double regn[], int ndim, double (*fxn)(double [], double), int init, unsigned long ncall, int itmx, double *tgral, double *sd, double *chi2a, void(*callback)(unsigned int, void *), void *pointer)
{
  void rebin(double rc, int nd, double r[], double xin[], double xi[]);
  static int i, it, j, k, mds, nd, ndo, ng, npg, ia[MXDIM + 1], kg[MXDIM + 1];
  static double calls, dv2g, dxg, f, f2, f2b, fb, rc, ti, tsi, wgt, xjac, xn, xnd, xo;
  static double d[NDMX + 1][MXDIM + 1], di[NDMX + 1][MXDIM + 1], dt[MXDIM + 1], dx[MXDIM + 1], r[NDMX + 1], x[MXDIM + 1], xi[MXDIM + 1][NDMX + 1], xin[NDMX + 1];
  static double schi, si, swgt;

  unsigned int iteration = 1;
  callback(iteration, pointer);

  if (init <= 0)
  {
    mds = ndo = 1;
    for (j = 1; j <= ndim; j++) xi[j][1] = 1.0;
  }

  if (init <= 1) si = swgt = schi = 0.0;

  if (init <= 2) 
  {
    nd = NDMX;
    ng = 1;

    if (mds)
    {
      ng = (int)pow(ncall/2.0 + 0.25,1.0/ndim);
      mds = 1;

      if ((2*ng - NDMX) >= 0)
      {
        mds = -1;
 	npg = ng/NDMX + 1;
	nd = ng/npg;
	ng = npg*nd;
      }
    }

    for (k = 1, i = 1; i <= ndim; i++)
      k *= ng;

    npg = IMAX(ncall/k,2);
    calls = npg*k;
    dxg = 1.0/ng;

    for (dv2g = 1, i = 1; i <= ndim; i++)
      dv2g *= dxg;

    dv2g = SQR(calls*dv2g)/npg/npg/(npg - 1.0);
    xnd = nd;
    dxg *= xnd;
    xjac = 1.0/calls;

    for (j = 1; j <= ndim; j++)
    {
      dx[j] = regn[j + ndim] - regn[j];
      xjac *= dx[j];
    }

    if (nd != ndo) 
    {
      for (i = 1; i <= nd; i++) r[i] = 1.0;
      for (j = 1; j <= ndim; j++) rebin(ndo/xnd,nd,r,xin,xi[j]);
      ndo = nd;
    }

  }

  for (it = 1; it <= itmx; it++) 
  {
    ti = tsi = 0.0;

    for (j = 1; j <= ndim; j++)
    {
      kg[j] = 1;
      for (i = 1; i <= nd; i++) d[i][j] = di[i][j] = 0.0;
    }

    for (;;) 
    {
      fb = f2b = 0.0;

      for (k = 1; k <= npg; k++)
      {
        wgt = xjac;
	for (j = 1; j <= ndim; j++)
        {
          xn = (kg[j] - rand()/(double)RAND_MAX)*dxg + 1.0;
          ia[j] = IMAX(IMIN((int)(xn),NDMX),1);
          if (ia[j] > 1)
          {
    	    xo = xi[j][ia[j]] - xi[j][ia[j]-1];
     	    rc = xi[j][ia[j]-1]+(xn - ia[j])*xo;
          } else { xo=xi[j][ia[j]]; rc=(xn - ia[j])*xo; }

     	  x[j] = regn[j] + rc*dx[j];
          wgt *= xo*xnd;
        }

	f = wgt*(*fxn)(x,wgt);
	f2 = f*f;
	fb += f;
	f2b += f2;

	for (j = 1; j <= ndim; j++)
        {
   	  di[ia[j]][j] += f;
  	  if (mds >= 0) d[ia[j]][j] += f2;
	}
      }  

      f2b = sqrt(f2b*npg);
      f2b = (f2b - fb)*(f2b + fb);
      if (f2b <= 0.0) f2b = TINY;
      ti += fb;
      tsi += f2b;

      if (mds < 0) 
      {
        for (j = 1; j <= ndim; j++) d[ia[j]][j] += f2b;
      }

      for (k = ndim; k >= 1; k--)
      {
        kg[k] %= ng;
	if (++kg[k] != 1) break;
      }

      if (k < 1) break;
    }

    tsi *= dv2g;
    wgt = 1.0/tsi;
    si += wgt*ti;
    schi += wgt*ti*ti;
    swgt += wgt;
    *tgral = si/swgt;
    *chi2a = (schi - si*(*tgral))/(it - 0.9999);
    if (*chi2a < 0.0) *chi2a = 0.0;
    *sd = sqrt(1.0/swgt);
    tsi = sqrt(tsi);

    iteration++;
    callback(iteration, pointer);

    for (j = 1; j <= ndim; j++)
    {
      xo = d[1][j];
      xn = d[2][j];
      d[1][j] = (xo + xn)/2.0;
      dt[j] = d[1][j];

      for (i = 2; i < nd; i++)
      {
        rc = xo + xn;
	xo = xn;
	xn = d[i+1][j];
	d[i][j] = (rc+xn)/3.0;
	dt[j] += d[i][j];
      }

      d[nd][j] = (xo + xn)/2.0;
      dt[j] += d[nd][j];
    }

    for (j = 1; j <= ndim; j++)
    {
      rc = 0.0;
      for (i = 1; i <= nd; i++)
      {
	if (d[i][j] < TINY) d[i][j] = TINY;
	r[i] = pow((1.0 - d[i][j]/dt[j])/(log(dt[j]) - log(d[i][j])),ALPH);
	rc += r[i];
      }
      rebin(rc/xnd,nd,r,xin,xi[j]);
    }
  }

}

void rebin(double rc, int nd, double r[], double xin[], double xi[])
{
  int i, k = 0;
  double dr = 0.0, xn = 0.0, xo = 0.0;

  for (i = 1; i < nd; i++)
  {
    while (rc > dr) dr += r[++k];
    if (k > 1) xo = xi[k-1];
    xn = xi[k];
    dr -= rc;
    xin[i] = xn - (xn - xo)*dr/r[k];
  }

  for (i = 1; i < nd; i++) xi[i] = xin[i];
  xi[nd] = 1.0;
}

#undef ALPH
#undef NDMX
#undef MXDIM
#undef TINY
