#include "mypoint.h"
#include "math.h"

MYPOINT::MYPOINT()
{
}

MYPOINT::MYPOINT(double x, double y, double z)
{
    px = x;
    py = y;
    pz = z;
}

const MYPOINT MYPOINT::operator+(const MYPOINT &r) const
{
    return MYPOINT(px + r.px, py + r.py, pz + r.pz); // access private variable? why?
}

const MYPOINT MYPOINT::operator-(const MYPOINT &r) const
{
    return MYPOINT(px - r.px, py - r.py, pz - r.pz);
}

const MYPOINT MYPOINT::operator*(double k) const
{
    return MYPOINT(px * k, py * k, pz * k);
}

MYPOINT MYPOINT::normalize() const
{
    double N = 1.0 / sqrt(px * px + py * py + pz * pz);
    return MYPOINT(px * N, py * N, pz * N);
}

double &MYPOINT::operator[](unsigned int index)
{
    return (&px)[index];
}

const double &MYPOINT::operator[](unsigned int index) const
{
    return (&px)[index];
}

double MYPOINT::dotProduct(MYPOINT p)
{
    return px * p.px + py * p.py + pz * p.pz;
}

MYPOINT MYPOINT::crossProduct(MYPOINT p)
{
    return MYPOINT(py * p.pz - pz * p.py, pz * p.px - px * p.pz, px * p.py - py * p.px);
}
