#ifndef POINTS_H
#define POINTS_H

#include "action_data.h"
#include "factoryMethod.h"
#include "point.h"

class Points : public Product {
 public:
  Points() = default;
  ~Points() = default;

  void MoveAllPoints(const Move& coeff);
  void RotateAllPoints(const Point& r_center, const Rotate& coeff);
  void ScaleAllPoints(const Point& s_center, const Scale& coeff);
  void SaveAllPoints(std::ofstream& fout);
  void AppendPoint(Point point);
  void FindMinMaxPoints(double& min_x, double& max_x, double& min_y,
                        double& max_y, double& min_z, double& max_z);

  std::vector<std::vector<int>> points_table_;
  std::vector<Point> array_points_;
};

class PointsCreator : public Creator {
 public:
  virtual Product* Create() const override { return (Product*)(new Points); }
};

#endif  // POINTS_H
