// CS3241Lab3.cpp : Defines the entry point for the console application.
//#include <cmath>
#include "math.h"
#include <iostream>
#include <fstream>

#ifdef _WIN32
	#include <Windows.h>
	#include "glut.h"
	#define M_PI 3.141592654
	#include <math.h>
	#include <time.h>
	#include <sys/timeb.h>
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/GLUT.h>
#endif

// global variable

bool m_Smooth = true;
bool m_Highlight = true;
bool pause = true;
GLfloat angle = 0;   /* in degrees */
GLfloat angle2 = 0;   /* in degrees */
GLfloat zoom = -0.2;
int mouseButton = 0;
int moving, startx, starty;
double hrAngle;
double minAngle;
double mAngle;
double secAngle;
int starArrLength = 3000;
int bpm = 72;
double starArr[3000]; //coordinates of stars in the default window

//Gold
float ambient_1[] = { 0.24725, 0.1995, 0.0745, 1.0f };
float diffuse_1[] = { 0.75164, 0.60648, 0.22648, 1.0f };
float specular_1[] = { 0.628281, 0.555802, 0.366065, 1.0f };
float shininess_1 = 51.2;
float emission_1[] = { 0.0f, 0.0f, 0.0f, 0.0f };
// Turquoise
float ambient_2[] = { 0.1, 0.18725, 0.1745, 1.0f };
float diffuse_2[] = { 0.396, 0.74151, 0.69102, 1.0f };
float specular_2[] = { 0.297254, 0.30829, 0.306678, 1.0f };
float shininess_2 = 12.8;
// Ruby
float ambient_3[] = { 0.1745, 0.01175, 0.01175, 1.0f };
float diffuse_3[] = { 0.61424, 0.04136, 0.04136, 1.0f };
float specular_3[] = { 0.727811, 0.626959, 0.626959, 1.0f };
float shininess_3 = 76.8;

// Emerald
float ambient_4[] = { 0.0215f, 0.1745f, 0.0215f, 1.0f };
float diffuse_4[] = { 0.07568f, 0.61424f, 0.07568f, 1.0f };
float specular_4[] = { 0.633f, 0.727811f, 0.633f, 1.0f };
float shininess_4 = 27.89743616f;


float reset_emission[] = { 0.0f, 0.0f, 0.0f, 0.0f };

//No highlight
float no_shininess = 0.0f;
float no_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };

#define NO_OBJECT 4;
int current_object = 0;

using namespace std;

void setupLighting()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	// Lights, material properties
    GLfloat	ambientProperties[]  = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat	diffuseProperties[]  = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat	specularProperties[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightPosition[] = {-100.0f,100.0f,100.0f,1.0f};
	
    glClearDepth( 1.0 );

    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularProperties);
	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition);
	
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

	// Default : lighting
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

}

//================= Material =====================================//
void drawSphere1(double r)
{

    float mat_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    float mat_diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
	float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};

	float shiny_specular[] = { 0.4f, 0.4f, 0.6f, 1.0f };
	float shiny_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	float shiny_diffuse[] = { 0.1f, 0.5f, 0.8f, 1.0f };
	float shininess = 100.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_specular);
	if(m_Highlight)
	{
		// your codes for highlight here
		glMaterialfv(GL_FRONT, GL_SPECULAR, shiny_specular);
		glMaterialfv(GL_FRONT, GL_AMBIENT, shiny_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, shiny_diffuse);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
		//glMaterialfv(GL_FRONT, GL_EMISSION, mat_specular);
	} else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	}

	
    int i,j;
	int n = 20;
    for(i=0;i<n;i++)
		for(j=0;j<2*n;j++)
		if(m_Smooth)
		{
			glBegin(GL_POLYGON);

			    // the normal of each vertex is actaully its own coordinates normalized for a sphere

			    // your normal here
				glNormal3d(sin(i*M_PI / n)*cos(j*M_PI / n), cos(i*M_PI / n)*cos(j*M_PI / n), sin(j*M_PI / n));
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n), r*cos(i*M_PI/n)*cos(j*M_PI/n), r*sin(j*M_PI/n));

			    // your normal here
				glNormal3d(sin((i + 1)*M_PI / n)*cos(j*M_PI / n), cos((i + 1)*M_PI / n)*cos(j*M_PI / n), sin(j*M_PI / n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));

			    // your normal here
				glNormal3d(sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), sin((j + 1)*M_PI / n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));

			    // your normal here
				glNormal3d(sin(i*M_PI / n)*cos((j + 1)*M_PI / n), cos(i*M_PI / n)*cos((j + 1)*M_PI / n), sin((j + 1)*M_PI / n));
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
 			glEnd();
		} else	{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),cos((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),sin((j+0.5)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
 			glEnd();
		}

}

void drawSphere2(double r)
{

	float mat_specular[] = { 0.992157f, 0.941176f, 0.807843f, 1.0f };
	float mat_ambient[] = { 0.329412f, 0.223529f, 0.1f, 0.027451f };
	float mat_diffuse[] = { 0.780392f, 0.568627f, 0.113725f, 1.0f };

	float mat_emission[] = { 0.1f, 0.1f, 0.1f, 0.0f };
	float no_shininess = 27.89743616;

	float shiny_specular[] = { 0.4f, 0.4f, 0.6f, 1.0f };
	float shiny_ambient[] = { 0.8f, 0.5f, 0.1f, 1.0f };
	float shiny_diffuse[] = { 0.8f, 0.5f, 0.1f, 1.0f };
	float shininess = 100.0f;
	float shiny_emission[] = { 0.1f, 0.1f, 0.1f, 0.0f };
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	if (m_Highlight)
	{
		// your codes for highlight here
		glMaterialfv(GL_FRONT, GL_SPECULAR, shiny_specular);
		glMaterialfv(GL_FRONT, GL_AMBIENT, shiny_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, shiny_diffuse);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, shiny_emission);
		//glMaterialfv(GL_FRONT, GL_EMISSION, mat_specular);
	}
	else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	}


	int i, j;
	int n = 20;
	for (i = 0; i<n; i++)
		for (j = 0; j<2 * n; j++)
			if (m_Smooth)
			{
				glBegin(GL_POLYGON);

				// the normal of each vertex is actaully its own coordinates normalized for a sphere

				// your normal here
				glNormal3d(sin(i*M_PI / n)*cos(j*M_PI / n), cos(i*M_PI / n)*cos(j*M_PI / n), sin(j*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos(j*M_PI / n), r*cos(i*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));

				// your normal here
				glNormal3d(sin((i + 1)*M_PI / n)*cos(j*M_PI / n), cos((i + 1)*M_PI / n)*cos(j*M_PI / n), sin(j*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos(j*M_PI / n), r*cos((i + 1)*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));

				// your normal here
				glNormal3d(sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), sin((j + 1)*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));

				// your normal here
				glNormal3d(sin(i*M_PI / n)*cos((j + 1)*M_PI / n), cos(i*M_PI / n)*cos((j + 1)*M_PI / n), sin((j + 1)*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos((j + 1)*M_PI / n), r*cos(i*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
				glEnd();
			}
			else	{
				glBegin(GL_POLYGON);
				// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glNormal3d(sin((i + 0.5)*M_PI / n)*cos((j + 0.5)*M_PI / n), cos((i + 0.5)*M_PI / n)*cos((j + 0.5)*M_PI / n), sin((j + 0.5)*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos(j*M_PI / n), r*cos(i*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos(j*M_PI / n), r*cos((i + 1)*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos((j + 1)*M_PI / n), r*cos(i*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
				glEnd();
			}

}
void drawSphereEmerald(double r)
{
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_4);
	glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_4);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_4);
	glMaterialfv(GL_FRONT, GL_EMISSION, reset_emission);

	if (m_Highlight)
	{
		// your codes for highlight here
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_4);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess_4);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_4);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_4);
	}
	else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_4);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_4);
	}

	int i, j;
	int n = 20;
	for (i = 0; i<n; i++)
		for (j = 0; j<2 * n; j++)
			if (m_Smooth)
			{
				glBegin(GL_POLYGON);

				// the normal of each vertex is actaully its own coordinates normalized for a sphere

				// your normal here
				glNormal3d(sin(i*M_PI / n)*cos(j*M_PI / n), cos(i*M_PI / n)*cos(j*M_PI / n), sin(j*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos(j*M_PI / n), r*cos(i*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));

				// your normal here
				glNormal3d(sin((i + 1)*M_PI / n)*cos(j*M_PI / n), cos((i + 1)*M_PI / n)*cos(j*M_PI / n), sin(j*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos(j*M_PI / n), r*cos((i + 1)*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));

				// your normal here
				glNormal3d(sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), sin((j + 1)*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));

				// your normal here
				glNormal3d(sin(i*M_PI / n)*cos((j + 1)*M_PI / n), cos(i*M_PI / n)*cos((j + 1)*M_PI / n), sin((j + 1)*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos((j + 1)*M_PI / n), r*cos(i*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
				glEnd();
			}
			else	{
				glBegin(GL_POLYGON);
				// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glNormal3d(sin((i + 0.5)*M_PI / n)*cos((j + 0.5)*M_PI / n), cos((i + 0.5)*M_PI / n)*cos((j + 0.5)*M_PI / n), sin((j + 0.5)*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos(j*M_PI / n), r*cos(i*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos(j*M_PI / n), r*cos((i + 1)*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos((j + 1)*M_PI / n), r*cos(i*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
				glEnd();
			}

}

void drawSphereTurquoise(double r)
{
	if (m_Highlight)
	{
		// your codes for highlight here
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_4);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess_4);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_4);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_4);
	}
	else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_4);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_4);
	}

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_2);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess_2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_2);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_2);
	glMaterialfv(GL_FRONT, GL_EMISSION, reset_emission);

	int i, j;
	int n = 20;
	for (i = 0; i<n; i++)
		for (j = 0; j<2 * n; j++)
			if (m_Smooth)
			{
				glBegin(GL_POLYGON);

				// the normal of each vertex is actaully its own coordinates normalized for a sphere

				// your normal here
				glNormal3d(sin(i*M_PI / n)*cos(j*M_PI / n), cos(i*M_PI / n)*cos(j*M_PI / n), sin(j*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos(j*M_PI / n), r*cos(i*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));

				// your normal here
				glNormal3d(sin((i + 1)*M_PI / n)*cos(j*M_PI / n), cos((i + 1)*M_PI / n)*cos(j*M_PI / n), sin(j*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos(j*M_PI / n), r*cos((i + 1)*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));

				// your normal here
				glNormal3d(sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), sin((j + 1)*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));

				// your normal here
				glNormal3d(sin(i*M_PI / n)*cos((j + 1)*M_PI / n), cos(i*M_PI / n)*cos((j + 1)*M_PI / n), sin((j + 1)*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos((j + 1)*M_PI / n), r*cos(i*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
				glEnd();
			}
			else	{
				glBegin(GL_POLYGON);
				// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glNormal3d(sin((i + 0.5)*M_PI / n)*cos((j + 0.5)*M_PI / n), cos((i + 0.5)*M_PI / n)*cos((j + 0.5)*M_PI / n), sin((j + 0.5)*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos(j*M_PI / n), r*cos(i*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos(j*M_PI / n), r*cos((i + 1)*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos((j + 1)*M_PI / n), r*cos(i*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
				glEnd();
			}

}void drawSphereGold(double r)
{
	if (m_Highlight)
	{
		// your codes for highlight here
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_1);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess_1);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_1);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_1);
	}
	else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_1);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_1);
	}


	int i, j;
	int n = 20;
	for (i = 0; i<n; i++)
		for (j = 0; j<2 * n; j++)
			if (m_Smooth)
			{
				glBegin(GL_POLYGON);

				// the normal of each vertex is actaully its own coordinates normalized for a sphere

				// your normal here
				glNormal3d(sin(i*M_PI / n)*cos(j*M_PI / n), cos(i*M_PI / n)*cos(j*M_PI / n), sin(j*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos(j*M_PI / n), r*cos(i*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));

				// your normal here
				glNormal3d(sin((i + 1)*M_PI / n)*cos(j*M_PI / n), cos((i + 1)*M_PI / n)*cos(j*M_PI / n), sin(j*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos(j*M_PI / n), r*cos((i + 1)*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));

				// your normal here
				glNormal3d(sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), sin((j + 1)*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));

				// your normal here
				glNormal3d(sin(i*M_PI / n)*cos((j + 1)*M_PI / n), cos(i*M_PI / n)*cos((j + 1)*M_PI / n), sin((j + 1)*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos((j + 1)*M_PI / n), r*cos(i*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
				glEnd();
			}
			else	{
				glBegin(GL_POLYGON);
				// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glNormal3d(sin((i + 0.5)*M_PI / n)*cos((j + 0.5)*M_PI / n), cos((i + 0.5)*M_PI / n)*cos((j + 0.5)*M_PI / n), sin((j + 0.5)*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos(j*M_PI / n), r*cos(i*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos(j*M_PI / n), r*cos((i + 1)*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos((j + 1)*M_PI / n), r*cos(i*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
				glEnd();
			}

}

void drawSphereRuby(double r)
{

	glMaterialfv(GL_FRONT, GL_EMISSION, reset_emission);
	if (m_Highlight)
	{
		// your codes for highlight here
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_3);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess_3);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_3);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_3);
	}
	else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_3);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_3);
	}



	int i, j;
	int n = 20;
	for (i = 0; i<n; i++)
		for (j = 0; j<2 * n; j++)
			if (m_Smooth)
			{
				glBegin(GL_POLYGON);

				// the normal of each vertex is actaully its own coordinates normalized for a sphere

				// your normal here
				glNormal3d(sin(i*M_PI / n)*cos(j*M_PI / n), cos(i*M_PI / n)*cos(j*M_PI / n), sin(j*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos(j*M_PI / n), r*cos(i*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));

				// your normal here
				glNormal3d(sin((i + 1)*M_PI / n)*cos(j*M_PI / n), cos((i + 1)*M_PI / n)*cos(j*M_PI / n), sin(j*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos(j*M_PI / n), r*cos((i + 1)*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));

				// your normal here
				glNormal3d(sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), sin((j + 1)*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));

				// your normal here
				glNormal3d(sin(i*M_PI / n)*cos((j + 1)*M_PI / n), cos(i*M_PI / n)*cos((j + 1)*M_PI / n), sin((j + 1)*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos((j + 1)*M_PI / n), r*cos(i*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
				glEnd();
			}
			else	{
				glBegin(GL_POLYGON);
				// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glNormal3d(sin((i + 0.5)*M_PI / n)*cos((j + 0.5)*M_PI / n), cos((i + 0.5)*M_PI / n)*cos((j + 0.5)*M_PI / n), sin((j + 0.5)*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos(j*M_PI / n), r*cos(i*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos(j*M_PI / n), r*cos((i + 1)*M_PI / n)*cos(j*M_PI / n), r*sin(j*M_PI / n));
				glVertex3d(r*sin((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*cos((i + 1)*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
				glVertex3d(r*sin(i*M_PI / n)*cos((j + 1)*M_PI / n), r*cos(i*M_PI / n)*cos((j + 1)*M_PI / n), r*sin((j + 1)*M_PI / n));
				glEnd();
			}

}

void drawTemplate(double r)
{
	float mat_ambient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
	float mat_diffuse[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
	float mat_specular[] = { 0.628281f, 0.555802f, 0.366065f, 1.0f };
	float no_shininess = 51.2;


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_EMISSION, reset_emission);



	int i, j;
	int n = 20;
	for (i = 0; i<n; i++)
		for (j = 0; j < 2 * n; j++) {
			double theta1a = i*M_PI / n;
			double theta1b = j*M_PI / n;

			double theta2a = (i + 1)*M_PI / n;
			double theta2b = (j + 1)*M_PI / n;

			double thetaA = (i + 0.5)*M_PI / n;
			double thetaB = (j + 0.5)*M_PI / n;

			if (m_Smooth)
			{
				glBegin(GL_POLYGON);

				// the normal of each vertex is actaully its own coordinates normalized for a sphere

				// your normal here
				glNormal3d(sin(theta1a)*cos(theta1b), cos(theta1a)*cos(theta1b), sin(theta1b));
				glVertex3d(r*sin(theta1a)*cos(theta1b), r*cos(theta1a)*cos(theta1b), r*sin(theta1b));

				// your normal here
				glNormal3d(sin(theta2a)*cos(theta1b), cos(theta2a)*cos(theta1b), sin(theta1b));
				glVertex3d(r*sin(theta2a)*cos(theta1b), r*cos(theta2a)*cos(theta1b), r*sin(theta1b));

				// your normal here
				glNormal3d(sin(theta2a)*cos(theta2b), cos(theta2a)*cos(theta2b), sin(theta2b));
				glVertex3d(r*sin(theta2a)*cos(theta2b), r*cos(theta2a)*cos(theta2b), r*sin(theta2b));

				// your normal here
				glNormal3d(sin(theta1a)*cos(theta2b), cos(theta1a)*cos(theta2b), sin(theta2b));
				glVertex3d(r*sin(theta1a)*cos(theta2b), r*cos(theta1a)*cos(theta2b), r*sin(theta2b));
				glEnd();
			}
			else	{
				glBegin(GL_POLYGON);
				// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glNormal3d(sin(thetaA)*cos(thetaB), cos(thetaA)*cos(thetaB), sin(thetaB));

				glVertex3d(r*sin(theta1a)*cos(theta1b), r*cos(theta1a)*cos(theta1b), r*sin(theta1b));
				glVertex3d(r*sin(theta2a)*cos(theta1b), r*cos(theta2a)*cos(theta1b), r*sin(theta1b));
				glVertex3d(r*sin(theta2a)*cos(theta2b), r*cos(theta2a)*cos(theta2b), r*sin(theta2b));
				glVertex3d(r*sin(theta1a)*cos(theta2b), r*cos(theta1a)*cos(theta2b), r*sin(theta2b));
				glEnd();
			}
		}
}

void drawRandomBase(double r)
{
	float mat_ambient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
	float mat_diffuse[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
	float mat_specular[] = { 0.628281f, 0.555802f, 0.366065f, 1.0f };
	float no_shininess = 51.2;


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);



	int i, j;
	int n = 20;
	for (i = 0; i<n; i++)
		for (j = 0; j < 2 * n; j++) {
			double theta1a = i*M_PI / n;
			double theta1b = j*M_PI / n;

			double theta2a = (i + 1)*M_PI / n;
			double theta2b = (j + 1)*M_PI / n;

			double thetaA = (i + 0.5)*M_PI / n;
			double thetaB = (j + 0.5)*M_PI / n;

			if (m_Smooth)
			{
				glBegin(GL_POLYGON);

				// the normal of each vertex is actaully its own coordinates normalized for a sphere
				
				glNormal3d(cos(thetaB)*(6 - (5 / 4 + sin(1 * thetaA))*sin(thetaA - 1 * thetaB)),
					(6 - (5 / 4 + sin(1 * thetaA))*sin(thetaA - 1 * thetaB))*sin(thetaB),
					-cos(thetaA - 1 * thetaB)*(5 / 4 + sin(1 * thetaA)));
				
				glVertex3d(cos(theta1b)*(6 - (5 / 4 + sin(1 * theta1a))*sin(theta1a - 1 * theta1b)),
					(6 - (5 / 4 + sin(1 * theta1a))*sin(theta1a - 1 * theta1b))*sin(theta1b),
					-cos(theta1a - 1 * theta1b)*(5 / 4 + sin(1 * theta1a)));
				
				glVertex3d(cos(theta2b)*(6 - (5 / 4 + sin(1 * theta1a))*sin(theta1a - 1 * theta2b)),
					(6 - (5 / 4 + sin(1 * theta1a))*sin(theta1a - 1 * theta2b))*sin(theta2b),
					-cos(theta1a - 1 * theta2b)*(5 / 4 + sin(1 * theta1a)));
				
				glVertex3d(cos(theta2b)*(6 - (5 / 4 + sin(1 * theta2a))*sin(theta2a - 1 * theta2b)),
					(6 - (5 / 4 + sin(1 * theta2a))*sin(theta2a - 1 * theta2b))*sin(theta2b),
					-cos(theta2a - 1 * theta2b)*(5 / 4 + sin(1 * theta2a)));

				glVertex3d(cos(theta1b)*(6 - (5 / 4 + sin(1 * theta2a))*sin(theta2a - 1 * theta1b)),
					(6 - (5 / 4 + sin(1 * theta2a))*sin(theta2a - 1 * theta1b))*sin(theta1b),
					-cos(theta2a - 1 * theta1b)*(5 / 4 + sin(1 * theta2a)));
				glEnd();
			}
			else	{
				glBegin(GL_POLYGON);
				// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glNormal3d(cos(thetaB)*(6 - (5 / 4 + sin(1 * thetaA))*sin(thetaA - 1 * thetaB)),
					(6 - (5 / 4 + sin(1 * thetaA))*sin(thetaA - 1 * thetaB))*sin(thetaB),
					-cos(thetaA - 1 * thetaB)*(5 / 4 + sin(1 * thetaA)));

				glVertex3d(cos(theta1b)*(6 - (5 / 4 + sin(1 * theta1a))*sin(theta1a - 1 * theta1b)),
					(6 - (5 / 4 + sin(1 * theta1a))*sin(theta1a - 1 * theta1b))*sin(theta1b),
					-cos(theta1a - 1 * theta1b)*(5 / 4 + sin(1 * theta1a)));

				glVertex3d(cos(theta2b)*(6 - (5 / 4 + sin(1 * theta1a))*sin(theta1a - 1 * theta2b)),
					(6 - (5 / 4 + sin(1 * theta1a))*sin(theta1a - 1 * theta2b))*sin(theta2b),
					-cos(theta1a - 1 * theta2b)*(5 / 4 + sin(1 * theta1a)));

				glVertex3d(cos(theta2b)*(6 - (5 / 4 + sin(1 * theta2a))*sin(theta2a - 1 * theta2b)),
					(6 - (5 / 4 + sin(1 * theta2a))*sin(theta2a - 1 * theta2b))*sin(theta2b),
					-cos(theta1a - 1 * theta2b)*(5 / 4 + sin(1 * theta2a)));

				glVertex3d(cos(theta1b)*(6 - (5 / 4 + sin(1 * theta2a))*sin(theta2a - 1 * theta1b)),
					(6 - (5 / 4 + sin(1 * theta2a))*sin(theta2a - 1 * theta1b))*sin(theta1b),
					-cos(theta2a - 1 * theta1b)*(5 / 4 + sin(1 * theta2a)));

				glEnd();
			}
		}
}
void drawCoolShit(double r, int n, float ambient[], float diffuse[], float specular[], float shininess)
{
	

	glMaterialfv(GL_FRONT, GL_EMISSION, emission_1);
	if (m_Highlight)
	{
		// your codes for highlight here
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	}
	else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	}



	int i, j;

	for (i = 0; i<n; i++)
		for (j = 0; j < 2 * n; j++) {
			double theta1a = i*M_PI / n;
			double theta1b = j*M_PI / n;

			double theta2a = (i + 1)*M_PI / n;
			double theta2b = (j + 1)*M_PI / n;

			double thetaA = (i + 0.5)*M_PI / n;
			double thetaB = (j + 0.5)*M_PI / n;

			double side = 3;
			//q is radious
			double q = r + 1;
			//p is thickness
			double p = 5/4;
			if (m_Smooth)
			{
				glBegin(GL_POLYGON);

				// the normal of each vertex is actaully its own coordinates normalized for a sphere

				glNormal3d(cos(theta1b)*(q - (p + sin(side * theta1a))*sin(theta1a - side * theta1b)),
					(q - (p + sin(side * theta1a))*sin(theta1a - side * theta1b))*sin(theta1b),
					-cos(theta1a - side * theta1b)*(p + sin(side * theta1a)));
				glVertex3d(cos(theta1b)*(q - (p + sin(side * theta1a))*sin(theta1a - side * theta1b)),
					(q - (p + sin(side * theta1a))*sin(theta1a - side * theta1b))*sin(theta1b),
					-cos(theta1a - side * theta1b)*(p + sin(side * theta1a)));

				glNormal3d(cos(theta2b)*(q - (p + sin(side * theta1a))*sin(theta1a - side * theta2b)),
					(q - (p + sin(side * theta1a))*sin(theta1a - side * theta2b))*sin(theta2b),
					-cos(theta1a - side * theta2b)*(p + sin(side * theta1a)));
				glVertex3d(cos(theta2b)*(q - (p + sin(side * theta1a))*sin(theta1a - side * theta2b)),
					(q - (p + sin(side * theta1a))*sin(theta1a - side * theta2b))*sin(theta2b),
					-cos(theta1a - side * theta2b)*(p + sin(side * theta1a)));

				glNormal3d(cos(theta2b)*(q - (p + sin(side * theta2a))*sin(theta2a - side * theta2b)),
					(q - (p + sin(side * theta2a))*sin(theta2a - side * theta2b))*sin(theta2b),
					-cos(theta2a - side * theta2b)*(p + sin(side * theta2a)));
				glVertex3d(cos(theta2b)*(q - (p + sin(side * theta2a))*sin(theta2a - side * theta2b)),
					(q - (p + sin(side * theta2a))*sin(theta2a - side * theta2b))*sin(theta2b),
					-cos(theta2a - side * theta2b)*(p + sin(side * theta2a)));

				glNormal3d(cos(theta1b)*(q - (p + sin(side * theta2a))*sin(theta2a - side * theta1b)),
					(q - (p + sin(side * theta2a))*sin(theta2a - side * theta1b))*sin(theta1b),
					-cos(theta2a - side * theta1b)*(p + sin(side * theta2a)));
				glVertex3d(cos(theta1b)*(q - (p + sin(side * theta2a))*sin(theta2a - side * theta1b)),
					(q - (p + sin(side * theta2a))*sin(theta2a - side * theta1b))*sin(theta1b),
					-cos(theta2a - side * theta1b)*(p + sin(side * theta2a)));

				glEnd();
			} else	{
				glBegin(GL_POLYGON);
				// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glNormal3d(cos(thetaB)*(q - (p + sin(side * thetaA))*sin(thetaA - side * thetaB)),
					(q - (p + sin(side * thetaA))*sin(thetaA - side * thetaB))*sin(thetaB),
					-cos(thetaA - side * thetaB)*(p + sin(side * thetaA)));

				glVertex3d(cos(theta1b)*(q - (p + sin(side * theta1a))*sin(theta1a - side * theta1b)),
					(q - (p + sin(side * theta1a))*sin(theta1a - side * theta1b))*sin(theta1b),
					-cos(theta1a - side * theta1b)*(p + sin(side * theta1a)));

				glVertex3d(cos(theta2b)*(q - (p + sin(side * theta1a))*sin(theta1a - side * theta2b)),
					(q - (p + sin(side * theta1a))*sin(theta1a - side * theta2b))*sin(theta2b),
					-cos(theta1a - side * theta2b)*(p + sin(side * theta1a)));

				glVertex3d(cos(theta2b)*(q - (p + sin(side * theta2a))*sin(theta2a - side * theta2b)),
					(q - (p + sin(side * theta2a))*sin(theta2a - side * theta2b))*sin(theta2b),
					-cos(theta2a - side * theta2b)*(p + sin(side * theta2a)));

				glVertex3d(cos(theta1b)*(q - (p + sin(side * theta2a))*sin(theta2a - side * theta1b)),
					(q - (p + sin(side * theta2a))*sin(theta2a - side * theta1b))*sin(theta1b),
					-cos(theta2a - side * theta1b)*(p + sin(side * theta2a)));
				glEnd();
			}
		}
}
double toRad(double degree) {
	return degree * (M_PI / 180);
}

//================= SOLAR =====================================//
void starPlot(int choice){
	glPushMatrix();
	double x, y;
	glBegin(GL_POINTS);
	if (choice == 1) {
		glMaterialfv(GL_FRONT, GL_EMISSION, specular_1);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_1);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess_1);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_1);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_1);
	}
	else {
		glMaterialfv(GL_FRONT, GL_EMISSION, specular_2);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_2);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess_2);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_2);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_2);
	}
	


	for (int i = 0; i < starArrLength; i += 6) {
		glVertex3d(starArr[i] / 100, starArr[i + 1] / 100, starArr[i + 2] / 100);
	}
	glEnd();
	glPopMatrix();
}
void planet1(double i, double second)
{
	glPushMatrix();
	double theta, theta2, r, g;
	double x1, y1;
	double x2, y2;
	glLineWidth(1);

	theta = (M_PI / 180)*i; // converting degree to radian
	glColor3f(1.0, 1.0, 0.0);
	x1 = 3 * sin(theta); y1 = 3 * cos(theta);

	glPopAttrib();
	glTranslated(x1, y1, 0);

	drawSphere2(0.5);
	theta2 = (M_PI / 180)*i*20; // converting degree to radian
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
	glTranslated(x2, y2, y2);

	drawSphere1(0.1);
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

	drawSphereGold(0.5);

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

	drawSphere2(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x1, y1, 0);
	glRotated(180 + second, 0, 0, 1);
	glTranslated(x2, y2, 0);

	drawSphere2(0.3);
	glPopMatrix();

}
void planet3(double i, double second)
//This planet is bouncing on the sun
{
	glPushMatrix();
	double theta, height, theta2, theta3, theta4;
	theta = (M_PI / 180)*(i * 36); // converting degree to radian
	glRotated(i * 7, 0, 1, 0);
	height = 2 * cos(theta);
	if (height < 0) {
		height = -height;
	}
	glTranslated(0, 0, 2);
	glTranslated(0, 0, height);
	theta2 = (M_PI / 180)*(i * 42);
	theta3 = (M_PI / 180)*(second * 36);
	theta4 = (M_PI / 180)*(i * 76);
	drawSphereEmerald(0.3);

	glPopMatrix();

}
void planet4(double i, double second, double minute)
//This planet has a moon that orbits in a "infinite" like path
{
	glPushMatrix();
	double theta, theta2, r, g;
	double x1, y1;
	double x2, y2;
	glLineWidth(1);

	theta = (M_PI / 180)*i; // converting degree to radian
	x1 = 10 * sin(theta + M_PI); y1 = 10 * cos(theta + M_PI);

	glPopAttrib();
	glTranslated(x1, 0, y1);

	drawSphereTurquoise(0.3);
	theta2 = (M_PI / 180)*i * 40; // converting degree to radian
	x2 = 0.8 * cos(theta2);
	y2 = 0.8* sin(theta2);
	glRotatef(second,0,0,1);
	glScalef(0.2, 0.2, 0.2);
	drawCoolShit(5, 70, ambient_1, diffuse_1, specular_1, shininess_1);
	glPopMatrix();

}

void planet5(double i, double second, double minute)
//This planet has a moon that orbits in a "infinite" like path
{
	glPushMatrix();
	double theta, theta2, r, g;
	double x1, y1;
	double x2, y2;
	glLineWidth(1);

	theta = (M_PI / 180)*i; // converting degree to radian
	x1 = 9 * sin(theta); y1 = 9 * cos(theta);

	glPopAttrib();
	glTranslated(x1, 0, y1);

	drawSphereGold(0.3);
	theta2 = (M_PI / 180)*i * 40; // converting degree to radian
	x2 = 0.8 * cos(theta2);
	y2 = 0.8* sin(theta2);
	glRotatef(second, 0, 0, 1);
	glScalef(0.2, 0.2, 0.2);
	drawCoolShit(5, 70, ambient_2, diffuse_2, specular_2, shininess_2);
	glPopMatrix();

}

void loadPlanet(double second, double milli, double minute) {
	double theta3 = (M_PI / 180)*(second * 72);
	double orbit2 = fmod(second * 34, 360);//to create variations of orbit timing
	drawSphereRuby(1 * abs(sin(theta3)) + 0.6);

	//planet1(second, milli);
	glPushMatrix();
	for (int i = 0; i < 4; i++) {
		glRotated(i * 90, 0, 0, 1);
		planet2(second, orbit2);
	}
	glPopMatrix();

	glPushMatrix();

	for (int i = 0; i < 2; i++) {
		glRotated(i * 180, 0, 1, 0);
		planet3(second, orbit2);
	}

	glPopMatrix();
	planet4(second, milli, minute);
	planet5(second, milli, minute);
	starPlot(2);

}
//================= Cool =====================================//
void loadCoolBlock(double minute, int chain) {
	double theta3 = (M_PI / 180)*(minute * 72 * 60);
	//drawSphere1(1 * abs(sin(theta3)) + 0.6);
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	for (int i = 0; i < chain; i++) {
		glPushMatrix();
		drawCoolShit(5, 70, ambient_2, diffuse_2, specular_2, shininess_2);
		glRotatef(90, 0, 0, 1);
		drawCoolShit(5, 70, ambient_1, diffuse_1, specular_1, shininess_1);
		glTranslatef(3, 7, 0);
		glRotatef(90, 0, 1, 0);
		
		glRotatef(30, 1, 0, 0);
		
		
		drawCoolShit(5, 70, ambient_2, diffuse_2, specular_2, shininess_2);
		glRotatef(90, 0, 0, 1);
		drawCoolShit(5, 70, ambient_1, diffuse_1, specular_1, shininess_1);
		glPopMatrix();
		glRotatef(30, 0, 0, 1);
		glRotatef(4, 1, 0, 0);
		glTranslatef(14, -6, 0);
		
	}
	glPopMatrix();
}


void loadCoolStructure(double minute) {

	//drawSphere1(1 * abs(sin(theta3)) + 0.6);
	glPushMatrix();
	glTranslatef(-1, -7.2, -20);
	glRotatef(-8, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);
	loadCoolBlock(minute,72);
	glPopMatrix();
	glPushMatrix();
	
	/*


	glTranslatef(0, 8, 0);

	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	drawCoolShit(5, 70, ambient_2, diffuse_2, specular_2, shininess_2);
	glRotatef(90, 0, 0, 1);
	*/

	glPopMatrix();
}

//================= MAIN =====================================//
void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

		//Load and calculate timer angles
		SYSTEMTIME mtimer;
		GetSystemTime(&mtimer);
		time_t current_time = time(0);
		struct tm * timeinfo = localtime(&current_time);

		double millis = mtimer.wMilliseconds;
		double mAngle = millis * 360 / 1000;

		int seconds = (float)timeinfo->tm_sec;
		double secAngle = seconds * 6 + fmod(mAngle, 360) / 60;

		int minutes = (float)timeinfo->tm_min;
		double minAngle = minutes * 6 + fmod(secAngle, 360) / 60;

		int hour = (float)timeinfo->tm_hour;
		double hrAngle = ((hour % 12) * 30) + fmod(minAngle, 360) / 60;
		
		glTranslatef(0, 0, -6);
		glRotatef(angle2, 1.0, 0.0, 0.0);
		glRotatef(angle, 0.0, 1.0, 0.0);

		glScalef(zoom,zoom,zoom);

		switch (current_object) {
		case 0:
			if (pause) {
				drawSphereEmerald(7);
			}
			else {
				double theta2 = (M_PI / 180)*(secAngle * bpm);
				drawSphereEmerald(2* abs(sin(theta2)) + 7);
			}
			break;
		case 1:
			// draw your second primitive object here
			zoom = 0.3;
			if (pause) {
				drawCoolShit(2, 50, ambient_2, diffuse_2, specular_2, shininess_2);
			}
			else {
				double theta2 = (M_PI / 180)*(secAngle * bpm);
				m_Smooth = false;
				drawCoolShit(2 * abs(sin(theta2)) + 2, 5, ambient_1, diffuse_1, specular_1, shininess_1);
				starPlot(1);
			}
			break;
		case 2:
			// draw your first composite object here

			loadCoolStructure(secAngle);
			break;
		case 3:
			// draw your second composite object here
			loadPlanet(secAngle, mAngle, minAngle);
			break;
		default:
			break;
		};
	glPopMatrix();
	glutSwapBuffers ();
}




void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
	case 'p':
	case 'P':
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		break;			
	case 'w':
	case 'W':
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		break;			
	case 'v':
	case 'V':
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
		break;			
	case 's':
	case 'S':
		m_Smooth = !m_Smooth;
		break;
	case 'h':
	case 'H':
		m_Highlight = !m_Highlight;
		break;

	case 'o':
	case 'O':
		pause = !pause;
		break;

	case 'Z':
	case 'z':
		bpm -= 2;
		glutPostRedisplay();
		break;
	case 'C':
	case 'c':
		bpm += 2;
		glutPostRedisplay();
		break;
	case 'x':
	case 'X':
		bpm = 72;
		glutPostRedisplay();
		break;

	case 'r': {
		angle = 0;   /* in degrees */
		angle2 = 0;   /* in degrees */
		zoom = -0.2;
		glutPostRedisplay();
		break;
	}

	case '1':
	case '2':
	case '3':
	case '4':
		current_object = key - '1';
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
  if (state == GLUT_DOWN) {
	mouseButton = button;
    moving = 1;
    startx = x;
    starty = y;
  }
  if (state == GLUT_UP) {
	mouseButton = button;
    moving = 0;
  }
}

void motion(int x, int y)
{
  if (moving) {
	if(mouseButton==GLUT_LEFT_BUTTON)
	{
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
	}
	else zoom += ((y-starty)*0.001);
    startx = x;
    starty = y;
	glutPostRedisplay();
  }
  
}

void idle()
{

	glutPostRedisplay();	//after updating, draw the screen again
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 3"<< endl<< endl;

	cout << "1-4: Draw different objects"<<endl;
	cout << "S: Toggle Smooth Shading"<<endl;
	cout << "H: Toggle Highlight"<<endl;
	cout << "W: Draw Wireframe"<<endl;
	cout << "P: Draw Polygon"<<endl;
	cout << "V: Draw Vertices"<<endl;
	cout << "O: Animate objects 1 and 2" << endl;
	cout << "ESC: Quit" <<endl<< endl;

	cout << "Left mouse click and drag: rotate the object"<<endl;
	cout << "Right mouse click and drag: zooming"<<endl;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	for (int i = 0; i < starArrLength; i++) {
		starArr[i] = rand() % 2000-1000;
	}
	glutCreateWindow ("CS3241 Assignment 3");
	glClearColor (0.0,0.0,0.0, 0.0);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	setupLighting();
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); 
	glDepthMask(GL_TRUE);

    glMatrixMode(GL_PROJECTION);
    gluPerspective( /* field of view in degree */ 40.0,
  /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 80.0);
	glMatrixMode(GL_MODELVIEW);
	glutMainLoop();

	return 0;
}
