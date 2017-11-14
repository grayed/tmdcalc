// SM.cpp
// Last modified 12.10.2017 by Artem Lipatov

#include "SM.h"

const double GF = 1.16639e-05;   // GeV^{-2}
const double MPL = 1.220896e+19; // Planck mass, GeV
const double sinwma2 = 0.23116;  // sin of Weinberg angle [squared]

const unsigned short int NC = 3;

double LQCD = 0.200; // QCD scale, GeV

bool isaQCDHO = true;
bool isaQEDrun = true;

unsigned short int NF = 4;

double mU = 0.0045; // up mass, GeV
double mD = 0.0085; // down mass, GeV
double mS = 0.155;  // strange mass, GeV
double mC = 1.4;    // charm mass, GeV
double mB = 4.75;   // beauty mass, GeV
double mT = 172.0;  // top mass, GeV

const double eU = 2.0/3.0;
const double eD = - 1.0/3.0;
const double eS = - 1.0/3.0;
const double eC = 2.0/3.0;
const double eB = - 1.0/3.0;
const double eT = 2.0/3.0;

double mE = 0.000511; // electron mass, GeV
double mMu = 0.105;   // muon mass, GeV
double mW = 80.403;   // W mass, GeV
double mZ = 91.1876;  // Z mass, GeV
double mH = 125.0;    // Higgs mass, GeV

double fdwZ = 2.4952;  // Z full decay width, GeV
double fdwW = 2.085;   // W full decay width, GeV
double fdwH = 4.3e-03; // Higgs full decay width, GeV

const double I3uct = 1.0/2.0;   // weak isospin (u, c, t)
const double I3dsb = - 1.0/2.0; // weak isospin (d, s, b)

const double BRb2B = 0.398;       // b -> B branching
const double BRc2D = 0.255;       // c -> D branching

const double BRB2JPSI = 0.0068383;  // B -> J/Psi + X branching
const double BRB2PSI2S = 0.0017504; // B -> J/Psi + X branching
const double BRB2CHIc0 = 0.00015;   // B -> chic0 + X branching
const double BRB2CHIc1 = 0.002084;  // B -> chic1 + X branching
const double BRB2CHIc2 = 0.000261;  // B -> chic2 + X branching

const double BRJPSI2ll = 0.05961;   // J/Psi -> ll branching
const double BRPSI2S2ll = 0.0079;   // Psi(2S) -> ll branching

const double BRPSI2S2JPSI = 0.610;  // Psi(2S) -> J/Psi branching
const double BRCHIc02JPSI = 0.0127; // chic0 -> J/Psi branching
const double BRCHIc12JPSI = 0.339;  // chic1 -> J/Psi branching
const double BRCHIc22JPSI = 0.192;  // chic2 -> J/Psi branching

double mBpm = 5.279;     // B^{+/-} mass, GeV
double mDstar = 2.01026; // D^* mass, GeV
double mK = 0.493;       // K mass, GeV

double mJPSI = 3.096916;  // J/Psi mass, GeV
double mPSI2S = 3.686097; // Psi(2S) mass, GeV
double mCHIc0 = 3.41475;  // chic0 mass, GeV
double mCHIc1 = 3.51066;  // chic1 mass, GeV
double mCHIc2 = 3.55620;  // chic2 mass, GeV

// CKB matrix elements

const double Vud = 0.97425;
const double Vus = 0.2252;
const double Vcd = 0.230;
const double Vcs = 1.023;
const double Vcb = 0.0406;
const double Vub = 0.00389;
const double Vtd = 0.0084;
const double Vts = 0.0387;
const double Vtb = 0.88;

