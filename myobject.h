#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QVector>
#include "mypoint.h"
#include "myedge.h"
#include "myface.h"
#include "ffd.h"

class MYOBJECT
{
public:
    QVector<MYPOINT> points;
    QVector<MYPOINT> normalizedpoints;
    QVector<MYEDGE> edges;
    QVector<MYFACE> faces;
    MYPOINT minPoint;
    MYPOINT maxPoint;
    FFD* ffd;

public:
    MYOBJECT();
    MYOBJECT(const QString &objpath);
    void toNormalize(MYVECTOR X0, MYVECTOR S, MYVECTOR T, MYVECTOR U);
    void refresh_normalized_points();
    void restore_points(MYVECTOR X0, MYVECTOR S, MYVECTOR T, MYVECTOR U);
};

#endif // MYOBJECT_H
