#include "edges.h"

void Edges::AppendEdge(Edge edge) { array_edges_.push_back(edge); }

void Edges::SaveAllEdges(std::ofstream& fout) {
  for (const auto& edge : array_edges_) {
    fout << "l " << edge.first_point << " " << edge.second_point << "\n";
  }
}