#include "points.h"

void Points::MoveAllPoints(const Move& coeff) {
  for (auto& point : array_points_) {
    point.MovePoint(coeff);
  }
}

void Points::RotateAllPoints(const Point& r_center, const Rotate& coeff) {
  for (auto& point : array_points_) {
    point.RotatePoint(r_center, coeff);
  }
}

void Points::ScaleAllPoints(const Point& s_center, const Scale& coeff) {
  for (auto& point : array_points_) {
    point.ScalePoint(s_center, coeff);
  }
}

void Points::SaveAllPoints(std::ofstream& fout) {
  for (const auto& point : array_points_) {
    fout << point.x_ << " " << point.y_ << " " << point.z_ << "\n";
  }
}

void Points::AppendPoint(Point point) { array_points_.push_back(point); }

void Points::FindMinMaxPoints(double& min_x, double& max_x, double& min_y,
                              double& max_y, double& min_z, double& max_z) {
  if (array_points_.empty()) return;

  min_x = max_x = array_points_[0].x_;
  min_y = max_y = array_points_[0].y_;
  min_z = max_z = array_points_[0].z_;

  for (const auto& point : array_points_) {
    min_x = std::min(min_x, point.x_);
    max_x = std::max(max_x, point.x_);

    min_y = std::min(min_y, point.y_);
    max_y = std::max(max_y, point.y_);

    min_z = std::min(min_z, point.z_);
    max_z = std::max(max_z, point.z_);
  }
}
