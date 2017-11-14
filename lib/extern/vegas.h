#ifndef VEGAS_H
#define VEGAS_H

extern int ndim;                // dimension
extern int itmx;                // number of iterations
extern int init;
extern unsigned long int calls; // number of calls
extern double regn[];           // integration region
extern double tgral;            // best estimate of the integral
extern double chi2a;            // \xi^2 per degree of freedom
extern double sd;               // standard deviation

extern void vegas(double regn[], int ndim, double (*fxn)(double [], double), int init, unsigned long ncall, int itmx, double *tgral, double *sd, double *chi2a, void(*callback)(unsigned int, void *), void *pointer);

#endif

