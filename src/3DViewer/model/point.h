#ifndef POINT_H
#define POINT_H

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

#include "action_data.h"
#include "factoryMethod.h"

class Point : public Product {
 public:
  Point();
  void MovePoint(const Move& move);
  void RotatePoint(const Point& r_center, const Rotate& rotate);
  void ScalePoint(const Point& s_center, const Scale& scale);
  bool SavePoint(std::ofstream& fout) const;

  double x_;
  double y_;
  double z_;

 private:
  static double ToRadians(const double angle);
  void RotateX(const Point& r_center, const double angle);
  void RotateY(const Point& r_center, const double angle);
  void RotateZ(const Point& r_center, const double angle);
};

class PointCreator : public Creator {
 public:
  virtual Product* Create() const override { return (Product*)(new Point); }
};

#endif  // POINT_H
