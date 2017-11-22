#include "myobject.h"

#include <QFile>
#include <QDebug>
#include <QTextStream>

MYOBJECT::MYOBJECT()
{
}

MYOBJECT::MYOBJECT(const QString &objpath)
{
    //QFile f("F:\\experiment\\qt\\Projects\\ComputerAnimatioonTwo\\ObjParseRight.txt");
    //f.open(QIODevice::WriteOnly | QIODevice::Text);
    //QTextStream txtOutput(&f);
    QFile file(objpath);
    if (!file.open(QIODevice::ReadOnly)) {
        printf("open model goes wrong.");
        return;
    }
    QTextStream in(&file); // text stream of the whole file
    while (!in.atEnd()) {
        QString input = in.readLine();
        if (input.isEmpty() || input[0] == '#') {
            continue;
        } // invalid line
        QTextStream ts(&input); // text stream of the whole line
        QString id;
        ts >> id;
        if (id == "v") {
            MYPOINT p;
            for (int i = 0; i < 3; i++) {
                ts >> p[i];
                minPoint[i] = qMin(minPoint[i], p[i]);
                maxPoint[i] = qMax(maxPoint[i], p[i]);
            }
            //txtOutput << p.px << "\t" << p.py << "\t" << p.pz << endl;
            points << p;
        } // point definition line
        else if (id == "f") {
            MYFACE f;
            for (int i = 0; i < 3; i++) {
                QString stmp;
                ts >> stmp;
                int itmp;
                itmp = stmp.toInt();
                itmp--;
                f[i] = itmp;
            }
            //txtOutput << f.pa << "\t" << f.pb << "\t" << f.pc << endl;
            faces << f;
            edges << MYEDGE(f[0], f[1]) << MYEDGE(f[1], f[2]) << MYEDGE(f[2], f[0]);
        }
    }
    file.close();
    //f.close();

    ffd = new FFD(minPoint, maxPoint);
    toNormalize(ffd->X0, ffd->S, ffd->T, ffd->U);
}

void MYOBJECT::toNormalize(MYVECTOR X0, MYVECTOR S, MYVECTOR T, MYVECTOR U)
{
    for (int i = 0; i < points.size(); i++) {
        double s, t, u;
        s = (T.crossProduct(U).dotProduct(points[i] - X0)) / (T.crossProduct(U).dotProduct(S));
        t = (S.crossProduct(U).dotProduct(points[i] - X0)) / (S.crossProduct(U).dotProduct(T));
        u = (S.crossProduct(T).dotProduct(points[i] - X0)) / (S.crossProduct(T).dotProduct(U));
        normalizedpoints.append(MYPOINT(s, t, u));
    }
}

void MYOBJECT::refresh_normalized_points()
{
    for (int i = 0; i < normalizedpoints.size(); i++) {
        normalizedpoints[i] = ffd->calculateBezier(normalizedpoints[i]);
    }
}

void MYOBJECT::restore_points(MYVECTOR X0, MYVECTOR S, MYVECTOR T, MYVECTOR U)
{
    for (int i = 0; i < normalizedpoints.size(); i++) {
        points[i] = X0 + S * normalizedpoints[i].px + T * normalizedpoints[i].py + U * normalizedpoints[i].pz;
    }
}
