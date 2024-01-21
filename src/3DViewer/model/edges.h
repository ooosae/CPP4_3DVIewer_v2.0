#ifndef EDGES_H
#define EDGES_H

#include <fstream>
#include <vector>

#include "factoryMethod.h"

struct Edge {
  int first_point;
  int second_point;
};

class Edges : public Product {
 public:
  Edges() = default;
  ~Edges() = default;

  void AppendEdge(Edge edge);
  void SaveAllEdges(std::ofstream &fout);

  std::vector<Edge> array_edges_;
};

class EdgesCreator : public Creator {
 public:
  virtual Product *Create() const override { return (Product *)(new Edges); }
};

#endif  // EDGES_H
