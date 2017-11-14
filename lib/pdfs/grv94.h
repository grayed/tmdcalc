// grv94.h
// Last modified 29.08.2017 by Artem Lipatov

#ifndef GRV94_H
#define GRV94_H

extern double grv94uvLO(double x, double q2);
extern double grv94dvLO(double x, double q2);
extern double grv94delLO(double x, double q2); // \bar d - \bar u
extern double grv94udbLO(double x, double q2); // \bar u + \bar d
extern double grv94sLO(double x, double q2);
extern double grv94cLO(double x, double q2);
extern double grv94bLO(double x, double q2);
extern double grv94gLO(double x, double q2);

#endif // GRV94_H
