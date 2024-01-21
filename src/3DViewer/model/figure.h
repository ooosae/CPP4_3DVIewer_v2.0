#ifndef FIGURE_H
#define FIGURE_H

#include "edges.h"
#include "faces.h"
#include "factoryMethod.h"
#include "figureBuilder.h"
#include "points.h"

class ConcreteFigureBuilder;

class FigureFacade {
 public:
  FigureFacade() = default;
  ~FigureFacade() = default;

  void DownloadFigure(const std::string& filename,
                      ConcreteFigureBuilder& builder);
  void MoveFigure(const Move& move);
  void ScaleFigure(const Scale& scale);
  void RotateFigure(const Rotate& rotate);
  void SaveFigure(const std::string& filename);

  Point center_;
  Points points_;
  Edges edges_;
  Faces faces_;

  void ReadFigure(std::ifstream& fin, FigureBuilder& builder);
  void ReadVertex(Point& point, const std::string& line);
  void ReadFace(Face& face, const std::string& line);
  void FaceToEdges(const Face& face, Edges& edges);
  bool ExistEdge(const Edge& edge);
};

class ConcreteFigureBuilder : public FigureBuilder {
 private:
  FigureFacade figure;

 public:
  void buildCenter(const Point& center) override { figure.center_ = center; }

  void buildPoints(const Points& points) override { figure.points_ = points; }

  void buildEdges(const Edges& edges) override { figure.edges_ = edges; }

  void buildFaces(const Faces& faces) override { figure.faces_ = faces; }

  void buildPointsTable() override {
    for (size_t i = 0; i < figure.edges_.array_edges_.size(); ++i) {
      if (static_cast<size_t>(figure.edges_.array_edges_[i].first_point) <
              figure.points_.points_table_.size() &&
          static_cast<size_t>(figure.edges_.array_edges_[i].second_point) <
              figure.points_
                  .points_table_[figure.edges_.array_edges_[i].first_point]
                  .size()) {
        figure.points_
            .points_table_[figure.edges_.array_edges_[i].first_point]
                          [figure.edges_.array_edges_[i].second_point] = 1;
        figure.points_
            .points_table_[figure.edges_.array_edges_[i].first_point]
                          [figure.edges_.array_edges_[i].second_point] = 1;
      } else {
        return;
      }
    }
  }

  FigureFacade getResult() { return figure; }
};

class FigureCreator : public Creator {
 public:
  virtual Product* Create() const override {
    return (Product*)(new FigureFacade);
  }
};

#endif  // FIGURE_H
