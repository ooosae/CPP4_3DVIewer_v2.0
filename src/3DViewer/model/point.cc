#include "point.h"

double Point::ToRadians(const double angle) { return angle * (M_PI / 180); }

void Point::RotateX(const Point& r_center, const double angle) {
  double r_cos = cos(ToRadians(angle));
  double r_sin = sin(ToRadians(angle));
  double y = y_;

  y_ = (y_ - r_center.y_) * r_cos + (z_ - r_center.z_) * r_sin + r_center.y_;
  z_ = -(y - r_center.y_) * r_sin + (z_ - r_center.z_) * r_cos + r_center.z_;
}

void Point::RotateY(const Point& r_center, const double angle) {
  double r_cos = cos(ToRadians(angle));
  double r_sin = sin(ToRadians(angle));
  double x = x_;

  x_ = (x_ - r_center.x_) * r_cos + (z_ - r_center.z_) * r_sin + r_center.x_;
  z_ = -(x - r_center.x_) * r_sin + (z_ - r_center.z_) * r_cos + r_center.z_;
}

void Point::RotateZ(const Point& r_center, const double angle) {
  double r_cos = cos(ToRadians(angle));
  double r_sin = sin(ToRadians(angle));
  double x = x_;

  x_ = (x_ - r_center.x_) * r_cos + (y_ - r_center.y_) * r_sin + r_center.x_;
  y_ = -(x - r_center.x_) * r_sin + (y_ - r_center.y_) * r_cos + r_center.y_;
}

Point::Point() : x_(0.0), y_(0.0), z_(0.0) {}

void Point::MovePoint(const Move& move) {
  x_ += move.dx;
  y_ += move.dy;
  z_ += move.dz;
}

void Point::RotatePoint(const Point& r_center, const Rotate& rotate) {
  RotateX(r_center, rotate.angle_x);
  RotateY(r_center, rotate.angle_y);
  RotateZ(r_center, rotate.angle_z);
}

void Point::ScalePoint(const Point& s_center, const Scale& scale) {
  x_ = (x_ - s_center.x_) * scale.kx + s_center.x_;
  y_ = (y_ - s_center.y_) * scale.ky + s_center.y_;
  z_ = (z_ - s_center.z_) * scale.kz + s_center.z_;
}

bool Point::SavePoint(std::ofstream& fout) const {
  if (!fout) return false;
  fout << "v " << x_ << " " << -y_ << " " << z_ << "\n";
  return true;
}
