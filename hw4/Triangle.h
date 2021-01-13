#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

namespace Raytracer148
{
  class Triangle : public Shape
  {
  public:
    Triangle(Eigen::Vector3d &v0, Eigen::Vector3d &v1, Eigen::Vector3d &v2, Eigen::Vector3d &ka, Eigen::Vector3d &kd, Eigen::Vector3d &ks) : v0(v0), v1(v1), v2(v2)
    {
      this->ka = ka;
      this->kd = kd;
      this->ks = ks;
    }

    virtual HitRecord intersect(const Ray &ray);

  private:
    Eigen::Vector3d v0, v1, v2;
  };
} // namespace Raytracer148

#endif