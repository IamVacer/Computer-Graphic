// CS3241Lab4.cpp : Defines the entry point for the console application.
//#include <cmath>
#include "math.h"
#include <iostream>
#include <fstream>

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

#define MAXPTNO 1000
#define NLINESEGMENT 32
#define NOBJECTONCURVE 8

using namespace std;

double millis;
double mAngle;

// Global variables that you can use
struct Point {
	int x,y;
};
double toRad(double angle){
	return (M_PI / 180)*angle; // converting degree to radian
}
void drawCircle(double scale, double r, double g, double b, double alpha)
{
	glPushMatrix();
	int i;
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;
	glColor4f(r, g, b, alpha); // set planet colour
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


// Storage of control points
int nPt = 0;
Point ptList[MAXPTNO];
Point ctList[MAXPTNO];

// Display options
bool displayControlPoints = true;
bool displayControlLines = true;
bool displayTangentVectors = false;
bool displayObjects = false;
bool C1Continuity = false;
bool displayBeizer = true;
	
void drawRightArrow()
{
	glColor3f(1, 0, 1);
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
		glVertex2f(0,0);
		glVertex2f(100,0);
		glVertex2f(95,5);
		glVertex2f(100,0);
		glVertex2f(95,-5);
	glEnd();
}
void erasePt(void) {
	nPt = 0;
}
void drawASmallTri()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(500, 00);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(500, 500);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(000, 500);
	glEnd();
}

int choose(int n, int k)
{
	if (k > n) return 0;
	if (k * 2 > n) k = n - k;
	if (k == 0) return 1;

	int result = n;
	for (int i = 2; i <= k; ++i) {
		result *= (n - i + 1);
		result /= i;
	}
	return result;
}


double bi(double t, int i) {
	double part1 = pow(1-t, 3 - i);
	double part2 = pow(t, i);
	return part1*part2;
}
void drawTan(void) {
	Point p1, p2, p3, p4, pAns, tAns;
	int c1 = choose(3, 0);
	int c2 = choose(3, 1);
	int c3 = choose(3, 2);
	int c4 = choose(3, 3);
	
	for (int i = 0; i + 3 < nPt; i += 3) {
		if (C1Continuity) {
			p1 = ctList[i];
			p2 = ctList[i + 1];
			p3 = ctList[i + 2];
			p4 = ctList[i + 3];
		}
		else {
			p1 = ptList[i];
			p2 = ptList[i + 1];
			p3 = ptList[i + 2];
			p4 = ptList[i + 3];
		}
		glPointSize(3);

		for (double t = 0; t < NOBJECTONCURVE ; t++) {
			glPushMatrix();
			double sT = t / (NOBJECTONCURVE-1);
			pAns.x = c1*bi(sT, 0)*p1.x + c2*bi(sT, 1)*p2.x + c3*bi(sT, 2)*p3.x + c4*bi(sT, 3)*p4.x;
			pAns.y = c1*bi(sT, 0)*p1.y + c2*bi(sT, 1)*p2.y + c3*bi(sT, 2)*p3.y + c4*bi(sT, 3)*p4.y;
			tAns.x = (3 * pow(1 - sT, 2)*(p2.x - p1.x)) + (6 * (1 - sT)*sT*(p3.x - p2.x)) + (3 * pow(sT, 2)*(p4.x - p3.x));
			tAns.y = (3 * pow(1 - sT, 2)*(p2.y - p1.y)) + (6 * (1 - sT)*sT*(p3.y - p2.y)) + (3 * pow(sT, 2)*(p4.y - p3.y));
			
			glTranslated(pAns.x, pAns.y,0);
			glRotatef(atan2(tAns.y, tAns.x) * 180 / M_PI, 0, 0, 1);
			drawRightArrow();
			glPopMatrix();
		}

	}
}

void drawObject(double angle) {
	Point p1, p2, p3, p4, pAns, tAns;
	int c1 = choose(3, 0);
	int c2 = choose(3, 1);
	int c3 = choose(3, 2);
	int c4 = choose(3, 3);

	for (int i = 0; i + 3 < nPt; i += 3) {
		if (C1Continuity) {
			p1 = ctList[i];
			p2 = ctList[i + 1];
			p3 = ctList[i + 2];
			p4 = ctList[i + 3];
		}
		else {
			p1 = ptList[i];
			p2 = ptList[i + 1];
			p3 = ptList[i + 2];
			p4 = ptList[i + 3];
		}
		glPointSize(3);

		for (double t = 0; t < NOBJECTONCURVE; t++) {
			glPushMatrix();
			double sT = t / (NOBJECTONCURVE - 1);
			pAns.x = c1*bi(sT, 0)*p1.x + c2*bi(sT, 1)*p2.x + c3*bi(sT, 2)*p3.x + c4*bi(sT, 3)*p4.x;
			pAns.y = c1*bi(sT, 0)*p1.y + c2*bi(sT, 1)*p2.y + c3*bi(sT, 2)*p3.y + c4*bi(sT, 3)*p4.y;
			tAns.x = (3 * pow(1 - sT, 2)*(p2.x - p1.x)) + (6 * (1 - sT)*sT*(p3.x - p2.x)) + (3 * pow(sT, 2)*(p4.x - p3.x));
			tAns.y = (3 * pow(1 - sT, 2)*(p2.y - p1.y)) + (6 * (1 - sT)*sT*(p3.y - p2.y)) + (3 * pow(sT, 2)*(p4.y - p3.y));

			glTranslated(pAns.x, pAns.y, 0);
			glRotatef(atan2(tAns.y, tAns.x) * 180 / M_PI, 0, 0, 1);
			drawCircle(20 * sin(toRad(angle / 2 - t* (180 / NOBJECTONCURVE))), abs(sin(toRad(angle / 2 - t* (90 / NOBJECTONCURVE)))), abs(sin(toRad(angle / 2 - t* (180 / NOBJECTONCURVE)))), abs(sin(toRad(angle / 2 - t* (45 / NOBJECTONCURVE)))), 1);
			glPopMatrix();
		}

	}
}

void drawBezier(void) {
	Point p1, p2, p3, p4, pAns;
	int c1 = choose(3, 0);
	int c2 = choose(3, 1);
	int c3 = choose(3, 2);
	int c4 = choose(3, 3);
	glLineWidth(3);
	if (C1Continuity) {
		for (int i = 0; i + 3 < nPt; i += 3) {
			p1 = ctList[i];
			p2 = ctList[i + 1];
			p3 = ctList[i + 2];
			p4 = ctList[i + 3];
			glPointSize(3);
			glBegin(GL_LINE_STRIP);
			for (double t = 0; t < NLINESEGMENT+1; t++) {
				double sT = t / NLINESEGMENT;
				pAns.x = c1*bi(sT, 0)*p1.x + c2*bi(sT, 1)*p2.x + c3*bi(sT, 2)*p3.x + c4*bi(sT, 3)*p4.x;
				pAns.y = c1*bi(sT, 0)*p1.y + c2*bi(sT, 1)*p2.y + c3*bi(sT, 2)*p3.y + c4*bi(sT, 3)*p4.y;
				glColor3f(0, 0, 1);
				glVertex2d(pAns.x, pAns.y);
				//prevPt = pAns;
			}
			glEnd();
		} 
	} else {
		for (int i = 0; i + 3 < nPt; i += 3) {
			p1 = ptList[i];
			p2 = ptList[i + 1];
			p3 = ptList[i + 2];
			p4 = ptList[i + 3];
			glPointSize(3);
			glBegin(GL_LINE_STRIP);
			for (double t = 0; t < NLINESEGMENT+1; t++) {
				double sT = t / NLINESEGMENT;
				pAns.x = c1*bi(sT, 0)*p1.x + c2*bi(sT, 1)*p2.x + c3*bi(sT, 2)*p3.x + c4*bi(sT, 3)*p4.x;
				pAns.y = c1*bi(sT, 0)*p1.y + c2*bi(sT, 1)*p2.y + c3*bi(sT, 2)*p3.y + c4*bi(sT, 3)*p4.y;
				glColor3f(0, 0, 1);
				glVertex2d(pAns.x, pAns.y);
			}
			glEnd();
		}
		glLineWidth(1);

		
	}
	//drawASmallTri();
}
void fixCont(void) {
	Point p1;
	for (int i = 0; i < nPt; i++) {
		if (i % 3 == 1 && i>2){
			p1.x = 2 * ptList[i - 1].x - ptList[i - 2].x;
			p1.y = 2 * ptList[i - 1].y - ptList[i - 2].y;
			ctList[i] = p1;
		}
	}
	
}
void drawCont(void) {
	
	for (int i = 0; i + 3 < nPt; i += 3) {
		Point p1;
		glPointSize(1);
		glColor3f(1, 0, 0);
		p1.x = 2* ptList[i + 3].x - ptList[i + 2].x;
		p1.y = 2* ptList[i + 3].y - ptList[i + 2].y;
		glBegin(GL_LINES);
		glVertex2d(p1.x, p1.y);
		glVertex2d(ptList[i+ 3].x, ptList[i + 3].y);
		glEnd();

		glBegin(GL_POINT);
		glPointSize(5);
		glColor3f(0, 0, 1);
		glVertex2d(p1.x, p1.y);
		glEnd();

	}
	//drawASmallTri();
}

void drawLines(void) {
	glLineWidth(1);
	if (C1Continuity) {
		for (int i = 0; i<nPt - 1; i++)
		{
			if ((i % 3 == 1 || i % 3 == 0) && i > 2) {
				glColor3f(0.8, 0.8, 0.8);
				glBegin(GL_LINES);
				glVertex2d(ptList[i].x, ptList[i].y);
				glVertex2d(ptList[i + 1].x, ptList[i + 1].y);
				glEnd();
				glColor3f(1, 0, 0);
			} else {
				glColor3f(0, 1, 0);
			}
			
			glBegin(GL_LINES);
			glVertex2d(ctList[i].x, ctList[i].y);
			glVertex2d(ctList[i + 1].x, ctList[i + 1].y);
			glEnd();
		}
	} else {
		glColor3f(0, 1, 0);
		for (int i = 0; i<nPt - 1; i++)
		{
			glColor3f(0, 1, 0);
			glBegin(GL_LINES);	
			glVertex2d(ptList[i].x, ptList[i].y);
			glVertex2d(ptList[i + 1].x, ptList[i + 1].y);
			glEnd();
		}
	}
	glPointSize(1);
	
}
void drawPt(void) {
	if (C1Continuity) {
		glPointSize(5);
		glBegin(GL_POINTS);
		for (int i = 0; i<nPt; i++)
		{
			glColor3f(0, 0, 0);
			glVertex2d(ctList[i].x, ctList[i].y);
			if (i % 3 == 1 && i > 2) {
				glColor3f(0.8, 0.8, 0.8);
				glVertex2d(ptList[i].x, ptList[i].y);
			}
		}
		glEnd();
		glPointSize(1);
	} else {
		glPointSize(5);
		glBegin(GL_POINTS);
		for (int i = 0; i<nPt; i++)
		{
			glColor3f(0, 0, 0);
			glVertex2d(ptList[i].x, ptList[i].y);
		}
		glEnd();
		glPointSize(1);
	}
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	if (displayObjects) {
		glClearColor(0.8* abs(sin(toRad(mAngle + 45))), 0.8* abs(sin(toRad(mAngle / 2))), 0.7* abs(cos(toRad(mAngle / 2 + 90))), 1.0);
	} else {
		glClearColor(0.8, 0.8, 0.8, 1.0);
	}
	//Load and calculate timer angles
	SYSTEMTIME mtimer;
	GetSystemTime(&mtimer);
	time_t current_time = time(0);
	struct tm * timeinfo = localtime(&current_time);

	millis = mtimer.wMilliseconds;
	mAngle = millis * 360 / 1000;


	if (displayBeizer) {
		drawBezier();
	}
	if(displayControlPoints)
	{
		drawPt();
	}

	if(displayControlLines)
	{
		drawLines();
	}
	if (displayTangentVectors) {

		drawTan();
	}
	if (displayObjects) {
		drawObject(mAngle);
	}

	glColor3f(0, 1, 0);

	

	glPopMatrix();
	glutSwapBuffers ();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,w,h,0); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void init(void)
{
	glClearColor(0.8,0.8,0.8, 1.0);
}

void readFile()
{

	std::ifstream file;
    file.open("savefile.txt");
	file >> nPt;

	if(nPt>MAXPTNO)
	{
		cout << "Error: File contains more than the maximum number of points." << endl;
		nPt = MAXPTNO;
	}

	for(int i=0;i<(2*nPt);i++)
	{
		file >> ptList[i].x;
		file >> ptList[i].y;
		file >> ctList[i].x;
		file >> ctList[i].y;
	}
    file.close();// is not necessary because the destructor closes the open file by default
}

void writeFile()
{
	std::ofstream file;
    file.open("savefile.txt");
    file << nPt << endl;

	for (int i = 0; i<(2 * nPt); i++)
	{
		file << ptList[i].x << " ";
		file << ptList[i].y << " ";
		file << ctList[i].x << " ";
		file << ctList[i].y << endl;
	}
    file.close();// is not necessary because the destructor closes the open file by default
}
void deletePrev(){
	if (nPt > 0) {
		nPt--;
	}
	
}
void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 'r':
		case 'R':
			readFile();
		break;

		case 'w':
		case 'W':
			writeFile();
		break;

		case 'T':
		case 't':
			displayTangentVectors = !displayTangentVectors;
		break;

		case 'o':
		case 'O':
			displayObjects = !displayObjects;
		break;

		case 'p':
		case 'P':
			displayControlPoints = !displayControlPoints;
		break;

		case 'L':
		case 'l':
			displayControlLines = !displayControlLines;
		break;

		case 'C':
		case 'c':
			C1Continuity = !C1Continuity;
		break;
		case 'D':
		case 'd':
			deletePrev();
			break;
		case 'e':
		case 'E':
			erasePt();

		break;

		case 's':
		case 'S':
			displayBeizer = !displayBeizer;

			break;


		case 27:
			exit(0);
		break;

		default:
		break;
	}

	glutPostRedisplay();
}



void mouse(int button, int state, int x, int y)
{
	/*button: GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON */
	/*state: GLUT_UP or GLUT_DOWN */
	enum
	{
		MOUSE_LEFT_BUTTON = 0,
		MOUSE_MIDDLE_BUTTON = 1,
		MOUSE_RIGHT_BUTTON = 2,
		MOUSE_SCROLL_UP = 3,
		MOUSE_SCROLL_DOWN = 4
	};
	if((button == MOUSE_LEFT_BUTTON)&&(state == GLUT_UP))
	{
		if(nPt==MAXPTNO)
		{
			cout << "Error: Exceeded the maximum number of points." << endl;
			return;
		}
		ptList[nPt].x=x;
		ptList[nPt].y=y;
		ctList[nPt].y = y;
		ctList[nPt].x = x;
		
		nPt++;
	}
	fixCont();
	glutPostRedisplay();
}
void idle()
{

	glutPostRedisplay();	//after updating, draw the screen again
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 4"<< endl<< endl;
	cout << "Left mouse click: Add a control point"<<endl;
	cout << "ESC: Quit" <<endl;
	cout << "P: Toggle displaying control points" <<endl;
	cout << "L: Toggle displaying control lines" <<endl;
	cout << "E: Erase all points (Clear)" << endl;
	cout << "C: Toggle C1 continuity" <<endl;	
	cout << "T: Toggle displaying tangent vectors" <<endl;
	cout << "O: Toggle displaying objects" <<endl;
	cout << "R: Read in control points from \"savefile.txt\"" <<endl;
	cout << "W: Write control points to \"savefile.txt\"" <<endl;
	cout << "D: Backspace" << endl;
	cout << "S: Toggle Beizer curve" << endl;
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow ("CS3241 Assignment 4");
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
