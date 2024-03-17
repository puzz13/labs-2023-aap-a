#ifndef SHAPE_H
#define SHAPE_H

#include "base_types.h"

namespace kovtun
{
  class Shape
  {
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t point) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double k) = 0;
  };
}

#endif
