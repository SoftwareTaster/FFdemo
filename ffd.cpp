#include "ffd.h"
#include <QtMath>

FFD::FFD()
{
}

FFD::FFD(MYPOINT ltp, MYPOINT rbp)
{
    double betweenX, betweenY, betweenZ;
    betweenX = (rbp.px - ltp.px) / 3;
    betweenY = (rbp.py - ltp.py) / 3;
    betweenZ = (rbp.pz - ltp.pz) / 3;
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            for (int k = 0; k <= 3; k++) {
                controlpoints[i][j][k].px = ltp.px + i * betweenX;
                controlpoints[i][j][k].py = ltp.py + j * betweenY;
                controlpoints[i][j][k].pz = ltp.pz + k * betweenZ;
            }
        }
    }
    X0 = ltp;
    S.px = rbp.px - ltp.px; S.py = 0; S.pz = 0;
    T.px = 0; T.py = rbp.py - ltp.py; T.pz = 0;
    U.px = 0; U.py = 0; U.pz = rbp.pz - ltp.pz;
}

int FFD::calculateFactorial(int i)
{
    if (i == 1) {
        return 1;
    }
    else {
        return i * calculateFactorial(i - 1);
    }
}

int FFD::calculateCombinatorial(int i, int n)
{
    int numerator = calculateFactorial(n);
    int denominator = calculateFactorial(i) * calculateFactorial(n - i);
    return numerator / denominator;
}

double FFD::calculateBernstein(int i, int n, double u)
{
    return calculateCombinatorial(i, n) * qPow(u, i) * qPow(1 - u, n - i);
}

MYPOINT FFD::calculateBezier(MYPOINT np)
{
    double resx = 0; double resy = 0; double resz = 0;
    int u = np.px; int v = np.py; int w = np.pz;
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            for (int k = 0; k <= 3; k++) {
                resx += calculateBernstein(i, 3, u) * calculateBernstein(j, 3, v) * calculateBernstein(k, 3, w) * controlpoints[i][j][k].px;
                resy += calculateBernstein(i, 3, u) * calculateBernstein(j, 3, v) * calculateBernstein(k, 3, w) * controlpoints[i][j][k].py;
                resz += calculateBernstein(i, 3, u) * calculateBernstein(j, 3, v) * calculateBernstein(k, 3, w) * controlpoints[i][j][k].pz;
            }
        }
    }
    return MYPOINT(resx, resy, resz);
}
