/*
 * (c) Artem Lipatov, 2017
 */

// pdf.cpp
// Last modified 04.09.2017 by Artem Lipatov

#include <cmath>

#include "pdf.h"
#include "grv94.h"

using namespace std;

pdf::pdf(TPDF id)
{
  if ( (id == AZERO) or (id == JH2013set1) or (id == JH2013set2) ) exit(0);

  pdfset = id;
  isFileLoaded = false;

  if (pdfset == GRV94LO) isFileLoaded = true;
}

pdf::pdf(TPDF id, string filename)
{
  if ( (id == AZERO) or (id == JH2013set1) or (id == JH2013set2) ) exit(0);

  pdfset = id;

  if (pdfset == MSTW2008LO) mstw = new c_mstwpdf(filename);
  if (pdfset == MSTW2008NLO) mstw = new c_mstwpdf(filename);
  if (pdfset == CTEQ66) cteq66.setct11(filename);

  isFileLoaded = true;
}

pdf::~pdf()
{
  if (pdfset == MSTW2008LO) delete mstw;
  if (pdfset == MSTW2008NLO) delete mstw;
  if (pdfset == CTEQ66) cteq66.pdfexit();
}

double pdf::gluon(double x, double q2)
{
  double q = sqrt(q2);
  double density = 0.0;

  if (pdfset == GRV94LO) density = grv94gLO(x,q2);
  if (pdfset == MSTW2008LO) density = mstw->parton(0,x,q);
  if (pdfset == MSTW2008NLO) density = mstw->parton(0,x,q);
  if (pdfset == CTEQ66) density = x*cteq66.parton(0,x,q);

  return density;
}

double pdf::uv(double x, double q2)
{
  double q = sqrt(q2);
  double density = 0.0;

  if (pdfset == GRV94LO) density = grv94uvLO(x,q2);
  if (pdfset == MSTW2008LO) density = mstw->parton(8,x,q);
  if (pdfset == MSTW2008NLO) density = mstw->parton(8,x,q);
  if (pdfset == CTEQ66) density = u(x,q2) - ubar(x,q2);

  return density;
}

double pdf::ubar(double x, double q2)
{
  double q = sqrt(q2);
  double density = 0.0;

  if (pdfset == GRV94LO) density = 0.5*(grv94udbLO(x,q2) - grv94delLO(x,q2));
  if (pdfset == MSTW2008LO) density = mstw->parton(-2,x,q);
  if (pdfset == MSTW2008NLO) density = mstw->parton(-2,x,q);
  if (pdfset == CTEQ66) density = x*cteq66.parton(-1,x,q);

  return density;
}

double pdf::u(double x, double q2)
{
  double q = sqrt(q2);
  double density = 0.0;

  if (pdfset == GRV94LO) density = uv(x,q2) + ubar(x,q2);
  if (pdfset == MSTW2008LO) density = mstw->parton(2,x,q);
  if (pdfset == MSTW2008NLO) density = mstw->parton(2,x,q);
  if (pdfset == CTEQ66) density = x*cteq66.parton(1,x,q);

  return density;
}

double pdf::dv(double x, double q2)
{
  double q = sqrt(q2);
  double density = 0.0;

  if (pdfset == GRV94LO) density = grv94dvLO(x,q2);
  if (pdfset == MSTW2008LO) density = mstw->parton(7,x,q);
  if (pdfset == MSTW2008NLO) density = mstw->parton(7,x,q);
  if (pdfset == CTEQ66) density = d(x,q2) - dbar(x,q2);

  return density;
}

double pdf::dbar(double x, double q2)
{
  double q = sqrt(q2);
  double density = 0.0;

  if (pdfset == GRV94LO) density = 0.5*(grv94udbLO(x,q2) + grv94delLO(x,q2));
  if (pdfset == MSTW2008LO) density = mstw->parton(-1,x,q);
  if (pdfset == MSTW2008NLO) density = mstw->parton(-1,x,q);
  if (pdfset == CTEQ66) density = x*cteq66.parton(-2,x,q);

  return density;
}

double pdf::d(double x, double q2)
{
  double q = sqrt(q2);
  double density = 0.0;

  if (pdfset == GRV94LO) density = dv(x,q2) + dbar(x,q2);
  if (pdfset == MSTW2008LO) density = mstw->parton(1,x,q);
  if (pdfset == MSTW2008NLO) density = mstw->parton(1,x,q);
  if (pdfset == CTEQ66) density = x*cteq66.parton(2,x,q);

  return density;
}

double pdf::s(double x, double q2)
{
  double q = sqrt(q2);
  double density = 0.0;

  if (pdfset == GRV94LO) density = grv94sLO(x,q2);
  if (pdfset == MSTW2008LO) density = mstw->parton(3,x,q);
  if (pdfset == MSTW2008NLO) density = mstw->parton(3,x,q);
  if (pdfset == CTEQ66) density = x*cteq66.parton(3,x,q);

  return density;
}

double pdf::c(double x, double q2)
{
  double q = sqrt(q2);
  double density = 0.0;

  if (pdfset == GRV94LO) density = grv94cLO(x,q2);
  if (pdfset == MSTW2008LO) density = mstw->parton(4,x,q);
  if (pdfset == MSTW2008NLO) density = mstw->parton(4,x,q);
  if (pdfset == CTEQ66) density = x*cteq66.parton(4,x,q);

  return density;
}

double pdf::b(double x, double q2)
{
  double q = sqrt(q2);
  double density = 0.0;

  if (pdfset == GRV94LO) density = grv94bLO(x,q2);
  if (pdfset == MSTW2008LO) density = mstw->parton(5,x,q);
  if (pdfset == MSTW2008NLO) density = mstw->parton(5,x,q);
  if (pdfset == CTEQ66) density = x*cteq66.parton(5,x,q);

  return density;
}
