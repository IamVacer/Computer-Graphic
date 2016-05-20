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


double secondAngle = 0.0;
double mininuteAngle = 0.0;
double hourAngle = 0.0;
GLfloat hour = 0.0
boolean clockBoolean = true;
GLfloat radius = 10.0;
GLfloat smallradius = 3.0;

double starArr[400]; //coordinates of stars in the default window
double starArr2[400]; //coordinates of stars if user wishes to zoom out

float alpha = 0.0, k = 1;
float tx = 0.0, ty = 0.0;

void drawCircle(double scale, double r, double g, double b, double alpha)
{
	glPushMatrix();
	int i;
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;
	glColor4f(r, g, b, alpha); // set planet colour
	glLineWidth(100);
	glBegin(GL_POLYGON);
	for (i = 0; i<360; i++) // angle in degree
	{
		theta = (M_PI / 180)*i; // converting degree to radian
		nextTheta = (M_PI / 180)*(i + 1);
		x1 = scale * sin(theta); y1 = scale * cos(theta);
		x2 = scale * sin(nextTheta); y2 = scale * cos(nextTheta);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}

	glEnd();
	glPopMatrix();
}

// -------------------------------   Clock Layout  ---------------------------------------

void starPlot(double second){
	double x, y;
	glBegin(GL_POINTS);
	double theta = (M_PI / 180)*second;
	glColor4f(1, 1, 1, cos(theta)); //enable change of colour
	for (int i = 0; i < 200; i += 2) {
		glVertex2d(starArr[i] / 100, starArr[i + 1] / 100);
		glVertex2d(starArr2[i] / 100, starArr2[i + 1] / 100);
	}
	glEnd();
}
void drawLayout(double second)
{
	
	drawCircle(8, 0, 0, 0, 1);
	
	glPushMatrix();
	double theta, nextTheta, degree;
	double x1, y1;
	double x2, y2;
	glLineWidth(1);
	for (degree = 0; degree <= 11; degree++) {
		theta = (M_PI / 180)*degree*30; // converting degree to radian
		glColor3f(0.0, 1.0, 1.0);
		x1 = 8 * sin(theta); y1 = 8 * cos(theta);
		x2 = 7.5 * sin(theta); y2 = 7.5 * cos(theta);
		glBegin(GL_LINES);
		glVertex2f(x2, y2);
		glVertex2f(x1, y1);
		glEnd();
	}

	

	glPopMatrix();

}


// -------------------------------   Seconds Line  ---------------------------------------

void secLine(double i, double second)
{
	glPushMatrix();
	double theta, theta2, r, g;
	double x1, y1;
	double x2, y2;
	glLineWidth(1);

	theta = (M_PI / 180)*i; // converting degree to radian
	glColor3f(1.0, 1.0, 0.0);
	x1 = 8 * sin(theta); y1 = 8 * cos(theta);

	//Drawing of Line to assist in clock reading
	glPushAttrib(GL_ENABLE_BIT);
	// glPushAttrib is done to return everything to normal after drawing
	glLineStipple(2, 0x1111); 
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(x1, y1);
	glEnd();

	glPopAttrib();
	glTranslated(x1, y1, 0);

	drawCircle(0.2, 1, 1, 0, 1);
	theta2 = (M_PI / 180)*second; // converting degree to radian
	if (theta2/M_PI<0.3) {
		g = 1;
		r = 0;
	} else {
		g = 1- theta2/M_PI;
		r = theta2 / M_PI;;
	}
	x2 = 0.8 * sin(theta2)*(1 - cos(theta2)); y2 = 0.8 * cos(theta2)*(1 - cos(theta2));
	glTranslated(x2, y2, 0);

	drawCircle(0.12, r, g, 0, 1);
	glPopMatrix();

}

// -------------------------------   Minutes Line  ---------------------------------------

void minLine(double i, double second)
{
	glPushMatrix();
	double theta, theta2;
	double x1, y1;
	double x2, y2;
	glLineWidth(5);

	theta = (M_PI / 180)*i; // converting degree to radian
	glColor3f(1.0, 0.0, 0.0);
	x1 = 6 * sin(theta); y1 = 6 * cos(theta);

	//Drawing of Line to assist in clock reading
	glPushAttrib(GL_ENABLE_BIT);
	// glPushAttrib is done to return everything to normal after drawing
	glLineStipple(2, 0x2222);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(x1, y1);
	glEnd();

	glPopAttrib();
	glTranslated(x1, y1, 0);
	drawCircle(0.4, 1, 0, 0,1);
	theta2 = (M_PI / 180)*second; // converting degree to radian
	x2 = 0.3 * sin(theta2); y2 = 0.3 * cos(theta2);
	glTranslated(x2, y2, 0);

	drawCircle(0.12-fmod(second,360)/360*0.06, 1, 1, 0, 1);
	glPopMatrix();

}

// -------------------------------   Hour Line  ------------------------------------------

void hrLine(double i, double second)
{
	glPushMatrix();
	double theta, theta2;
	double x1, y1;
	double x2, y2;
	glLineWidth(300);

	theta = (M_PI / 180)*i; // converting degree to radian
	glColor3f(0.0, 1.0, 0.0);
	x1 = 4 * sin(theta); y1 = 4 * cos(theta);

	//Drawing of Line to assist in clock reading
	glPushAttrib(GL_ENABLE_BIT);
	// glPushAttrib is done to return everything to normal after drawing
	glLineStipple(2, 0x4444);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(x1, y1);
	glEnd();

	glPopAttrib();
	glTranslated(x1, y1, 0);
	drawCircle(0.6, 0, 1, 0, 1);
	theta2 = (M_PI / 180)*second; // converting degree to radian
	x2 = 0.5 * sin(theta2); y2 = 0.5 * cos(theta2);
	glTranslated(x2, y2, 0);
	drawCircle(0.2 - fmod(second, 360) / 360 * 0.1, 1, 0, 0, 1);
	glPopMatrix();

}


// -------------------------------   SOLAR  ------------------------------------------


void planet1(double i, double second)
{
	glPushMatrix();
	double theta, theta2, r, g;
	double x1, y1;
	double x2, y2;
	glLineWidth(1);

	theta = (M_PI / 180)*i; // converting degree to radian
	glColor3f(1.0, 1.0, 0.0);
	x1 = 8 * sin(theta); y1 = 8 * cos(theta);

	glPopAttrib();
	glTranslated(x1, y1, 0);

	drawCircle(1, 1, 1, 0, 1);
	theta2 = (M_PI / 180)*second; // converting degree to radian
	if (theta2 / M_PI<0.3) {
		g = 1;
		r = 0;
	}
	else {
		g = 1 - theta2 / M_PI;
		r = theta2 / M_PI;;
	}

	//Butteryfly equation
	x2 = 0.8 * sin(theta2)*(exp(cos(theta2)) - 4 * cos(2 * theta2) - pow(sin(theta2 / 12), 5));
	y2 = 0.8 * cos(theta2)*(exp(cos(theta2)) - 4 * cos(2 * theta2) - pow(sin(theta2 / 12), 5));
	glTranslated(x2, y2, 0);

	drawCircle(0.12, r, g, 0, 1);
	glPopMatrix();

}

void planet2(double i, double second)
//this planet has 2 moons spinning around it
{
	glPushMatrix();
	double theta, theta2, r, g;
	double x1, y1;
	double x2, y2;

	theta = (M_PI / 180)*(i + 67); // converting degree to radian
	theta2 = (M_PI / 180)*second; // converting degree to radian
	glColor3f(1.0, 1.0, 0.0);
	x1 = 5 * sin(-theta); y1 = 5 * cos(-theta);

	glTranslated(x1, y1, 0);

	drawCircle(0.2, cos(theta2), 1, sin(theta2), 1);
	
	if (theta2 / M_PI<0.3) {
		g = 1;
		r = 0;
	}
	else {
		g = 1 - theta2 / M_PI;
		r = theta2 / M_PI;;
	}
	glRotated(second, 0, 0, 1);
	x2 = 1.8 * sin(theta2);
	y2 = 0.5 * cos(theta2);
	glTranslated(x2, y2, 0);

	drawCircle(0.12, g, 0, r, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x1, y1, 0);
	glRotated(180+second, 0, 0, 1);
	glTranslated(x2, y2, 0);

	drawCircle(0.07, g, 0, r, 1);
	glPopMatrix();

}

void planet3(double i, double second)
//This planet is bouncing on the sun
{
	glPushMatrix();
	double theta, height, theta2, theta3, theta4;
	theta = (M_PI / 180)*(i*36); // converting degree to radian
	glRotated(i * 7, 0, 0, 1);
	height = 2 * cos(theta);
	if (height < 0) {
		height = -height;
	}
	glTranslated(0, 2, 0);
	glTranslated(0, height,0);
	theta2 = (M_PI / 180)*(i * 42);
	theta3 = (M_PI / 180)*(second * 36);
	theta4 = (M_PI / 180)*(i * 76);
	drawCircle(0.1, cos(theta4), cos(theta2), sin(theta3), 1);

	glPopMatrix();

}

void planet4(double i, double second)
//This planet has a moon that orbits in a "infinite" like path
{
	glPushMatrix();
	double theta, theta2, r, g;
	double x1, y1;
	double x2, y2;
	glLineWidth(1);

	theta = (M_PI / 180)*i; // converting degree to radian
	glColor3f(1.0, 1.0, 0.0);
	x1 = 8 * sin(theta + M_PI); y1 = 8 * cos(theta + M_PI);

	glPopAttrib();
	glTranslated(x1, y1, 0);

	drawCircle(1, 1, 1, 0, 1);
	theta2 = (M_PI / 180)*i*40; // converting degree to radian
	if (theta2 / M_PI<0.3) {
		g = 1;
		r = 0;
	}
	else {
		g = 1 - theta2 / M_PI;
		r = theta2 / M_PI;;
	}
	x2 = 0.8 * cos(theta2*3);
	y2 = 1.6 * sin(theta2);
	glTranslated(x2, y2, 0);

	drawCircle(0.12, r, g, 0, 1);
	glPopMatrix();

}

void loadPlanet(double second, double milli, double minute) {
	drawCircle(2, 1, 0.5, 0, 1);
	double orbit2 = fmod(second * 34, 360);//to create variations of orbit timing
	planet1(second, milli);

	glPushMatrix();
	for (int i = 0; i < 4; i++) {
		glRotated(i * 90, 0, 0, 1);
		planet2(second, orbit2);
	}
	glPopMatrix();
	
	glPushMatrix();

	for (int i = 0; i < 2; i++) {
		glRotated(i * 180, 0, 0, 1);
		planet3(second, orbit2);
	}
	
	glPopMatrix();
	planet4(second, milli);
}

// -------------------------------   Main  ------------------------------------------
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
	
	//Load and calculate timer angles
	SYSTEMTIME mtimer;
	GetSystemTime(&mtimer);
	time_t current_time = time(0);
	struct tm * timeinfo = localtime(&current_time);

	double millis =  mtimer.wMilliseconds;
	double mAngle = millis * 360 / 1000;
	
	int seconds = (float)timeinfo->tm_sec;
	double secAngle = seconds * 6 + fmod(mAngle, 360)/60;

	int minutes = (float)timeinfo->tm_min;
	double minAngle = minutes * 6 + fmod(secAngle, 360)/60;

	int hour = (float)timeinfo->tm_hour;
	double hrAngle = ((hour % 12) * 30) + fmod(minAngle, 360) / 60;


	if (clockBoolean) {
		//Clock Layout
		glClearColor(0.0, 0.0, 0.3, 1.0);
		drawLayout(mAngle);
		starPlot(1);
		secLine(secAngle, mAngle);
		minLine(minAngle, secAngle);
		hrLine(hrAngle, minAngle);
		drawCircle(2, 1, 0.5, 0, 1);
		

	}
	else {
		//Solar System
		glClearColor(0.0, 0.0, 0.0, 1.0);
		starPlot(secAngle*37);
		loadPlanet(secAngle, mAngle, minAngle);
	}
	
	glPopMatrix();
	glutSwapBuffers ();
}

void idle()
{

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

		case 't':
			clockBoolean = !clockBoolean;
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
	cout << "Toogle Clock\n";
	cout <<"ESC: Quit\n";
	
	for (int i = 0; i < 400; i++) {
		starArr[i] = rand()%3000 - 1500;
		starArr2[i] = rand() % 20000 - 10000;
	}
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
