// OpenGLScence_raw.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include"GL/glut.h"
#include<memory> 
#include "RoamingScenceManager.h"

void MousePressEvent(int button, int state, int x, int y);
void MouseMoveEvent(int x,int y);
void ProcessSpecialKeys(int key, int x, int y);

void reshape(int w, int h);
void display();

bool leftButtonState;
bool rightButtonState;

//#define  GLUT_WHEEL_UP 3           //定义滚轮操作  
//#define  GLUT_WHEEL_DOWN 4

std::auto_ptr<RoamingScenceManager> manager(new RoamingScenceManager());


int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("原生OpenGL");
	manager->init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(MousePressEvent);
	glutMotionFunc(MouseMoveEvent);
	glutSpecialFunc(ProcessSpecialKeys);
	glutMainLoop();
	return 0;

}

void display()
{
	manager->render();
	glFlush();
}

void reshape(int w,int h)
{
	glViewport(0, -(w - h) / 2, w, w);
}

void MousePressEvent(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			manager->getInitPos(x, y);
			leftButtonState = true;
		}
		else
		{
			leftButtonState = false;
		}
	}

	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			manager->getInitPos(x, y);
			rightButtonState = true;
		}
		else
		{
			rightButtonState = false;
		}
	}

}

void MouseMoveEvent(int x, int y)
{
	if (leftButtonState)
	{
		manager->executeRotateOperation(x, y);
	}
	if (rightButtonState)
	{
	    manager->executeTranslateOperation(x, y);
	} 
	   display();
}
	
void ProcessSpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		manager->executeScaleOperation(-0.1);
	}
	if (key == GLUT_KEY_DOWN)
	{
		manager->executeScaleOperation(0.1);
	}
	display();
}

