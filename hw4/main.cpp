#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "Disk.h"
#include "Triangle.h"

using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main()
{
  Image im(500, 500);

  Vector3d lightPos(3, 3, 0);
  Vector3d backgroundColor(0, 0, 0);
  Scene scene(lightPos, backgroundColor);

  // SPHERES
  Vector3d kaSphere(0.1, 0.2, 0.1), kdSphere(0.1, 0.2, 0.1), ksSphere(1.0, 1.0, 1.0);
  Vector3d centerBigSphere(0, 0, 4), centerSmallA(-0.5, 1, 2.5), centerSmallB(0.5, 1.25, 2.75);
  scene.addShape(new Sphere(centerBigSphere, 2, kaSphere, kdSphere, ksSphere));
  scene.addShape(new Sphere(centerSmallA, .5, kaSphere, kdSphere, ksSphere));
  scene.addShape(new Sphere(centerSmallB, .5, kaSphere, kdSphere, ksSphere));

  // TRIANGLES
  Vector3d kaTri(0.8, 0.1, 0.1), kdTri(0.8, 0.1, 0.1), ksTri(1.0, 1.0, 1.0);
  Vector3d tri1Corner1(0.4, 1.8, 2.0), tri1Corner2(3.0, 1.0, 4.0), tri1Corner3(2.0, -0.5, 2.5);
  scene.addShape(new Triangle(tri1Corner1, tri1Corner2, tri1Corner3, kaTri, kdTri, ksTri));

  // DISKS
  Vector3d kaDisk(0.1, 0.1, 0.8), kdDisk(0.1, 0.1, 0.8), ksDisk(1.0, 1.0, 1.0);
  double disksDepth = 1.5;
  double deltaX = -0.5, deltaY = -0.5;
  Vector3d disksNormal(0, 0.2, 0.5);
  Vector3d diskTopCenter(0 + deltaX, 0.5 + deltaY, disksDepth),
      diskBottomCenter(0 + deltaX, -0.5 + deltaY, disksDepth),
      diskLeftCenter(-0.5 + deltaX, 0 + deltaY, disksDepth),
      diskRightCenter(0.5 + deltaX, 0 + deltaY, disksDepth);
  scene.addShape(new Disk(diskTopCenter, disksNormal, 0.25, kaDisk, kdDisk, ksDisk));
  scene.addShape(new Disk(diskBottomCenter, disksNormal, 0.25, kaDisk, kdDisk, ksDisk));
  scene.addShape(new Disk(diskLeftCenter, disksNormal, 0.25, kaDisk, kdDisk, ksDisk));
  scene.addShape(new Disk(diskRightCenter, disksNormal, 0.25, kaDisk, kdDisk, ksDisk));

  scene.render(im);

  im.writePNG("test.png");

  return 0;
}