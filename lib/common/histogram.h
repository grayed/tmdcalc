// histogram.h
// Last modified 10.11.2017 by Artem Lipatov

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QList>
#include <QString>

struct THistogramEntry
{
  double lowerborder;
  double upperborder;
  double store;
};

class THistogram {
public:
  THistogram(QString hcaption);
  THistogram(double hlowerborder, double hupperborder, unsigned short int hsize, QString hcaption);
  ~THistogram(void);

  void create(double hlowerborder, double hupperborder, unsigned short int hsize);
  void update(double hlowerborder, double hupperborder, unsigned short int hsize);

  void append(THistogramEntry other);
  void format(unsigned short int id, double lowerborder, double upperborder);
  void put(double locus, double store);
  void clear(void);

  double weightedsum(void);
  unsigned short int size(void);

  void saveAsCurve(QString filename);
  void saveAsHistogram(QString filename);

  QString caption;
  QList <THistogramEntry> entry;
};

#endif
