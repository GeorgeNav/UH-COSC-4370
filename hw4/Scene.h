#ifndef SCENE_H
#define SCENE_H

#include "Shape.h"
#include "Image.h"
#include <vector>
#include <limits>

namespace Raytracer148
{
  class Scene
  {
  public:
    Scene(Eigen::Vector3d &l0, Eigen::Vector3d backgroundColor) : l0(l0), backgroundColor(backgroundColor) {}

    virtual ~Scene()
    {
      for (unsigned int i = 0; i < shapes.size(); i++)
        delete shapes[i];
      shapes.resize(0);
    }

    void addShape(Shape *s) { shapes.push_back(s); }
    HitRecord closestHit(const Ray &ray);
    Eigen::Vector3d trace(const Ray &ray, int curDepth);
    void render(Image &image);

  private:
    std::vector<Shape *> shapes;
    Eigen::Vector3d l0;              // Light position
    Eigen::Vector3d backgroundColor; // black background color
  };
} // namespace Raytracer148

#endif
