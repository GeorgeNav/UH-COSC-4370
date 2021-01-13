#ifndef DISK_H
#define DISK_H

#include "Shape.h"

namespace Raytracer148
{
  class Disk : public Shape
  {
  public:
    Disk(Eigen::Vector3d &p0, Eigen::Vector3d &n, double radius, Eigen::Vector3d &ka, Eigen::Vector3d &kd, Eigen::Vector3d &ks) : p0(p0), n(n), radius(radius)
    {
      this->ka = ka;
      this->kd = kd;
      this->ks = ks;
    }

    virtual HitRecord intersect(const Ray &ray);

  private:
    Eigen::Vector3d p0, n;
    double radius;
  };
} // namespace Raytracer148

#endif