/*******************************************************
 * Homework 1: Rasterization                           *
 * CS 148 (Summer 2016), Stanford University           *
 *-----------------------------------------------------*
 * Here you will implement the circle rasterization    *
 * method you derived in the written portion of the    *
 * homework.                                           *
 * To compile this in linux:                           *
 *        g++ hw1.cpp                                  *
 * Then, run the program as follows:                   *
 *        ./a.out 200                                  *
 * to generate a 200x200 image containing a circular   *
 * arc.  Note that the coordinate system we're using   *
 * places pixel centers at integer coordinates and     *
 * has the origin at the lower left.                   *
 * Your code will generate a .ppm file containing the  *
 * final image. These images can be viewed using       *
 * "display" in Linux or Irfanview in Mac/Windows.     *
 *******************************************************/

#include <GL/gl.h>
#include <GL/glut.h>

// other includes
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
#include <math.h>
using namespace std;

// We'll store image info as globals; not great programming practice
// but ok for this short program.
int size;
bool **image;
const int QUAD_1 = 0;
const int QUAD_2 = 1;
const int QUAD_3 = 2;
const int QUAD_4 = 3;

void static display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, size + 1, 0, size + 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glColor3f(1.0, 1.0, 1.0);
  glPointSize(1.0);
  for (int x = 0; x < size + 1; x++)
    for (int y = 0; y < size + 1; y++)
      if (image[y][x])
      {
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
      }
}

void renderPixel(int x, int y)
{
  assert(x >= 0 && y >= 0 && x <= size && y <= size);
  image[x][y] = 1;

  /* if (x >= 0 && y >= 0 && x <= size && y <= size)
    image[x][y] = 1; */

  // TODO:  light up the pixel's symmetric counterpart (INFO: in opengl)
}

void circlePoints(int x, int y, int dx, int dy, bool quadrants[])
{
  if (quadrants[QUAD_1])
  {
    renderPixel(x + dx, y + dy);
    renderPixel(y + dx, x + dy);
  }
  if (quadrants[QUAD_4])
  {
    renderPixel(y + dx, -x + dy);
    renderPixel(x + dx, -y + dy);
  }
  if (quadrants[QUAD_3])
  {
    renderPixel(-x + dx, -y + dy);
    renderPixel(-y + dx, -x + dy);
  }
  if (quadrants[QUAD_2])
  {
    renderPixel(-y + dx, x + dy);
    renderPixel(-x + dx, y + dy);
  }
}

void circleIntegerMidpointScanConversion(int radius, int dx, int dy, bool quadrants[])
{
  int x = 0;
  int y = radius;
  double d = 1 - radius;
  circlePoints(x, y, dx, dy, quadrants);

  while (y > x)
  {
    if (d < 0)
      d += 2 * x + 3;
    else
      d += 2 * (x - y--) + 5;

    x++;
    circlePoints(x, y, dx, dy, quadrants);
  }
}

void rasterizeArc(int radius)
{
  char *myargv[1];
  int myargc = 1;
  glutInit(&myargc, myargv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(size + 1, size + 1);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("HW1 - Rasterizer");
  glClearColor(0.0, 0.0, 0.0, 0.0);

  // TODO:  rasterize the arc using renderPixel to light up pixels
  int dx = size / 2;
  int dy = size / 2;
  bool quadCircle[4];
  quadCircle[QUAD_1] = true;
  quadCircle[QUAD_2] = false;
  quadCircle[QUAD_3] = false;
  quadCircle[QUAD_4] = true;
  circleIntegerMidpointScanConversion(150, dx, dy, quadCircle);

  quadCircle[QUAD_1] = true;
  quadCircle[QUAD_2] = true;
  quadCircle[QUAD_3] = false;
  quadCircle[QUAD_4] = false;
  circleIntegerMidpointScanConversion(100, dx, dy, quadCircle);
}

// You shouldn't need to change anything below this point.

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    cout << "Usage: " << argv[0] << " circleSize\n";
    return 0;
  }

#ifdef _WIN32
  sscanf_s(argv[1], "%d", &size);
#else
  sscanf(argv[1], "%d", &size);
#endif
  if (size <= 0)
  {
    cout << "Image must be of positive size.\n";
    return 0;
  }

  // reserve image as 2d array
  image = new bool *[size + 1];
  for (int i = 0; i <= size; i++)
    image[i] = new bool[size + 1];

  rasterizeArc(size);

  char filename[50];
#ifdef _WIN32
  sprintf_s(filename, 50, "circle%d.ppm", size);
#else
  sprintf(filename, "circle%d.ppm", size);
#endif

  ofstream outfile(filename);
  outfile << "P3\n# " << filename << "\n";
  outfile << size + 1 << ' ' << size + 1 << ' ' << 1 << endl;

  for (int i = 0; i <= size; i++)
    for (int j = 0; j <= size; j++)
      outfile << image[size - i][j] << " 0 0\n";

  outfile.close();

  glutDisplayFunc(display);
  glutMainLoop();

  // delete image data
  for (int i = 0; i <= size; i++)
    delete[] image[i];
  delete[] image;

  return 0;
}