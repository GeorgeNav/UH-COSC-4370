#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <GL/glut.h>

using namespace std;
#define GL_PI 3.1415926535897932384626433832795

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {5.0, 2.0, 5.0, 1.0}; // TODO: Your code here! setup a proper camera position. It should be 4 dimentions homogeneous coordinate, first three elements represent position and 4th element should be 1.
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples.

float specular[] = {1.0, 1.0, 1.0, 1.0};
float shininess[] = {50.0};

void problem1()
{
	// TODO: Your code here!
	float radius = 2;
	float teapot_size = 0.5;
	float rotation_value_in_degrees = 40;
	float rotation_value_in_radians = rotation_value_in_degrees * GL_PI / 180;

	float x, y;
	int teapot_i = 0;

	glMatrixMode(GL_MODELVIEW);
	// glTranslatef(0.0, radius, -15.0);

	float teapot_rotation = 0;
	while (teapot_i != 9)
	{
		x = radius * cos(rotation_value_in_radians * teapot_i);
		y = radius * sin(rotation_value_in_radians * teapot_i);

		glPushMatrix();
		glTranslatef(x, y, 0.0);
		glRotatef(teapot_rotation, 0.0, 0.0, 1.0);
		glutSolidTeapot(teapot_size);
		glPopMatrix();

		teapot_i += 1;
		teapot_rotation += 40;
	}
}

void problem2()
{
	// TODO: Your code here!
	float cube_size = 0.5;
	int n_cubes = 15;

	float dx = (float)-(cube_size / 2 + n_cubes * cube_size);
	float dy = (float)cube_size / 2;
	glTranslatef(dx, dy, 0.0);

	float scale_factor;
	float cube_dy;
	for (int i = 0; i < n_cubes; i++)
	{
		glPushMatrix();
		scale_factor = pow(1.1, i);
		glTranslatef(cube_size * i, scale_factor * cube_size / 2, 0.0);
		glScalef(1.0, scale_factor, 1.0);
		glutSolidCube(cube_size);
		glPopMatrix();
	}
}

const int n_fingers = 5;
const int n_joints = 5;
void problem3()
{
	// TODO: Your code here! Your own creativity.
	float r = 255.0 / 255.0;
	float g = 182.0 / 255.0;
	float b = 193.0 / 255.0;
	int X = 0, Y = 1, Z = 2;
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3f(r, g, b);

	float hand[n_fingers][n_joints][3] = {
			{// pinky finger
			 {0, 0, 0},
			 {-0.3, 3, 0.0},
			 {-0.3, 4, 0.2},
			 {-0.3, 3.5, 0.4},
			 {-0.3, 2.7, 0.5}},
			{// ring finger
			 {0, 0, 0},
			 {0, 3, 0.0},
			 {0, 4, 0.2},
			 {0, 3.5, 0.4},
			 {0, 2.7, 0.5}},
			{// middle finger
			 {0, 0, 0},
			 {0.3, 3, 0.0},
			 {0.3, 4, 0.1},
			 {0.3, 4.5, 0.2},
			 {0.3, 5, 0.3}},
			{// pointer finger
			 {0, 0, 0},
			 {0.5, 3, 0.0},
			 {0.6, 4, 0.1},
			 {0.7, 4.5, 0.2},
			 {0.8, 5, 0.3}},
			{// thumb
			 {0, 0, 0},
			 {0.8, 2.5, 0.1},
			 {0.6, 3.0, 0.3},
			 {0.4, 2.8, 0.2},
			 {0.3, 2.7, 0.2}}};

	int joint = 0;
	for (int finger = 0; finger < n_fingers; finger++)
	{
		for (int joint = 0; joint + 1 < n_joints; joint++)
		{
			glVertex3f(hand[finger][joint][X], hand[finger][joint][Y], hand[finger][joint][Z]);
			glVertex3f(hand[finger][joint + 1][X], hand[finger][joint + 1][Y], hand[finger][joint + 1][Z]);
		}
	}
	glEnd();
}

void display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	Create axis	
	*/
	glDisable(GL_LIGHTING); // NOTE: Disables lighting when determining pixel color for the next primitive fragments
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);	// NOTE: subsequent pairs of verticies create straight single segment lines
	glColor3f(1, 0, 0); // NOTE: red
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0); // x axis
	glColor3f(0, 1, 0);	 // NOTE: green
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0); // y axis
	glColor3f(0, 0, 1);	 // NOTE: blue
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1); // z axis
	glEnd();						 // NOTE: Ends the grouping of primitives for current (GL_LINES) from the last glBegin call

	glEnable(GL_LIGHTING);													 // NOTE: Enables lighting when determining pixel color for the next primitive fragments
	glShadeModel(GL_SMOOTH);												 // NOTE: Use smooth shading out of the options of smooth (GL_SMOOTH) and flat (GL_FLAT)
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);	 // NOTE: set specular (GL_SPECULAR) parameter to a uniform vector (4d) for lighting
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess); // NOTE: set shininess (GL_SHININESS) parameter to a uniform vector (4d) for lighting

	/*
	Projection matrix operations
	*/
	glMatrixMode(GL_PROJECTION); // NOTE: subsequent matrix operations are applied to the projection (GL_PROJECTION) matrix stack
	glLoadIdentity();						 // NOTE: the current matrix mode (GL_PROJECTION) gets reset to an identity matrix

	// TODO: Your code here! Use glViewport() and gluPerspective() to setup projection matrix.
	glViewport(0, 0, windowWidth, windowHeight); // NOTE: lower_left_x, lower_left_y, width, height
	gluPerspective(60, (double)windowWidth / (double)windowHeight, 2, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// TODO: Your code here! Use gluLookAt() to setup model-view matrix.
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);
	glLineWidth(2.0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos); // NOTE: set position (GL_POSITION) parameter
	glEnable(GL_LIGHT0);

	glRotatef(yRot, 0, 1, 0);

	if (curProblem == 1)
		problem1();
	else if (curProblem == 2)
		problem2();
	else if (curProblem == 3)
		problem3();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON)
		rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y)
{
	if (leftDown)
		yRot += (x - lastPos[0]) * .1;
	if (rightDown)
	{
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1, (y - lastPos[1]) * .1);
	}

	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(int key, int x, int y)
{
	// TODO: Your code here! use key to switch between different scene, and set q, Q and Escape key as quit.
	switch (key)
	{
	case GLUT_KEY_LEFT:
	{
		if (curProblem - 1 > 0)
		{
			curProblem -= 1;
			glutPostRedisplay();
		}
		break;
	}
	case GLUT_KEY_RIGHT:
	{
		if (curProblem + 1 <= 3)
		{
			curProblem += 1;
			glutPostRedisplay();
		}
		break;
	}
	default:
		return;
	}
}

void reshape(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);

	glutMainLoop();

	return 0;
}