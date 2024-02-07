#ifndef concave_hpp
#define concave_hpp

#include "shape.hpp"

class Concave : public Shape
{
public:
  Concave(const point_t ver1, const point_t ver2, const point_t ver3, const point_t ver4);

  virtual ~Concave();
  virtual double getArea() const;
  virtual rectangle_t getFrameRect() const;
  virtual void move(point_t newPos);
  virtual void move(double x, double y);
  virtual void scale(double k);
  bool isTriangle(point_t first, point_t second, point_t third);
  bool isInsideTriangle(const point_t& A, const point_t& B, const point_t& C, const point_t& P);
  point_t getVer1() const;
  point_t getVer2() const;
  point_t getVer3() const;
  point_t getVer4() const;
private:
  point_t ver1_;
  point_t ver2_;
  point_t ver3_;
  point_t ver4_;
};

#endif
