#include "faces.h"

void Faces::AppendFace(Face face) { array_faces_.push_back(face); }

void Faces::SaveAllFaces(std::ofstream& fout) {
  for (const auto& face : array_faces_) {
    SaveFace(face, fout);
  }
}

void Faces::SaveFace(const Face& face, std::ofstream& fout) {
  for (const auto& point : face.points) {
    fout << point << " ";
  }
  fout << "\n";
}