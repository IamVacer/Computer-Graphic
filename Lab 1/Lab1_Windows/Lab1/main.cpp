// CS3241Lab1.cpp : Defines the entry point for the console application.
#include <cmath>
#include <iostream>

/* Include header files depending on platform */
#ifdef _WIN32
	#include <glut.h>
	#define M_PI 3.14159
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/GLUT.h>
#endif

float alpha = 0.0, rage = -1;

void drawASmallTri()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-0.2, -0.2);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(0, 0.2);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.2, -0.2);
	glEnd();
}





void drawTriangle() {
	glBegin(GL_POLYGON);
		glColor3f(1, 0.4, 0);
		glVertex2f(0, 0);
		glVertex2f(-0.2, 2);
		glVertex2f(0.2, 2);
	glEnd();
}
void drawCircle()
{
	glPushMatrix();
	int i;
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;
	glColor3f(0, 0, 0); // black color
	glBegin(GL_POLYGON);
	for (i = 0; i<360; i++) // angle in degree
	{
		theta = (M_PI / 180)*i; // converting degree to radian
		nextTheta = (M_PI / 180)*(i + 1);
		x1 = sin(theta); y1 = cos(theta);
		x2 = sin(nextTheta); y2 = cos(nextTheta);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();
}

void drawEyes(int type)
{
	glPushMatrix();
	if (type == -1) {
		glLineWidth(120);
		glBegin(GL_LINE_STRIP);
		glVertex2f(-0.7, 0.07);
		glVertex2f(-0.8, 0.1);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex2f(-0.25, 0.07);
		glVertex2f(-0.15, 0.1);
		glEnd();
	}
	else if (type % 2 == 0) {
		glScalef(0.05, 0.05, 0.05);
		glTranslated(-4, 2, 0);
		drawCircle();
		glTranslated(-11, 0, 0);
		drawCircle();
	}
	else {
		glLineWidth(120);
		glBegin(GL_LINE_STRIP);
		glVertex2f(-0.7, 0.1);
		glVertex2f(-0.8, 0.1);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex2f(-0.25, 0.1);
		glVertex2f(-0.15, 0.1);
		glEnd();
	}
	
	glPopMatrix();

}

void drawMouth(int mode)
{
	if (mode % 2 == 0) {
		glPushMatrix();
		glLineWidth(120);
		glBegin(GL_LINE_STRIP);
		glVertex2f(-0.35, -0.1);
		glVertex2f(-0.55, -0.1);
		glEnd();
		glPopMatrix();

	}
	else {
		glBegin(GL_POLYGON);
		glColor3f(0, 0, 0);
		glVertex2f(-0.35, -0.05);
		glVertex2f(-0.55, -0.05);
		glVertex2f(-0.55, -0.15);
		glVertex2f(-0.35, -0.15);
		glEnd();
	}
	
}


void drawCicle(int start, int end)
{
	int i;
	double theta, nextTheta;
	double x1, y1;
	double x2, y2;
	glColor3f(0, 0, 0); // black color
	glLineWidth(100);
	glBegin(GL_LINE_STRIP);
	for (i = start; i<end; i++) // angle in degree
	{
		theta = (M_PI / 180)*i; // converting degree to radian
		nextTheta = (M_PI / 180)*(i + 1);
		x1 = sin(theta); y1 = cos(theta);
		x2 = sin(nextTheta); y2 = cos(nextTheta);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}

	glEnd();
}


void drawCheek()
{
	glPushMatrix();
	glTranslated(-0.2, 0, 0);
	glScalef(0.1, 0.25, 0.5);
	drawCicle(30, 150);
	glTranslated(-8.5, 0, 0);
	glScalef(-1, 1, 1);
	drawCicle(30, 150);
	glPopMatrix();
}
void drawHand(int status)
{
	glPushMatrix();
	if (status == -1) {
		glTranslatef(-0.7, 0.3, 0);
		glScalef(-0.3, -0.5, 1);
		drawCicle(0, 80);
		glTranslatef(-3.5, 0, 0);
		drawCicle(0, 80);
	}
	else if (status % 2 == 0) {
		glTranslatef(-0.0, 0.3, 0);
		glScalef(0.3, -0.5, 1);
		drawCicle(0, 80);
		glTranslatef(-3.5, 0, 0);
		drawCicle(0, 80);
	}
	

	glPopMatrix();
}

void drawTable(int status) {
	float base1 = 0.05, base2 = 0.45;
	if (status % 2 == 1) {
		base1 = 0;
		base2 = 0.5;
	}
	glPushMatrix();
	glLineWidth(120);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.1, 0.05);
	glVertex2f(0.6, 0.05);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(0.05, 0.05);
	glVertex2f(base1, -0.10);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(0.45, 0.05);
	glVertex2f(base2, -0.10);
	glEnd();

	glPopMatrix();
}
void drawFace(int status)
{
	glPushMatrix();
	glTranslatef(-0.4, 0, 0);
	glScalef(0.5, 0.5,0.5);
	drawCheek();
	drawEyes(status);
	drawMouth(0);
	drawHand(-1);
	glPopMatrix();

}
void drawAngryFace(int status)
{
	glPushMatrix();
	if (status % 2 == 0) {
		glScalef(0.9, 1, 1);
	}
	glTranslatef(-0.4, 0, 0);
	glScalef(0.5, 0.5, 0.5);
	drawCheek();
	drawEyes(-1);
	drawMouth(status + 1);
	drawHand(0);
	glPopMatrix();

}
void drawFlyingTable(int status) {
	glPushMatrix();
	glTranslatef(0.2, 0.4, 0);
	glRotatef(-30, 0, 0, 1);
	drawTable(status);
	glPopMatrix();
}
void drawStageOneNormal(int status)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	if (status == -1) {}

	else {
		drawFace(status);
		drawTable(0);
	}
	
}
void drawBackground(int rotate) {
	glPushMatrix();
	if (rotate % 2 == 1) {
		for (int i = 0; i < 8; i++) {
			drawTriangle();
			glRotatef(45, 0, 0, 1);
		}
	}
	else {
		glRotatef(45/2, 0, 0, 1);
		for (int i = 0; i < 8; i++) {
			drawTriangle();
			glRotatef(45, 0, 0, 1);
			}
			
	}

	
	glPopMatrix();

}
void drawStageTwoRage(int rage)
{
	if (rage == -1){}
	else {
		drawBackground(rage);
		glClearColor(1.0, 0, 0, 1);
		drawAngryFace(rage);
		drawFlyingTable(rage);
	} 

}
void mydisplay()
{

	glClear(GL_COLOR_BUFFER_BIT);
	//glRotatef(alpha, 0, 0, 1);
	drawStageOneNormal(alpha);
	drawStageTwoRage(rage);
	glFlush();
}


void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glShadeModel(GL_SMOOTH);
}

void keyboard(unsigned char key, int x, int y)
{
	//keys to control scaling - k
	//keys to control rotation - alpha
	switch (key) {

	case 'a':
		glClearColor(1.0, 1.0, 1.0, 1.0);
		alpha++;
		rage = -1;
		glutPostRedisplay();
		break;

	case 's':
		glClearColor(1.0, 0, 0, 1);
		alpha = -1;
		rage++;
		glutPostRedisplay();
		break;


	default:
		break;
	}
}
int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}

