// histogram.cpp
// Last modified 10.11.2017 by Artem Lipatov

#include <QFile>
#include <QTextStream>

#include "histogram.h"

THistogram::THistogram(QString hcaption)
{
  caption = hcaption;
}

THistogram::THistogram(double hlowerborder, double hupperborder, unsigned short int hsize, QString hcaption)
{
  caption = hcaption;
  create(hlowerborder, hupperborder, hsize);
}

THistogram::~THistogram(void)
{
  entry.clear();
}

void THistogram::create(double hlowerborder, double hupperborder, unsigned short int hsize)
{
  double entrywidth = (hupperborder - hlowerborder)/hsize;
  for (unsigned short int i = 0; i < hsize; i++)
  {
    THistogramEntry *other = new(THistogramEntry);

    other->lowerborder = hlowerborder + i*entrywidth;
    other->upperborder = hlowerborder + (i + 1)*entrywidth;
    other->store = 0.0;

    append(*other);
  }
}

void THistogram::update(double hlowerborder, double hupperborder, unsigned short int hsize)
{
  entry.clear();
  create(hlowerborder, hupperborder, hsize);
}

unsigned short int THistogram::size(void)
{
  return entry.size();
}

void THistogram::clear(void)
{
  for (unsigned short int i = 0; i < entry.size(); i++)
    entry[i].store = 0.0;
}

void THistogram::append(THistogramEntry other)
{
  entry.append(other);
}

void THistogram::format(unsigned short int id, double lowerborder, double upperborder)
{
  entry[id].lowerborder = lowerborder;
  entry[id].upperborder = upperborder;
}

void THistogram::put(double locus, double store)
{
  if ( (locus < entry[0].lowerborder) or
       (locus > entry[entry.size() - 1].upperborder) ) return;

  for (unsigned short int i = 0; i < entry.size(); i++)
    if ( (locus >= entry[i].lowerborder) and (locus <= entry[i].upperborder) )
    {
      entry[i].store += store/(entry[i].upperborder - entry[i].lowerborder);
      break;
    }
}

double THistogram::weightedsum(void)
{
  double s = 0.0;

  for (unsigned short int i = 0; i < entry.size(); i++)
    s = s + entry[i].store*(entry[i].upperborder - entry[i].lowerborder);

  return s;
}

void THistogram::saveAsCurve(QString filename)
{
  QFile outfile(filename);
  if (not outfile.open(QIODevice::WriteOnly | QIODevice::Text)) return;

  QString textstring;
  QTextStream textstream(&outfile);
  for (unsigned short int i = 0; i < entry.size(); i++)
  {
    textstring = QString::number( 0.5*(entry[i].lowerborder + entry[i].upperborder) );
    textstring.append(" ");
    textstring.append(QString::number(entry[i].store));
    textstring.append("\n");

    textstream << textstring;
  }

  outfile.close();
}

void THistogram::saveAsHistogram(QString filename)
{
  QFile outfile(filename);
  if (not outfile.open(QIODevice::WriteOnly | QIODevice::Text)) return;

  QString textstring;
  QTextStream textstream(&outfile);
  for (unsigned short int i = 0; i < entry.size(); i++)
  {
    textstring = QString::number(entry[i].lowerborder);
    textstring.append(" ");
    textstring.append(QString::number(entry[i].store));
    textstring.append("\n");

    textstream << textstring;

    textstring = QString::number(entry[i].upperborder);
    textstring.append(" ");
    textstring.append(QString::number(entry[i].store));
    textstring.append("\n");

    textstream << textstring;
  }

  outfile.close();
}
