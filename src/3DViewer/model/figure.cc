#include "figure.h"

void FigureFacade::DownloadFigure(const std::string& filename,
                                  ConcreteFigureBuilder& builder) {
  std::ifstream fin(filename);
  if (fin.is_open()) {
    ReadFigure(fin, builder);
    fin.close();
  }
}

void FigureFacade::MoveFigure(const Move& move) {
  center_.MovePoint(move);
  points_.MoveAllPoints(move);
  double value = (move.dz > 0.0) ? (move.dz + 1) : (-1 / (move.dz - 1));
  Scale scale = {value, value, value};
  ScaleFigure(scale);
}

void FigureFacade::ScaleFigure(const Scale& scale) {
  points_.ScaleAllPoints(center_, scale);
}

void FigureFacade::RotateFigure(const Rotate& rotate) {
  points_.RotateAllPoints(center_, rotate);
}

void FigureFacade::SaveFigure(const std::string& filename) {
  std::ofstream fout(filename);
  if (fout.is_open()) {
    points_.SaveAllPoints(fout);
    edges_.SaveAllEdges(fout);
    faces_.SaveAllFaces(fout);
    fout.close();
  }
}

void FigureFacade::ReadFigure(std::ifstream& fin, FigureBuilder& builder) {
  std::string line;

  EdgesCreator edgesCreator;
  Edges* edges = (Edges*)edgesCreator.Create();

  PointsCreator pointsCretor;
  Points* points = (Points*)pointsCretor.Create();

  FacesCreator facesCreator;
  Faces* faces = (Faces*)facesCreator.Create();

  while (std::getline(fin, line)) {
    if (line.substr(0, 2) == "v ") {
      Point vertex;
      ReadVertex(vertex, line);
      points->AppendPoint(vertex);
    } else if (line.substr(0, 2) == "f ") {
      Face face;
      ReadFace(face, line);
      faces->AppendFace(face);
    }
  }
  builder.buildFaces(*faces);
  builder.buildPoints(*points);
  builder.buildPointsTable();

  for (size_t i = 0; i < faces->array_faces_.size(); ++i) {
    FaceToEdges(faces->array_faces_[i], *edges);
  }
  builder.buildEdges(*edges);
}

void FigureFacade::ReadVertex(Point& point, const std::string& line) {
  std::istringstream iss(line);
  std::string v;
  iss >> v >> point.x_ >> point.y_ >> point.z_;
}

void FigureFacade::ReadFace(Face& face, const std::string& line) {
  std::istringstream iss(line);
  std::string token;
  int num_tokens = 0;
  while (iss >> token) {
    if (num_tokens > 0) {
      int point_index;
      std::istringstream(token) >> point_index;
      face.points.push_back(point_index);
    }
    num_tokens++;
  }
}

void FigureFacade::FaceToEdges(const Face& face, Edges& edges) {
  for (size_t i = 0; i < face.points.size(); ++i) {
    Edge edge;
    edge.first_point = face.points[i];
    edge.second_point = face.points[(i + 1) % face.points.size()];
    if (!ExistEdge(edge)) {
      edges.AppendEdge(edge);
    }
  }
}

bool FigureFacade::ExistEdge(const Edge& edge) {
  if (static_cast<size_t>(edge.first_point) < points_.points_table_.size() &&
      static_cast<size_t>(edge.second_point) <
          points_.points_table_[edge.first_point].size()) {
    return points_.points_table_[edge.first_point][edge.second_point] == 1;
  } else {
    return false;
  }
}
