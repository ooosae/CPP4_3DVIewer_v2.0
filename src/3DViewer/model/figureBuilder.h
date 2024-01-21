#pragma once

#include "figure.h"

class FigureBuilder {
 public:
  virtual ~FigureBuilder() = default;
  virtual void buildCenter(const Point& center) = 0;
  virtual void buildPoints(const Points& points) = 0;
  virtual void buildEdges(const Edges& edges) = 0;
  virtual void buildFaces(const Faces& faces) = 0;
  virtual void buildPointsTable() = 0;
};
