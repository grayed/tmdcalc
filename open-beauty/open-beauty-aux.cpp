#include <cmath>
#include "../lib/common/utils.h"
#include "../lib/common/HEPVector4.h"
#include "../lib/common/histogram.h"

double minlBeautyTransverseMomentum = 0.0;
double maxlBeautyTransverseMomentum = 500.0;
double minlBeautyRapidity = - 7.0;
double maxlBeautyRapidity = 7.0;
double minlBeautyPseudoRapidity = - 7.0;
double maxlBeautyPseudoRapidity = 7.0;

double minnlBeautyTransverseMomentum = 0.0;
double maxnlBeautyTransverseMomentum = 500.0;
double minnlBeautyRapidity = - 7.0;
double maxnlBeautyRapidity = 7.0;
double minnlBeautyPseudoRapidity = - 7.0;
double maxnlBeautyPseudoRapidity = 7.0;

double minBeautyPairInvariantMass = 0.0;
double maxBeautyPairInvariantMass = 1000.0;

double minBeautyPairAzimuthalAngle = 0.0;
double maxBeautyPairAzimuthalAngle = PI;

THistogram hbTransverseMomentum = THistogram(0.0, 100.0, 50, "b-transverse-momentum.dat");
THistogram hbRapidity = THistogram(-7.0, 7.0, 50, "b-rapidity.dat");
THistogram hbbInvariantMass = THistogram(0.0, 1000.0, 50, "bb-invariant-mass.dat");
THistogram hbbAzimuthalAngle = THistogram(0.0, PI, 50, "bb-azimuthal-angle.dat");

void putOpenBeautyEvent(THEPVector4 p1, THEPVector4 p2, double store)
{
  THEPVector4 pl, pnl;
  chooseleading2(p1,p2,pl,pnl);

  double ptl = pl.transversemomentum();
  double yl = pl.rapidity();

  double ptnl = pnl.transversemomentum();
  double ynl = pnl.rapidity();

  double M = invariantmass(p1,p2);
  double dphi = azimuthalangle(p1,p2);

  if ( (ptl >= minlBeautyTransverseMomentum) and (ptl <= maxlBeautyTransverseMomentum) and
       (yl >= minlBeautyRapidity) and (yl <= maxlBeautyRapidity) and
       (ptnl >= minnlBeautyTransverseMomentum) and (ptnl <= maxnlBeautyTransverseMomentum) and
       (ynl >= minnlBeautyRapidity) and (ynl <= maxnlBeautyRapidity) and
       (M >= minBeautyPairInvariantMass) and (M <= maxBeautyPairInvariantMass) and
       (dphi >= minBeautyPairAzimuthalAngle) and (dphi <= maxBeautyPairAzimuthalAngle) )
  {
    hbTransverseMomentum.put(pl.transversemomentum(),store);
    hbRapidity.put(pl.rapidity(),store);
    hbbInvariantMass.put(M,store);
    hbbAzimuthalAngle.put(dphi,store);
  }
}

void saveOpenBeautyOutput(void)
{
  hbTransverseMomentum.saveAsHistogram("b-transverse-momentum.dat");
  hbRapidity.saveAsHistogram("b-rapidity.dat");
}
