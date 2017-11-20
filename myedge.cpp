#include "myedge.h"

MYEDGE::MYEDGE()
{
}

MYEDGE::MYEDGE(int i, int j)
{
    pi = i;
    pj = j;
}

int &MYEDGE::operator[](unsigned int index)
{
    return (&pi)[index];
}

const int &MYEDGE::operator[](unsigned int index) const
{
    return (&pi)[index];
}
