#include "Sphere.h"
#include <limits>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Sphere::intersect(const Ray &ray)
{
  HitRecord result;

  // set up intersection system as at^2+bt+c (see lecture 10)
  double at = ray.direction.squaredNorm();
  double bt = 2 * ray.direction.dot(ray.origin - this->c);
  double ct = (ray.origin - c).squaredNorm() - this->r * this->r;

  double discriminant = bt * bt - 4 * at * ct;

  if (discriminant < numeric_limits<double>::epsilon())
    return result; // no hit!

  double t0 = (-bt - sqrt(discriminant)) / (2 * at);
  double t1 = (-bt + sqrt(discriminant)) / (2 * at);

  if (t1 < numeric_limits<double>::epsilon())
    return result; // no hit!

  // hit!

  if (t0 > numeric_limits<double>::epsilon())
    result.t = t0; // use closer hit if it's in front
  else
    result.t = t1;

  result.position = ray.origin + result.t * ray.direction;
  result.normal = (result.position - this->c).normalized();
  result.shape = this;

  return result;
}