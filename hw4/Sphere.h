#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

namespace Raytracer148
{
  class Sphere : public Shape
  {
  public:
    Sphere(Eigen::Vector3d &center, double radius, Eigen::Vector3d &ka, Eigen::Vector3d &kd, Eigen::Vector3d &ks) : c(center), r(radius)
    {
      this->ka = ka;
      this->kd = kd;
      this->ks = ks;
    }

    virtual HitRecord intersect(const Ray &ray);

  private:
    Eigen::Vector3d c;
    double r;
  };
} // namespace Raytracer148

#endif