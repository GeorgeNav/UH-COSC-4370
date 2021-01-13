#include "Disk.h"
#include <limits>

using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Disk::intersect(const Ray &ray)
{
  HitRecord result;

  double denominator = ray.direction.dot(this->n);
  if (denominator > 0.0 || denominator < 0.0)
  {
    double t = (this->p0 - ray.origin).dot(this->n) / denominator;
    if (t >= 0)
    {
      Eigen::Vector3d p = ray.origin + t * ray.direction;
      Eigen::Vector3d v = p - this->p0;
      double d2 = v.dot(v);
      if (d2 <= pow(this->radius, 2.0))
      {
        result.t = t;
        result.position = ray.origin + t * ray.direction;
        result.normal = (result.position - this->p0).normalized();
        result.shape = this;
      }
    }
  }

  return result;
}