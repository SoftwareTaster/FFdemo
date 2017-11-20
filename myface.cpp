#include "myface.h"

MYFACE::MYFACE()
{
}

MYFACE::MYFACE(int a, int b, int c)
{
    pa = a;
    pb = b;
    pc = c;
}

int &MYFACE::operator[](unsigned int index)
{
    return (&pa)[index];
}

const int &MYFACE::operator[](unsigned int index) const
{
    return (&pa)[index];
}
