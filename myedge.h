#ifndef MYEDGE_H
#define MYEDGE_H

class MYEDGE
{
public:
    int pi, pj;

public:
    MYEDGE();
    MYEDGE(int i, int j);
    int &operator[](unsigned int index);
    const int &operator[](unsigned int index) const;
};

#endif // MYEDGE_H
