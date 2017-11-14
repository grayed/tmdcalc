#include <cmath>
#include "tmdpdf.h"

#include <QFile>
#include <QStringList>

tmdpdf::tmdpdf(void)
{
  isDataFileLoaded = false;
}

tmdpdf::~tmdpdf()
{
  entry1.clear();
  entry2.clear();
  entry3.clear();

  store.clear();
}

void tmdpdf::LoadFromFile(QString FileName)
{
  QFile File(FileName);

  if ( File.open(QIODevice::ReadOnly) )
  {
    while ( not File.atEnd() )
    {
      QString DataString = File.readLine();
      QStringList varStringList = DataString.split(" ", QString::SkipEmptyParts);

      double var1 = exp(varStringList.at(0).toDouble());
      double var2 = exp(varStringList.at(1).toDouble());
      double var3 = exp(varStringList.at(2).toDouble());
      double var4 = varStringList.at(3).toDouble();

     if (entry1.size() == 0) entry1.append(var1);
        else if ( var1 > entry1.at(entry1.size() - 1) ) entry1.append(var1);

      if (entry2.size() == 0) entry2.append(var2);
        else if ( var2 > entry2.at(entry2.size() - 1) ) entry2.append(var2);

      if (entry3.size() == 0) entry3.append(var3);
        else if ( var3 > entry3.at(entry3.size() - 1) ) entry3.append(var3);

      store.append(var4/var2);
    }

   isDataFileLoaded = true;
  }

  File.close();
}

double tmdpdf::getTMD(double x, double k2, double q)
{
  if (not isDataFileLoaded) exit(0);

  unsigned short int n1 = entry1.size();
  unsigned short int n2 = entry2.size();
  unsigned short int n3 = entry3.size();

  if ( (x < entry1.at(0)) or (x > entry1.at(n1 - 1)) or
       (k2 < entry2.at(0)) or (k2 > entry2.at(n2 - 1)) or
       (q < entry3.at(0)) or (q > entry3.at(n3 - 1)) ) return 0.0;

  double x1 = entry1.at(0);
  double x2 = entry1.at(n1 - 1);

  double y1 = entry2.at(0);
  double y2 = entry2.at(n2 - 1);

  double z1 = entry3.at(0);
  double z2 = entry3.at(n3 - 1);

  unsigned short int i1 = 0;
  for (int i = 0; i < n1 - 1; i++)
    if ( (x >= entry1.at(i)) and (x <= entry1.at(i + 1)) )
    {
      x1 = entry1.at(i);
      x2 =  entry1.at(i + 1);
      i1 = i;
      break;
    }

  unsigned short int i2 = 0;
  for (int i = 0; i < n2 - 1; i++)
    if ( (k2 >= entry2.at(i)) and (k2 <= entry2.at(i + 1)) )
    {
      y1 = entry2.at(i);
      y2 =  entry2.at(i + 1);
      i2 = i;
      break;
    }

  unsigned short int i3 = 0;
  for (int i = 0; i < n3 - 1; i++)
    if ( (q >= entry3.at(i)) and (q <= entry3.at(i + 1)) )
    {
      z1 = entry3.at(i);
      z2 =  entry3.at(i + 1);
      i3 = i;
      break;
    }

  double f111 = store.at( i3 + i2*n3 + i1*n2*n3 );
  double f112 = store.at( (i3 + 1) + i2*n3 + i1*n2*n3 );
  double f211 = store.at( i3 + i2*n3 + (i1 + 1)*n2*n3 );
  double f212 = store.at( (i3 + 1) + i2*n3 + (i1 + 1)*n2*n3 );
  double f121 = store.at( i3 + (i2 + 1)*n3 + i1*n2*n3 );
  double f122 = store.at( (i3 + 1) + (i2 + 1)*n3 + i1*n2*n3 );
  double f221 = store.at( i3 + (i2 + 1)*n3 + (i1 + 1)*n2*n3 );
  double f222 = store.at( (i3 + 1) + (i2 + 1)*n3 + (i1 + 1)*n2*n3 );

  return ( f111*(x2 - x)*(y2 - k2)*(z2 - q) + f112*(x2 - x)*(y2 - k2)*(q - z1) +
    f121*(x2 - x)*(k2 - y1)*(z2 - q) + f122*(x2 - x)*(k2 - y1)*(q - z1) +
    f211*(x - x1)*(y2 - k2)*(z2 - q) + f212*(x - x1)*(y2 - k2)*(q - z1) +
    f221*(x - x1)*(k2 - y1)*(z2 - q) + f222*(x - x1)*(k2 - y1)*(q - z1) )/( (x2 - x1)*(y2 -
    y1)*(z2 - z1) );
}
