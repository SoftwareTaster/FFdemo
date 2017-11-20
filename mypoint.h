#ifndef MYPOINT_H
#define MYPOINT_H

class MYPOINT
{
public:
    double px, py, pz;

public:
    MYPOINT();
    MYPOINT(double x, double y, double z); // constructor
    const MYPOINT operator+(const MYPOINT& r) const;
    const MYPOINT operator-(const MYPOINT& r) const;
    const MYPOINT operator*(double k) const; // operator overloading
    MYPOINT normalize() const; // normalization useless?
    double &operator[](unsigned int index);
    const double &operator[](unsigned int index) const;
    double dotProduct(MYPOINT p);
    MYPOINT crossProduct(MYPOINT p);
};

#endif // MYPOINT_H
