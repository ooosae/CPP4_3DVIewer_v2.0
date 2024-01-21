#ifndef ACTION_DATA_H
#define ACTION_DATA_H

struct Move {
  double dx;
  double dy;
  double dz;
};

struct Rotate {
  double angle_x;
  double angle_y;
  double angle_z;
};

struct Scale {
  double kx;
  double ky;
  double kz;
};

#endif  // ACTION_DATA_H