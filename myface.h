#ifndef MYFACE_H
#define MYFACE_H

class MYFACE
{
public:
    int pa, pb, pc;

public:
    MYFACE();
    MYFACE(int a, int b, int c);
    int &operator[](unsigned int index);
    const int &operator[](unsigned int index) const;
};

#endif // MYFACE_H
