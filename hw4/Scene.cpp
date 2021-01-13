#include "Scene.h"
#include <cmath>

using namespace Raytracer148;
using namespace std;
using namespace Eigen;

const unsigned int MAX_DEPTH = 5;

HitRecord Scene::closestHit(const Ray &ray)
{
  HitRecord result;
  result.t = -1;
  bool foundSomething = false;

  for (unsigned int i = 0; i < shapes.size(); i++)
  {
    HitRecord r = shapes[i]->intersect(ray);
    if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t))
    {
      result = r;
      foundSomething = true;
    }
  }

  return result;
}

// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray &ray, int currentDepth)
{
  // For now we'll have diffuse shading with no shadows, so it's easy!
  HitRecord hitRay = closestHit(ray);
  Vector3d result = this->backgroundColor;

  if (hitRay.t < numeric_limits<double>::epsilon())
    return result;

  // Ray Equation: Lecture 17 - ray tracing (basic) page 19
  hitRay.position = ray.origin + hitRay.t * ray.direction // O + t * D
                    - ray.direction * 0.001;              // to prevent surface conflict
  Vector3d l = (this->l0 - hitRay.position).normalized(), // light direction
      n = hitRay.normal.normalized(),                     // normal direction
      h = (-ray.direction.normalized() + l).normalized(); // reflection direction

  Vector3d La = hitRay.shape->ka;                               // Ambient shader
  Vector3d Ld = hitRay.shape->kd * max(0.0, n.dot(l));          // Diffuse shader
  Vector3d Ls = hitRay.shape->ks * pow(max(0.0, n.dot(h)), 32); // Specular shader

  // Shadow
  Ray shadowRay(hitRay.position, l.normalized()); // go past the hitRay position in light's direction
  HitRecord shadowHit = closestHit(shadowRay);    // find the closest object to cast a shadow on
  result = shadowHit.t < 0
               ? La + Ls + Ld // normal phong shading if there's no shadow ray hit
               : La;          // ambient shading only if there's a hit (cast shadow)

  // Reflection: https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
  Vector3d dRef = ray.direction.normalized(),
           nRef = hitRay.normal.normalized();
  Vector3d reflectionRay = dRef - 2 * dRef.dot(nRef) * nRef; // r = d - 2 * d * n * n
  Ray reflectingRay(hitRay.position, reflectionRay);

  if (currentDepth > MAX_DEPTH) // do not trace reflecting ray (if any) once depth is met
    return result;

  double strength = 0.3;                                             // strength of reflection
  return result + strength * trace(reflectingRay, currentDepth + 1); // trace reflect ray
}

void Scene::render(Image &image)
{
  // We make the assumption that the camera is located at (0,0,0)
  // and that the image plane happens in the square from (-1,-1,1)
  // to (1,1,1).

  assert(image.getWidth() == image.getHeight());

  int size = image.getWidth();
  double pixelSize = 2. / size;
  for (int x = 0; x < size; x++)
    for (int y = 0; y < size; y++)
    {
      Ray curRay;
      curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;

      curRay.direction[0] = (x + 0.5) * pixelSize - 1;
      curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
      curRay.direction[2] = 1;

      Vector3d color = trace(curRay, 1.0);
      image.setColor(x, y, color[0], color[1], color[2]);
    }
}
