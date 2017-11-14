// utils.h
// Last modified 07.11.2017 by Artem Lipatov

#ifndef UTILS_H
#define UTILS_H

const double Q0 = 1.3;
const double PI = 3.14159;
const double ZERO = 1.0e-05;

const double GeV2nb = 4.0e+05;
const double GeV2pb = 4.0e+08;
const double GeV2fb = 4.0e+11;
const double nb2pb = 1.0e+03;
const double pb2nb = 1.0e-03;

const double GeV2TeV = 1.0e-03;
const double TeV2GeV = 1.0e+03;

const double rad2grad = 180.0/PI;
const double grad2rad = PI/180.0;

extern double aQED(void);        // QED constant
extern double aQED(double q2);   // QED running constant
extern double aQCD(double q2);   // QCD running constant
extern double aQCDSS(double q2); // Shirkov-Solovtsov QCD running constant
extern double aQCDLO(double q2); // QCD running constant at LO
extern double aQCDHO(double q2); // QCD running constant at NLO

extern double L(double, double, double);
extern double G(double, double, double, double, double, double);

// DGLAP splitting functions (LO)

extern double Pgg(double z);
extern double Pqg(double z);
extern double Pgq(double z);
extern double Pqq(double z);
extern double zPgg(double z);

extern double sqr(double x);
extern double max(double x, double y);
extern double min(double x, double y);
extern double heaviside(double x);
extern double eulergamma(double x);

extern void randomize(void);
extern double random(double x, double y);

extern void assist(void);

enum TFactorization { COLL, TMD };
enum TCollision { pp, ppbar };

enum TPDF { GRV94LO,
            MSTW2008LO, MSTW2008NLO,
            CTEQ66,
            AZERO,
            JH2013set1, JH2013set2,
            KMR
          };

enum THardScale { FinalParticleTransverseMomentum, FinalParticleTransverseMass, SubprocessEnergy, SubprocessEnergyPlusPairTransverseMomentum };
enum TScaleRate { DefaultScale, UpperScale, LowerScale };

enum TFragmentation { HQET, PETERSON };

extern double Ecm;
extern double g[4][4]; // metric tensor

extern unsigned long int nIterations;
extern unsigned long int nEventsPerIteration;

extern TFactorization Factorization;
extern TCollision Collision;
extern THardScale FactorizationScale;
extern THardScale RenormalizationScale;
extern TScaleRate ScaleRate;
extern TPDF PDF;

#endif
