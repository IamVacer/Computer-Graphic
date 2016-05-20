// CS3241Lab2.cpp : Defines the entry point for the console application.
#include <cmath>
#include <iostream>

/* Include header files depending on platform */
#ifdef _WIN32
	#include "glut.h"
	#define M_PI 3.14159

	#include <math.h>
	#include <time.h>
	#include <sys/timeb.h>
	#include "windows.h"
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/GLUT.h>


#endif

using namespace std;

#define numStars 100
#define numPlanets 9
double secondAngle = 0.0;
double mininuteAngle = 0.0;
double hourAngle = 0.0;
GLfloat hour = 0.0;
GLfloat x1 = 0.0;
GLfloat y2 = 0.0;
GLfloat z1 = 0.0;
GLfloat radius = 10.0;
GLfloat smallradius = 3.0;

class planet
{
public:
	float distFromRef;
	float angularSpeed;
	GLfloat color[3];
	float size;
	float angle;

	planet()
	{
		distFromRef = 0;
		angularSpeed = 0;
		color[0] = color[1] = color[2] = 0;
		size = 0;
		angle = 0;
	}
};
void drawTriangle(int x) {
	glPushMatrix();
	glRotated(x, 0, 0, 1);
	glBegin(GL_POLYGON);
	
	glColor3f(1, 0.4, 0);
	
	glVertex2f(0, 2);
	glVertex2f(-0.2, 0);
	glVertex2f(0.2, 0);
	glEnd();
	glPopMatrix();
}
float alpha = 0.0, k=1;
float tx = 0.0, ty=0.0;
planet planetList[numPlanets];
// -------------------------------   Seconds Line  ---------------------------------------

void secondsLine2(int x, double height, double width)
{
	int sec_ticks;
	secondAngle += 0.1;
	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(2.0);
	glPushMatrix();
	glTranslatef(height, width, 0.0);
	
	glRotated(x, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 7);
	glEnd();
	/*
	for (sec_ticks = 0; sec_ticks < 60; sec_ticks++)
	{
		glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glRotated((360 / 60) * sec_ticks, 0.0, 0.0, 1.0);
		glTranslatef(6.0, 0.0, 0.0);
		glutSolidCube(0.25);
		glPopMatrix();
	}
	*/
	glPopMatrix();
	glutPostRedisplay();
	//glutTimerFunc(10000,secondsLine,0);

}

void secondsLine1(double i)
{
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;
	glColor3f(0, 0, 0); // black color
	glLineWidth(300);

	theta = (M_PI / 180)*i; // converting degree to radian
	glColor3f(1.0, 1.0, 0.0);
	x1 = 8 * sin(theta); y1 = 8 * cos(theta);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(x1, y1);
	glEnd();

}
// -------------------------------   Minutes Line  ---------------------------------------

void minutesLines(int x)
{
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2.0);
	glPushMatrix();

	

	glRotated(x, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 7.0, 1.0);
	glEnd();
	glPopMatrix();
}

// -------------------------------   Hour Line  ------------------------------------------

void hourLine(int x)
{
	int hour_ticks;

	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(3.0);
	glPushMatrix();

	//glTranslatef(10.0, 10.0, 0.0);

	glRotated(x, 0.0, 0.0, 1.0);

	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 6.5, 0.0);
	glEnd();

	/*
	for (hour_ticks = 0; hour_ticks < 12; hour_ticks++)
		
	{
		glPushMatrix();// Draw next arm axis.
		glColor3f(0.0, 1.0, 1.0); // give it a color
		glTranslatef(0.0, 0.0, 0.0);
		glRotated((360 / 12) * hour_ticks, 0.0, 0.0, 1.0);
		glTranslatef(6.0, 0.0, 0.0);
		glutSolidCube(1.0);

		glPopMatrix();
	}
	*/
	glPopMatrix();
}


void drawCircle(int start, int end, int scale)
{
	int i;
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;
	glColor3f(0, 0, 0); // black color
	glLineWidth(100);
	glBegin(GL_POLYGON);
	for (i = start; i<end; i++) // angle in degree
	{
		theta = (M_PI / 180)*i; // converting degree to radian
		nextTheta = (M_PI / 180)*(i + 1);
		x1 = scale * sin(theta); y1 = scale * cos(theta);
		x2 = scale * sin(nextTheta); y2 = scale * cos(nextTheta);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}

	glEnd();
}

void drawCircle2(double i)
{
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;
	glColor3f(0, 0, 0); // black color
	glLineWidth(300);

	theta = (M_PI / 180)*i; // converting degree to radian

	x1 = 8 * sin(theta); y1 = 8 * cos(theta);

	glTranslated(x1, y1, 0);
	drawCircle(0, 360, 2);

}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.3, 1.0);
	glShadeModel (GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();

	//controls transformation
	glScalef(k, k, k);	
	glTranslatef(tx, ty, 0);	
	glRotated(alpha, 0, 0, 1);
	
	
	//animation angles


	SYSTEMTIME mtimer;
	GetSystemTime(&mtimer);
	double millis =  mtimer.wMilliseconds;
	double mAngle = millis * 360 / 1000;
	time_t current_time = time(0);
	struct tm * timeinfo = localtime(&current_time);
	int seconds = (float)timeinfo->tm_sec;
	double secAngle = seconds * 6 + fmod(mAngle, 360)/60;
	int minutes = (float)timeinfo->tm_min;
	double minAngle = minutes * 6 + fmod(secAngle, 360)/60;
	int hour = (float)timeinfo->tm_hour;
	double hrAngle = ((hour % 12) * 30) + fmod(minAngle, 360) / 60;
	//double angleHr = 360 - (hour %12) / 12 * 360;

	//drawTriangle(90);
	//draw stuff here!
	//drawTriangle(angleSec);
	//drawTriangle(angleMin);
	//drawTriangle(angleHr);
	drawCircle(0, 360, 8);
	secondsLine1(secAngle);
	minutesLines(-minAngle);
	hourLine(-hrAngle);

	drawCircle2(secAngle);

	glPopMatrix();
	glutSwapBuffers ();
}

void idle()
{
	//update animation here
	


	glutPostRedisplay();	//after updating, draw the screen again
}

void keyboard (unsigned char key, int x, int y)
{
	//keys to control scaling - k
	//keys to control rotation - alpha
	//keys to control translation - tx, ty
	switch (key) {

		case 'a':
			alpha+=10;
			glutPostRedisplay();
		break;

		case 'd':
			alpha-=10;
			glutPostRedisplay();
		break;

		case 'q':
			k+=0.1;
			glutPostRedisplay();
		break;

		case 'e':
			if(k>0.1)
				k-=0.1;
			glutPostRedisplay();
		break;

		case 'z':
			tx-=0.1;
			glutPostRedisplay();
		break;

		case 'c':
			tx+=0.1;
			glutPostRedisplay();
		break;

		case 's':
			ty-=0.1;
			glutPostRedisplay();
		break;

		case 'w':
			ty+=0.1;
			glutPostRedisplay();
		break;
		
		case 27:
			exit(0);
		break;

		default:
		break;
	}
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 2\n\n";
	cout<<"+++++CONTROL BUTTONS+++++++\n\n";
	cout<<"Scale Up/Down: Q/E\n";
	cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
	cout<<"Move Up/Down: W/S\n";
	cout<<"Move Left/Right: Z/C\n";
	cout <<"ESC: Quit\n";

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (200, 300);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);	
	//glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
