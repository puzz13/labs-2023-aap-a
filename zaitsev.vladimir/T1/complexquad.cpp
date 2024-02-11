#include "complexquad.hpp"
#include <stdexcept>
#include <cstring>
#include <cmath>
#include <cstddef>
#include <limits>
#include <algorithm>
#include "base-types.hpp"
#include "Geom_functions.h"

void changeRectangleBounds(zaitsev::point_t& left_corner, zaitsev::point_t& right_corner, const zaitsev::point_t& new_pt)
{
  left_corner.x = std::min(left_corner.x, new_pt.x);
  left_corner.y = std::min(left_corner.y, new_pt.y);
  right_corner.x = std::max(right_corner.x, new_pt.x);
  right_corner.y = std::max(right_corner.y, new_pt.y);
}

zaitsev::Complexquad::Complexquad(const point_t* sections)
{
  if (!checkIntersection(sections))
  {
    throw std::invalid_argument("Lines are parallel");
  }
  std::memcpy(vertices_, sections, 4 * sizeof(point_t));
}

double zaitsev::Complexquad::getArea() const
{
  point_t center = getCenter();
  return getAreaOfTriangle(center, vertices_[0], vertices_[3]) + getAreaOfTriangle(center, vertices_[0], vertices_[3]);
}

zaitsev::rectangle_t zaitsev::Complexquad::getFrameRect() const
{
  point_t left_corner = vertices_[0];
  point_t right_corner = vertices_[0];

  for (size_t i = 1; i < 4; ++i)
  {
    changeRectangleBounds(left_corner, right_corner, vertices_[i]);
  }

  point_t size = right_corner - left_corner;
  point_t pos = (left_corner + right_corner) / 2;
  return { size.x, size.y, pos };
}

void zaitsev::Complexquad::move(const point_t& dest_pos)
{
  point_t pos = getCenter();
  move(dest_pos.x - pos.x, dest_pos.y - pos.y);
}

void zaitsev::Complexquad::move(double x_shift, double y_shift)
{
  point_t shift = { x_shift, y_shift };
  for (size_t i = 0; i < 4; ++i)
  {
    vertices_[i] += shift;
  }
}

zaitsev::point_t zaitsev::Complexquad::getCenter() const
{
  return findIntersection(vertices_);
}

void zaitsev::Complexquad::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Scale factor must be positive");
  }
  point_t center = getCenter();
  for (size_t i = 0; i < 4; ++i)
  {
    vertices_[i] = center + (vertices_[i] - center) * factor;
  }
  return;
}
