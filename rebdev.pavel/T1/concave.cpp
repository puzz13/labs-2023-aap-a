#include "concave.hpp"
#include <cstddef>
#include <iostream>

rebdev::Concave::Concave(const point_t * vertexs):
  vertexs_(nullptr)
{
  bool isConcave = 0;
  for (size_t i = 0; ((i < 4) && (!isConcave)); ++i)
  {
    if (isTriangle(vertexs[i], vertexs[(i + 1) % 4], vertexs[(i + 2) % 4]))
    {
      double arr[3] = {0.0, 0.0, 0.0};
      for (size_t j = 0; j < 3; ++j)
      {
        arr[j] = (vertexs[(i + j) % 4].x - vertexs[(i + 3) % 4].x)
          * (vertexs[(i + (j + 1) % 3) % 4].y - vertexs[(i + j) % 4].y);
        arr[j] -= (vertexs[(i + (j + 1) % 3) % 4].x - vertexs[(i + j) % 4].x)
          * (vertexs[(i + j) % 4].y - vertexs[(i + 3) % 4].y);
      }

      bool identicalSigns = ((arr[0] > 0) && (arr[1] > 0) && (arr[2] > 0));
      identicalSigns = (identicalSigns || ((arr[0] < 0) && (arr[1] < 0) && (arr[2] < 0)));

      if (identicalSigns)
      {
        try
        {
          vertexs_ = new point_t[4];
        }
        catch (const std::exception & e)
        {
          delete[] vertexs_;
          throw;
        }

        for (int i = 0; i < 4; ++i)
        {
          vertexs_[i] = vertexs[i];
        }
        isConcave = 1;
      }
    }
  }
  if (!isConcave)
  {
    throw std::logic_error("concave error");
  }

  for (size_t i = 0; i < 4; ++i)
  {
    vertexs_[i] = vertexs[i];
  }
};

rebdev::Concave::~Concave()
{
  delete[] vertexs_;
};

double rebdev::Concave::getArea() const
{
  double sum  = 0;
  for (size_t i = 0; i < 4; ++i)
  {
    sum += (vertexs_[i].x * vertexs_[(i + 1) % 4].y) - (vertexs_[(i + 1) % 4].x * vertexs_[i].y);
  }
  sum /= 2;

  return ((sum < 0) ? -sum : sum);
};

rebdev::rectangle_t rebdev::Concave::getFrameRect() const
{
  double xMin = vertexs_[0].x, xMax = vertexs_[0].y;
  double yMin = xMin, yMax = xMax;
  for (int i = 0; i < 4; ++i)
  {
    xMin = ((xMin >= vertexs_[i].x) ? vertexs_[i].x : xMin);
    yMin = ((yMin >= vertexs_[i].y) ? vertexs_[i].y : yMin);
    xMax = ((xMax <= vertexs_[i].x) ? vertexs_[i].x : xMax);
    yMax = ((yMax <= vertexs_[i].y) ? vertexs_[i].y : yMax);
  }
  return rectangle_t{(xMax - xMin), (yMax - yMin), point_t{xMin + (xMax - xMin)/2, yMin + (yMax - yMin)/2}};
};

void rebdev::Concave::move(const point_t point)
{
  double yChange = vertexs_[2].y - point.y;
  double xChange = vertexs_[2].x - point.x;
  for (int i = 0; i < 4; ++i)
  {
    vertexs_[i].x += xChange;
    vertexs_[i].y += yChange;
  }
};

void rebdev::Concave::move(const double x, const double y)
{
  for (int i = 0; i < 4; ++i)
  {
    vertexs_[i].x += x;
    vertexs_[i].y += y;
  }
};

void rebdev::Concave::scale(const double k)
{
  vertexs_[0] = scalePoint(vertexs_[0], vertexs_[2], k);
  vertexs_[1] = scalePoint(vertexs_[1], vertexs_[2], k);
  vertexs_[3] = scalePoint(vertexs_[3], vertexs_[2], k);
};

rebdev::point_t rebdev::Concave::scalePoint(const point_t & pointToScale, const point_t & centerPoint, const double k)
{
  point_t scaledPoint = {(pointToScale.x - centerPoint.x) * k + centerPoint.x,
    (pointToScale.y - centerPoint.y) * k + centerPoint.y};
  return scaledPoint;
};

bool rebdev::Concave::isTriangle(const point_t f, const point_t s, const point_t t)
{
    return (((t.x - f.x) / (s.x - f.x)) != ((t.y - f.y) / (s.y - f.y)));
};
