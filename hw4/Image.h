#ifndef IMAGE_H
#define IMAGE_H

#include <png.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>

namespace Raytracer148
{

  typedef struct
  {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
  } pixel_t;

  class Image
  {
  public:
    Image(size_t w, size_t h) : width(w), height(h)
    {
      pixels = (pixel_t *)calloc(sizeof(pixel_t), width * height);
    }

    virtual ~Image()
    {
      free(pixels);
    }

    int writePNG(const char *path);

    void setColor(int x, int y, double r, double g, double b)
    {
      assert(x >= 0 && x < (int)width && y >= 0 && y < (int)height);

      // Clamp to [0,1]
      r = std::min(1., std::max(r, 0.));
      g = std::min(1., std::max(g, 0.));
      b = std::min(1., std::max(b, 0.));

      pixel_t *p = pixelAt(x, y);
      p->red = (uint8_t)(r * 255);
      p->green = (uint8_t)(g * 255);
      p->blue = (uint8_t)(b * 255);
    }

    int getWidth() { return width; }
    int getHeight() { return height; }

  private:
    size_t width, height;
    pixel_t *pixels;

    pixel_t *pixelAt(int x, int y)
    {
      return pixels + width * y + x;
    }
  };

} // namespace Raytracer148

#endif
