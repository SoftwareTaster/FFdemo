#ifndef FFD_H
#define FFD_H

#include <QVector>
#include "mypoint.h"

typedef MYPOINT MYVECTOR;

class FFD
{
public:
    MYPOINT controlpoints[4][4][4];
    MYVECTOR X0;
    MYVECTOR S, T, U;

public:
    FFD();
    FFD(MYPOINT ltp, MYPOINT rbp);
    int calculateFactorial(int i);
    int calculateCombinatorial(int i, int n);
    double calculateBernstein(int i, int n, double u);
    MYPOINT calculateBezier(MYPOINT np); // only accept the normalized points
};

#endif // FFD_H
