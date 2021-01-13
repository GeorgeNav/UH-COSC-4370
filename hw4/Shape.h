#ifndef SHAPE_H
#define SHAPE_H

#include <eigen3/Eigen/Dense>

namespace Raytracer148
{
  struct Ray
  {
    Ray() {}
    Ray(Eigen::Vector3d &origin, const Eigen::Vector3d &direction) : origin(origin), direction(direction) {}
    Eigen::Vector3d origin, direction;
  };

  class Shape;

  struct HitRecord
  {
    Eigen::Vector3d position, normal;
    double t = -1;
    Shape *shape = nullptr;
  };

  class Shape
  {
  public:
    Eigen::Vector3d ka, kd, ks; // for each: shadingCoefficient * lightColor

    virtual ~Shape() {}
    virtual HitRecord intersect(const Ray &ray) = 0;
  };

} // namespace Raytracer148

#endif
