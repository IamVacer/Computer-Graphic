#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

/* Include header files depending on platform */
#ifdef _WIN32
	#include "glut.h"
	#include <Windows.h>
	#define M_PI 3.141592654
	#include <math.h>
	#include <time.h>
	#include <sys/timeb.h>	
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/GLUT.h>
#endif

using namespace std;
GLuint texSet[45];
GLuint fireSet[30];
double hrAngle, minAngle, mAngle, mRad, hrRad, minRad;
double secAngle, secRad;
int starArrLength = 6000;
double starArr[6000]; //coordinates of stars in the default window
int planeLength = 45;
double planeArr[45];




// You may add more functions here if you like
// ========================================================================
double toRad(double degree) {
	return degree * (M_PI / 180);
}

void drawCoolShit(double r, int n, GLuint texture)
{
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
			double p = 5 / 4;

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture);

			glBegin(GL_POLYGON);

			// the normal of each vertex is actaully its own coordinates normalized for a sphere

			glNormal3d(cos(theta1b)*(q - (p + sin(side * theta1a))*sin(theta1a - side * theta1b)),
				(q - (p + sin(side * theta1a))*sin(theta1a - side * theta1b))*sin(theta1b),
				-cos(theta1a - side * theta1b)*(p + sin(side * theta1a)));

			glTexCoord2d(0, 0);
			glVertex3d(cos(theta1b)*(q - (p + sin(side * theta1a))*sin(theta1a - side * theta1b)),
				(q - (p + sin(side * theta1a))*sin(theta1a - side * theta1b))*sin(theta1b),
				-cos(theta1a - side * theta1b)*(p + sin(side * theta1a)));

			glNormal3d(cos(theta2b)*(q - (p + sin(side * theta1a))*sin(theta1a - side * theta2b)),
				(q - (p + sin(side * theta1a))*sin(theta1a - side * theta2b))*sin(theta2b),
				-cos(theta1a - side * theta2b)*(p + sin(side * theta1a)));

			glTexCoord2d(0, 1);
			glVertex3d(cos(theta2b)*(q - (p + sin(side * theta1a))*sin(theta1a - side * theta2b)),
				(q - (p + sin(side * theta1a))*sin(theta1a - side * theta2b))*sin(theta2b),
				-cos(theta1a - side * theta2b)*(p + sin(side * theta1a)));

			glNormal3d(cos(theta2b)*(q - (p + sin(side * theta2a))*sin(theta2a - side * theta2b)),
				(q - (p + sin(side * theta2a))*sin(theta2a - side * theta2b))*sin(theta2b),
				-cos(theta2a - side * theta2b)*(p + sin(side * theta2a)));

			glTexCoord2d(1, 1);
			glVertex3d(cos(theta2b)*(q - (p + sin(side * theta2a))*sin(theta2a - side * theta2b)),
				(q - (p + sin(side * theta2a))*sin(theta2a - side * theta2b))*sin(theta2b),
				-cos(theta2a - side * theta2b)*(p + sin(side * theta2a)));

			glNormal3d(cos(theta1b)*(q - (p + sin(side * theta2a))*sin(theta2a - side * theta1b)),
				(q - (p + sin(side * theta2a))*sin(theta2a - side * theta1b))*sin(theta1b),
				-cos(theta2a - side * theta1b)*(p + sin(side * theta2a)));

			glTexCoord2d(1, 1);
			glVertex3d(cos(theta1b)*(q - (p + sin(side * theta2a))*sin(theta2a - side * theta1b)),
				(q - (p + sin(side * theta2a))*sin(theta2a - side * theta1b))*sin(theta1b),
				-cos(theta2a - side * theta1b)*(p + sin(side * theta2a)));

			glEnd();
			glDisable(GL_TEXTURE_2D);
			
		}
}

void drawDrill() {
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glRotated(mAngle, 0, 0, 1);
	glTranslatef(0, 0, 0.1* sin(mAngle*30));
	glScaled(0.5, 0.5, 0.5);
	for (double i = 1; i < 7; i++) {
		drawCoolShit(log(i/1.3), 5, texSet[40]);
		glRotated(-15, 0, 0, 1);
		glTranslatef(0, 0, -1);
	}
	glScalef(1, 1, 2);
	//drawCoolShit(2 * sin(secAngle) + 2, 10, texSet[1]);
	glPopMatrix();
}

void starPlot(){
	glPushMatrix();
	glRotated(-secAngle, 0, 1, 0);
	glPushMatrix();
	double x, y;
	glBegin(GL_POINTS);

	for (int i = 0; i < starArrLength; i += 6) {
		glColor4f(1, 1, i, 1); 
		glVertex3d(starArr[i] / 50, starArr[i + 1] / 50 + 17, starArr[i + 2] / 50);
	}
	glEnd();
	glPopMatrix();
	glPopMatrix();
}
// ========================================================================
void drawPlane(int texture) {
	
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	glScaled(0.1, 0.1, 0.1);
	glScaled((1*sin(mRad))+1.5, 1, 1);
	glTranslated(0, -7, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSet[texture]);
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.4, 0.0, 0.2);
	glTexCoord2d(0, 0);
	/* left wing */
	glVertex3d(-7.0, 0.0, 2.0);
	glTexCoord2d(0, 1);
	glVertex3d(-1.0, 0.0, 3.0);
	glTexCoord2d(1, 1);
	glVertex3d(-1.0, 7.0, 3.0);
	/* left base */
	glTexCoord2d(0, 1);
	glColor3f(0.4, 0.5, 0.2);
	glTexCoord2d(0, 0);
	glVertex3d(0.0, 0.0, 0.0);
	glTexCoord2d(1, 1);
	glVertex3d(0.0, 8.0, 0.0);
	/* right base */
	glTexCoord2d(0, 0);
	glVertex3d(1.0, 0.0, 3.0);
	glTexCoord2d(0, 1);
	glVertex3d(1.0, 7.0, 3.0);
	/* final tip of right wing */
	glTexCoord2d(0, 0);
	glColor3f(0.4, 0.5, 0.2);
	glVertex3d(7.0, 0.0, 2.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void drawPlaneS() {
	glPushMatrix();
	glRotated(secAngle, 0, 1, 0);
	glPushMatrix();
	for (int i = 0; i < planeLength; i += 3) {
		glRotated(360/(planeLength/3), 0, 1, 0);
		glPushMatrix();
		glTranslated(planeArr[i], planeArr[i+1], 0);
		drawPlane(planeArr[i+2]);
		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();
}
void drawCone(){
	glPushMatrix();
	glTranslatef(0, 6, 0);
	glTranslatef(0, 0.2* sin(mAngle * 30),0);
	glPushMatrix();
	
	glColor3f(0.93, 0.34, 0.19);
	glRotated(90, -1, 0, 0);
	glutSolidCone(2, 4, 30, 10);
	glTranslated(0, 0, 1.1);
	glColor3f(1, 1, 1);
	glutSolidCone(1.45, 3, 30, 10);
	glTranslated(0, 0, 1.1);
	glColor3f(0.93, 0.34, 0.19);
	glutSolidCone(0.93, 1.9, 30, 10);
	glPopMatrix();
	glPopMatrix();
}
void drawFire() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	int fireMode = (floor(secAngle*10));
	glBindTexture(GL_TEXTURE_2D, fireSet[fireMode % 30]);
	for (int i = 0; i < 4; i++) {
		glBegin(GL_POLYGON);
		glTexCoord2d(0, 0); glVertex3f(-1.5, 4, 2.01);
		glTexCoord2d(1, 0); glVertex3f(-0.5, 4, 2.01);
		glTexCoord2d(1, 1); glVertex3f(-0.5, 5, 2.01);
		glTexCoord2d(0, 1); glVertex3f(-1.5, 5, 2.01);
		glEnd();

		glBegin(GL_POLYGON);
		glTexCoord2d(0, 0); glVertex3f(1.5, 4, 2.01);
		glTexCoord2d(1, 0); glVertex3f(0.5, 4, 2.01);
		glTexCoord2d(1, 1); glVertex3f(0.5, 5, 2.01);
		glTexCoord2d(0, 1); glVertex3f(1.5, 5, 2.01);
		glEnd();
		glRotated(90, 0, 1, 0);

	}
	

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawWin() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSet[29]);
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glBegin(GL_POLYGON);
		glTexCoord2d(0.13, 0.5); glVertex3f(0.5, 3, 2.01);
		glTexCoord2d(1, 0.5); glVertex3f(-0.5, 3, 2.01);
		glTexCoord2d(1, 1); glVertex3f(-0.5, 3.5, 2.01);
		glTexCoord2d(0.13, 1); glVertex3f(0.5, 3.5, 2.01);
		glEnd();
		glPopMatrix();
		glRotated(90, 0, 1, 0);

	}

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void drawCube() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSet[24]);

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3f(-2, 3, -2);
	glTexCoord2d(1, 0); glVertex3f(-2, 6, -2);
	glTexCoord2d(1, 1); glVertex3f(-2, 6, 2);
	glTexCoord2d(0, 1); glVertex3f(-2, 3, 2);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3f(-2, 3, -2);
	glTexCoord2d(1, 0); glVertex3f(-2, 6, -2);
	glTexCoord2d(1, 1); glVertex3f(2, 6, -2);
	glTexCoord2d(0, 1); glVertex3f(2, 3, -2);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3f(-2, 6, -2);
	glTexCoord2d(1, 0); glVertex3f(2, 6, -2);
	glTexCoord2d(1, 1); glVertex3f(2, 6, 2);
	glTexCoord2d(0, 1); glVertex3f(-2, 6, 2);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3f(2, 3, -2);
	glTexCoord2d(1, 0); glVertex3f(2, 6, -2);
	glTexCoord2d(1, 1); glVertex3f(2, 6, 2);
	glTexCoord2d(0, 1); glVertex3f(2, 3, 2);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3f(-2, 3, 2);
	glTexCoord2d(1, 0); glVertex3f(-2, 6, 2);
	glTexCoord2d(1, 1); glVertex3f(2, 6, 2);
	glTexCoord2d(0, 1); glVertex3f(2, 3, 2);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3f(-2, 3, -2);
	glTexCoord2d(1, 0); glVertex3f(2, 3, -2);
	glTexCoord2d(1, 1); glVertex3f(2, 3, 2);
	glTexCoord2d(0, 1); glVertex3f(-2, 3, 2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawRoof() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSet[16]);

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3f(-2, 6.01, -2);
	glTexCoord2d(1, 0); glVertex3f(2, 6.01, -2);
	glTexCoord2d(1, 1); glVertex3f(2, 6.01, 2);
	glTexCoord2d(0, 1); glVertex3f(-2, 6.01, 2);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3f(2.01, 5.5, -2);
	glTexCoord2d(1, 0); glVertex3f(2.01, 6, -2);
	glTexCoord2d(1, 1); glVertex3f(2.01, 6, 2);
	glTexCoord2d(0, 1); glVertex3f(2.01, 5.5, 2);
	glEnd();
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3f(-2.01, 5.5, -2);
	glTexCoord2d(1, 0); glVertex3f(-2.01, 6, -2);
	glTexCoord2d(1, 1); glVertex3f(-2.01, 6, 2);
	glTexCoord2d(0, 1); glVertex3f(-2.01, 5.5, 2);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3f(-2, 5.5, -2.01);
	glTexCoord2d(1, 0); glVertex3f(-2, 6, -2.01);
	glTexCoord2d(1, 1); glVertex3f(2, 6, -2.01);
	glTexCoord2d(0, 1); glVertex3f(2, 5.5, -2.01);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3f(-2, 5.5, 2.01);
	glTexCoord2d(1, 0); glVertex3f(-2, 6, 2.01);
	glTexCoord2d(1, 1); glVertex3f(2, 6, 2.01);
	glTexCoord2d(0, 1); glVertex3f(2, 5.5, 2.01);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void drawMyHouse(GLuint texSet[])
{
	//plot dimension
	//x: -5:5
	//y: >= 0
	//z: -5:5

	// Your main drawing code goes here
	// =========================================

	// floor plane (you may remove this)
	
	glPushMatrix();
	glRotated(45, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 0.03* sin(mAngle * 30), 0);
	drawCube();
	drawRoof();
	drawFire();
	drawWin();
	glPopMatrix();

	drawCone();
	drawPlaneS();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSet[9]);
	glBegin(GL_POLYGON);
	
	glTexCoord2d(0, 0); glVertex3f(-5, -0.02, -5);
	glTexCoord2d(1, 0); glVertex3f(5, -0.02, -5);
	glTexCoord2d(1, 1); glVertex3f(5, -0.02, 5);
	glTexCoord2d(0, 1); glVertex3f(-5, -0.02, 5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// =========================================
}

// ********** You do not need to edit any code beyond this point **********

// The following code supports loading textures from disk
// ========================================================================

GLuint loadMyTextures(char *filename)
{
	GLuint myTexture;
	FILE * file;
	unsigned char *tex, *tex2;

	// texture data
	int width = 256;
	int height = 256;

	// allocate buffer
	tex = (unsigned char *)malloc(width * height * 3);
	tex2 = (unsigned char *)malloc(width * height * 3);

	// open and read texture data
	file = fopen(filename, "rb");

	if (file == NULL)
		cout << "Error! Missing texture!\n";

	fread(tex, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i<width*height; i++)
	{
		tex2[i * 3] = tex[i * 3 + 2];
		tex2[i * 3 + 1] = tex[i * 3 + 1];
		tex2[i * 3 + 2] = tex[i * 3];
	}

	// allocate a texture name
	glGenTextures(1, &myTexture);
	glBindTexture(GL_TEXTURE_2D, myTexture);

	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	// when texture area is large, bilinear filter the first mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// texture should tile
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// build texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tex2);

	// free buffers
	free(tex);
	free(tex2);
	return myTexture;
}
// ========================================================================

// The following code is used to support rotation of the scene with your mouse
// ========================================================================
bool isDraggingLeft = false;
bool isDraggingRight = false;
int prevX = 0, prevY = 0;
int curX = 0, curY = 0;
float angle1 = M_PI, angle2 = -1;	// angles are in radians
float dist = 12.0;
float lookY = 5;
float aspectRatio = 1.0;

void LMBDragged(float dx, float dy) {
	angle1 -= ((float)dx) / 150.0;
	angle2 += ((float)dy) / 150.0;

	if (angle1 < 0)	angle1 += 2 * M_PI;
	else if (angle1 > 2 * M_PI) angle1 -= 2 * M_PI;
	if (angle2 < 0)	angle2 += 2 * M_PI;
	else if (angle2 > 2 * M_PI) angle2 -= 2 * M_PI;
}

void RMBDragged(float dx, float dy) {
	dist += ((float)dx) / 100.0;
	lookY += ((float)dy) / 50.0;
}

void computeCameraPosition() {
	float camX = dist * sin(angle1) * sin(angle2);
	float camY = dist * cos(angle2);
	float camZ = dist * cos(angle1) * sin(angle2);

	float upVectorY = 1.0;
	if (angle2 >= 0 && angle2 < M_PI) {
		upVectorY = -1.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, aspectRatio, 1, 75);
	gluLookAt(camX, camY+lookY, camZ, 0, lookY, 0, 0, upVectorY, 0);
	glMatrixMode(GL_MODELVIEW);
}

void resetCamera() {
	angle1 = M_PI;
	angle2 = -1;
	lookY = 3;
	dist = 12.0;
}
// ========================================================================


// The following code is the usual stuff you give OpenGL
// ========================================================================

void init(void)
{
	//glClearColor (0.73, 0.90, 0.96, 1.0);
	glShadeModel (GL_SMOOTH);
    glEnable(GL_NORMALIZE);

	texSet[0] = loadMyTextures("brick1.bmp");
	texSet[1] = loadMyTextures("brick2.bmp");
	texSet[2] = loadMyTextures("brick3.bmp");
	texSet[3] = loadMyTextures("brick4.bmp");
	texSet[4] = loadMyTextures("door1.bmp");
	texSet[5] = loadMyTextures("door2.bmp");
	texSet[6] = loadMyTextures("flower1.bmp");
	texSet[7] = loadMyTextures("flower2.bmp");
	texSet[8] = loadMyTextures("flower3.bmp");
	texSet[9] = loadMyTextures("grass1.bmp");

	texSet[10] = loadMyTextures("grass2.bmp");
	texSet[11] = loadMyTextures("leaves1.bmp");
	texSet[12] = loadMyTextures("leaves2.bmp");
	texSet[13] = loadMyTextures("roof1.bmp");
	texSet[14] = loadMyTextures("roof2.bmp");
	texSet[15] = loadMyTextures("roof3.bmp");
	texSet[16] = loadMyTextures("roof4.bmp");
	texSet[17] = loadMyTextures("roof5.bmp");
	texSet[18] = loadMyTextures("roof6.bmp");
	texSet[19] = loadMyTextures("stone1.bmp");

	texSet[20] = loadMyTextures("stone2.bmp");
	texSet[21] = loadMyTextures("tile1.bmp");
	texSet[22] = loadMyTextures("tile2.bmp");
	texSet[23] = loadMyTextures("tile3.bmp");
	texSet[24] = loadMyTextures("tile4.bmp");
	texSet[25] = loadMyTextures("tile5.bmp");
	texSet[26] = loadMyTextures("tile6.bmp");
	texSet[27] = loadMyTextures("window1.bmp");
	texSet[28] = loadMyTextures("window2.bmp");
	texSet[29] = loadMyTextures("window3.bmp");

	texSet[30] = loadMyTextures("window4.bmp");
	texSet[31] = loadMyTextures("window5.bmp");
	texSet[32] = loadMyTextures("window6.bmp");
	texSet[33] = loadMyTextures("wood1.bmp");
	texSet[34] = loadMyTextures("wood2.bmp");
	texSet[35] = loadMyTextures("wood3.bmp");
	texSet[36] = loadMyTextures("wood4.bmp");
	texSet[37] = loadMyTextures("wood5.bmp");
	texSet[38] = loadMyTextures("wood6.bmp");
	texSet[39] = loadMyTextures("wood7.bmp");

	texSet[40] = loadMyTextures("custom/custom1.bmp");
	texSet[41] = loadMyTextures("custom/custom2.bmp");
	texSet[42] = loadMyTextures("custom/custom3.bmp");
	texSet[43] = loadMyTextures("custom/custom4.bmp");
	texSet[44] = loadMyTextures("custom/custom5.bmp");

	fireSet[0] = loadMyTextures("custom/fire0.bmp");
	fireSet[1] = loadMyTextures("custom/fire1.bmp");
	fireSet[2] = loadMyTextures("custom/fire2.bmp");
	fireSet[3] = loadMyTextures("custom/fire3.bmp");
	fireSet[4] = loadMyTextures("custom/fire4.bmp");
	fireSet[5] = loadMyTextures("custom/fire5.bmp");
	fireSet[6] = loadMyTextures("custom/fire6.bmp");
	fireSet[7] = loadMyTextures("custom/fire7.bmp");
	fireSet[8] = loadMyTextures("custom/fire8.bmp");
	fireSet[9] = loadMyTextures("custom/fire9.bmp");
	fireSet[10] = loadMyTextures("custom/fire10.bmp");
	fireSet[11] = loadMyTextures("custom/fire11.bmp");
	fireSet[12] = loadMyTextures("custom/fire12.bmp");
	fireSet[13] = loadMyTextures("custom/fire13.bmp");
	fireSet[14] = loadMyTextures("custom/fire14.bmp");
	fireSet[15] = loadMyTextures("custom/fire15.bmp");
	fireSet[16] = loadMyTextures("custom/fire16.bmp");
	fireSet[17] = loadMyTextures("custom/fire17.bmp");
	fireSet[18] = loadMyTextures("custom/fire18.bmp");
	fireSet[19] = loadMyTextures("custom/fire19.bmp");
	fireSet[20] = loadMyTextures("custom/fire20.bmp");
	fireSet[21] = loadMyTextures("custom/fire21.bmp");
	fireSet[22] = loadMyTextures("custom/fire22.bmp");
	fireSet[23] = loadMyTextures("custom/fire23.bmp");
	fireSet[24] = loadMyTextures("custom/fire24.bmp");
	fireSet[25] = loadMyTextures("custom/fire25.bmp");
	fireSet[26] = loadMyTextures("custom/fire26.bmp");
	fireSet[27] = loadMyTextures("custom/fire27.bmp");
	fireSet[28] = loadMyTextures("custom/fire28.bmp");
	fireSet[29] = loadMyTextures("custom/fire29.bmp");
	
	cout << "Texture loading complete" << endl;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, 1.0, 1, 75);
	computeCameraPosition();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	aspectRatio = (float)w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, aspectRatio, 1, 75);
	computeCameraPosition();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(void)
{
	int startTime=glutGet(GLUT_ELAPSED_TIME);
	int counter = 1;
	SYSTEMTIME mtimer;
	GetSystemTime(&mtimer);
	time_t current_time = time(0);
	struct tm * timeinfo = localtime(&current_time);

	double millis = mtimer.wMilliseconds;
	mAngle = millis * 360 / 1000;
	mRad = toRad(mAngle);

	int seconds = (float)timeinfo->tm_sec;
	secAngle = seconds * 6 + fmod(mAngle, 360) / 60;
	secRad = toRad(secAngle);

	int minutes = (float)timeinfo->tm_min;
	minAngle = minutes * 6 + fmod(secAngle, 360) / 60;
	minRad = toRad(minAngle);

	
	glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawDrill();
	starPlot();
	drawMyHouse(texSet);
	
	int endTime=glutGet(GLUT_ELAPSED_TIME);
	// cout<<"Frame Rate: "<<(float)1000/(endTime-startTime)<<"\n";
	glFlush();
	glutSwapBuffers();

}

void mouse(int button, int state, int x, int y)
{

	if(!isDraggingLeft && button == GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		isDraggingLeft = true;
		isDraggingRight = false;
		prevX = x;
		prevY = y;
	}

	else if(button == GLUT_LEFT_BUTTON && state==GLUT_UP)
	{		
		isDraggingLeft = false;
		prevX = 0;
		prevY = 0;
	}

	if (!isDraggingRight && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		isDraggingLeft = false;
		isDraggingRight = true;
		prevX = x;
		prevY = y;
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		isDraggingRight = false;
		prevX = 0;
		prevY = 0;
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
		resetCamera();
		computeCameraPosition();
		glutPostRedisplay();
	}

}

void mouseMotion(int x, int y) {
	if (isDraggingLeft) {
		float dx = x - prevX;
		float dy = y - prevY;

		LMBDragged(dx, dy);
		computeCameraPosition();
		glutPostRedisplay();

		prevX = x;
		prevY = y;
	}

	if (isDraggingRight) {
		float dx = x - prevX;
		float dy = y - prevY;

		RMBDragged(dx, dy);
		computeCameraPosition();
		glutPostRedisplay();

		prevX = x;
		prevY = y;
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'w' || key == 'W') {
		dist -= 1.0;
		computeCameraPosition();
		glutPostRedisplay();
	}

	if (key == 's' || key == 'S') {
		dist += 1.0;
		computeCameraPosition();
		glutPostRedisplay();
	}
	
	if (key == 27) {
		exit(0);
	}
}

void idle()
{

	glutPostRedisplay();	//after updating, draw the screen again
}

int main(int argc, char **argv)
{
	cout << "CS3241 Lab 5\n\n";
	cout << "+++++CONTROLS+++++++\n\n";
	cout << "Left Click and Drag: Rotate camera\n";
	cout << "Right Click and Drag:\n";
	cout << "\tVertical: Change camera elevation\n";
	cout << "\tHorizontal: Zoom in and out\n";
	cout << "Middle Click: Reset camera\n";
	cout << "W: Zoom In\n";
	cout << "S: Zoom Out\n";
	cout <<"ESC: Quit\n";
	for (int i = 0; i < starArrLength; i++) {
		starArr[i] = rand() % 2000 - 1000;
	}
	for (int i = 0; i < planeLength; i += 3) {
		planeArr[i] = rand()%100/20+3;//radius
		planeArr[i + 1] = rand() % 100 / 20+3;// height
		planeArr[i + 2] = floor(rand() % 43);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);
	resetCamera();
	init ();
	glutDisplayFunc(display);
	//setupLighting();
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);	
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}

// ========================================================================

