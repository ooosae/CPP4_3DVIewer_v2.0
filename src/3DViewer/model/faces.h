#ifndef FACES_H
#define FACES_H

#include "factoryMethod.h"
#include "points.h"

struct Face {
  std::vector<int> points;
};

class Faces : public Product {
 public:
  Faces() = default;
  ~Faces() = default;

  void AppendFace(Face face);
  void SaveAllFaces(std::ofstream& fout);

  std::vector<Face> array_faces_;

 private:
  void SaveFace(const Face& face, std::ofstream& fout);
};

class FacesCreator : public Creator {
 public:
  virtual Product* Create() const override { return (Product*)(new Faces); };
};

#endif  // FACES_H
