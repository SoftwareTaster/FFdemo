#include "stdafx.h"
#include"GL/glew.h"
#include"GL/glut.h"

#include"MathAPIKernel/Vector3D.h"
#include"MathAPIKernel/Position3D.h"
#include"MathAPIKernel/Matrix4D.h"

#include "RoamingScenceManager.h"
RoamingScenceManager::RoamingScenceManager()
{
    OldMouse=new Position3D();
    Mouse=new Position3D();

    NewEye=new Vector3D(100,0,0);
    NewUp=new Vector3D(0,0,1);
    NewView=new Vector3D(0,0,0);

    AuxY =new Vector3D(0,1,0);
    AuxZ=new Vector3D();
	*AuxZ = (Vector3D)*NewEye - (Vector3D)*NewView;
    AuxX=new Vector3D();
    *AuxX=Vector3D::crossProduct(*AuxY,*AuxZ);
    AuxX->normalize();

    TempTranslateVec=new Vector3D(0,0,0);
    TempscaleFactor=1;
}

RoamingScenceManager::~RoamingScenceManager()
{
    delete OldMouse;
    delete Mouse;
    delete NewEye;
    delete NewUp;
    delete NewView;
    delete AuxX;
    delete AuxY;
    delete AuxZ;
	delete TempTranslateVec;
}

void RoamingScenceManager::init()
{
    init_CoordinaryDisplayList();
   glShadeModel(GL_SMOOTH);
   glClearColor(0.156   ,   0.156  ,    0.168 ,     0.0);
   glClearDepth(1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1000/2,1000/2,-1000/2,1000/2,-1000/2,1000/2);
}

void RoamingScenceManager::render()
{
    glClearColor(0.156   ,   0.156  ,    0.168 ,     0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    *NewView=*NewEye*-1;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(TempTranslateVec->X(),TempTranslateVec->Y(),TempTranslateVec->Z());
    glScalef(TempscaleFactor,TempscaleFactor,TempscaleFactor);
    gluLookAt(NewEye->X(),NewEye->Y(),NewEye->Z(),
              NewView->X(),NewView->Y(),NewView->Z(),
              NewUp->X(),NewUp->Y(),NewUp->Z());
    glColor3f(1,0,0);
    glutWireCube(250);
    glCallList(ID_COORDINATY);
}

void RoamingScenceManager::executeRotateOperation(int x, int y)
{
    Mouse->setX(x);
    Mouse->setY(y);

    Vector3D MouseTrace=*AuxY*(OldMouse->Y()-Mouse->Y())+*AuxX*(Mouse->X()-OldMouse->X());
    Vector3D RotateAsix=Vector3D::crossProduct(MouseTrace,*AuxZ);
    RotateAsix.normalize();

    float angle=MouseTrace.length();
    Matrix4D rotatMatrix=Matrix4D::getRotateMatrix(angle,RotateAsix);

    *NewEye=rotatMatrix*(*NewEye);
    *NewUp=rotatMatrix*(*NewUp);

    NewUp->normalize();
    *AuxY=*NewUp;
	*AuxZ = (Vector3D)*NewEye - (Vector3D)*NewView;
    *AuxX=Vector3D::crossProduct(*AuxY,*AuxZ);
    AuxX->normalize();
    *OldMouse=*Mouse;
}

void RoamingScenceManager::executeScaleOperation(float factor)
{
	if (TempscaleFactor <= 0)
	{
		TempscaleFactor = 0.1;
	}
	else
	{
		TempscaleFactor += factor;
	}
}

void RoamingScenceManager::executeTranslateOperation(int x, int y)
{
    Mouse->setX(x);
    Mouse->setY(y);
    Vector3D vec(-OldMouse->X()+Mouse->X(),-Mouse->Y()+OldMouse->Y(),0);
    *TempTranslateVec=*TempTranslateVec+vec;
    *OldMouse=*Mouse;
}

void RoamingScenceManager::getInitPos(int x, int y)
{
    Mouse->setX(x);
    Mouse->setY(y);
    *OldMouse=*Mouse;
}

void RoamingScenceManager::init_CoordinaryDisplayList()
{
    ID_COORDINATY=glGenLists(1);
    glNewList(ID_COORDINATY,GL_COMPILE);

    int length=50;
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(length,0.0,0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,length,0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,length);
    glEnd();

    glLineWidth(1);
    glEnd();
    glEndList();
}
