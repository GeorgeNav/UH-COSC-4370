#include "Triangle.h"
#include <limits>

using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Triangle::intersect(const Ray &ray)
{
  HitRecord result;

  Vector3d triNormal = ((this->v1 - this->v0).cross(this->v2 - this->v0)).normalized(); // triangle normal direction

  if (fabs(triNormal.dot(ray.direction)) < std::numeric_limits<double>::epsilon())
    return result; // no hit: ray is parallel with triangle plane

  double t = -((ray.origin - this->v1).dot(triNormal)) / (ray.direction.dot(triNormal));
  Vector3d p = ray.origin + t * ray.direction; // point position: O + t * D

  double auxPoint1 = ((this->v1 - this->v0).cross(p - this->v0)).dot(triNormal);
  if (auxPoint1 <= 0)
    return result; // no hit: outside triangle boundaries

  double auxPoint2 = ((this->v2 - this->v1).cross(p - this->v1)).dot(triNormal);
  if (auxPoint2 <= 0)
    return result; // no hit: outside triangle boundaries

  double auxPoint3 = ((this->v0 - this->v2).cross(p - this->v2)).dot(triNormal);
  if (auxPoint3 <= 0)
    return result; // no hit: outside triangle boundaries

  result.t = t;
  result.position = p;
  result.normal = triNormal;
  result.shape = this;

  return result;
}