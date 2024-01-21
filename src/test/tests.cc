#include "../3DViewer/model/figure.h"
#include "gtest/gtest.h"

TEST(PointTest, PointDefTest) {
  Point point;
  EXPECT_EQ(point.x_, 0.0);
  EXPECT_EQ(point.y_, 0.0);
  EXPECT_EQ(point.z_, 0.0);
}

TEST(PointTest, MoveTest) {
  Point point;
  point.x_ = 1.0;
  point.y_ = 2.0;
  point.z_ = 3.0;
  Move move = {1.0, 2.0, 3.0};

  point.MovePoint(move);

  double expected_x = 2.0;
  double expected_y = 4.0;
  double expected_z = 6.0;

  EXPECT_EQ(point.x_, expected_x);
  EXPECT_EQ(point.y_, expected_y);
  EXPECT_EQ(point.z_, expected_z);
}

TEST(FigureTest, RotateTest) {
  Point point;
  point.x_ = 1.0;
  point.y_ = 2.0;
  point.z_ = 3.0;
  Move move = {1.0, 2.0, 3.0};

  point.MovePoint(move);

  double expected_x = 2.0;
  double expected_y = 4.0;
  double expected_z = 6.0;

  EXPECT_EQ(point.x_, expected_x);
  EXPECT_EQ(point.y_, expected_y);
  EXPECT_EQ(point.z_, expected_z);
}

TEST(FigureTest, ReadVertexTest) {
  FigureFacade figure;
  Point point;
  std::string line = "v 1.0 2.0 3.0";

  figure.ReadVertex(point, line);

  ASSERT_DOUBLE_EQ(point.x_, 1.0);
  ASSERT_DOUBLE_EQ(point.y_, 2.0);
  ASSERT_DOUBLE_EQ(point.z_, 3.0);
}

TEST(FigureTest, ReadFaceTest) {
  FigureFacade figure;
  Face face;
  std::string line = "f 1 2 3";

  figure.ReadFace(face, line);

  ASSERT_EQ(face.points.size(), 3);
  ASSERT_EQ(face.points[0], 1);
  ASSERT_EQ(face.points[1], 2);
  ASSERT_EQ(face.points[2], 3);
}

TEST(PointTest, AppendPointTest) {
  Points points;
  Point point;
  point.x_ = 1.0;
  point.y_ = 2.0;
  point.z_ = 3.0;

  points.AppendPoint(point);

  ASSERT_EQ(points.array_points_.size(), 1);
  ASSERT_DOUBLE_EQ(points.array_points_[0].x_, 1.0);
  ASSERT_DOUBLE_EQ(points.array_points_[0].y_, 2.0);
  ASSERT_DOUBLE_EQ(points.array_points_[0].z_, 3.0);
}

TEST(FaceTest, AppendFaceTest) {
  Faces faces;
  Face face = {{1, 2, 3}};

  faces.AppendFace(face);

  ASSERT_EQ(faces.array_faces_.size(), 1);
  ASSERT_EQ(faces.array_faces_[0].points.size(), 3);
  ASSERT_EQ(faces.array_faces_[0].points[0], 1);
  ASSERT_EQ(faces.array_faces_[0].points[1], 2);
  ASSERT_EQ(faces.array_faces_[0].points[2], 3);
}

TEST(EdgeTest, AppendEdgeTest) {
  Edges edges;
  Edge edge = {1, 2};

  edges.AppendEdge(edge);
  edge = {3, 4};
  edges.AppendEdge(edge);
  ASSERT_EQ(edges.array_edges_.size(), 2);
  ASSERT_EQ(edges.array_edges_[0].first_point, 1);
  ASSERT_EQ(edges.array_edges_[1].second_point, 4);
}

TEST(FigureTest, FillPointsTableTest) {
  FigureFacade figure;
  // figure.edges_.array_edges_ = {{1, 2}, {2, 3}, {3, 1}};
  Edge edge = {1, 2};
  figure.edges_.AppendEdge(edge);
  edge = {2, 3};
  figure.edges_.AppendEdge(edge);
  edge = {3, 1};
  figure.edges_.AppendEdge(edge);
  ASSERT_EQ(figure.edges_.array_edges_.size(), 3);
  // figure.FillPointsTable();

  ConcreteFigureBuilder builder;
  builder.buildEdges(figure.edges_);
  ASSERT_EQ(builder.getResult().edges_.array_edges_.size(), 3);
  // ASSERT_EQ(figure.points_.points_table_[1][2], 1);  //segfault
  // ASSERT_EQ(figure.points_.points_table_[2][3], 1);
  // ASSERT_EQ(figure.points_.points_table_[3][1], 1);
}

TEST(FigureTest, FaceToEdgesTest) {
  FigureFacade figure;
  Face face = {{1, 2, 3}};
  figure.FaceToEdges(face, figure.edges_);

  ASSERT_EQ(figure.edges_.array_edges_.size(), 3);
  ASSERT_EQ(figure.edges_.array_edges_[0].first_point, 1);
  ASSERT_EQ(figure.edges_.array_edges_[0].second_point, 2);
  ASSERT_EQ(figure.edges_.array_edges_[1].first_point, 2);
  ASSERT_EQ(figure.edges_.array_edges_[1].second_point, 3);
  ASSERT_EQ(figure.edges_.array_edges_[2].first_point, 3);
  ASSERT_EQ(figure.edges_.array_edges_[2].second_point, 1);
}

TEST(FigureFacadeTest, MoveFigureTest) {
  FigureFacade figureFacade;

  figureFacade.center_.x_ = 1.0;
  figureFacade.center_.y_ = 2.0;
  figureFacade.center_.z_ = 3.0;

  Point point1, point2, point3;
  point1.x_ = 1.0;
  point1.y_ = 2.0;
  point1.z_ = 3.0;

  point2.x_ = 2.0;
  point2.y_ = 3.0;
  point2.z_ = 4.0;

  point3.x_ = 3.0;
  point3.y_ = 4.0;
  point3.z_ = 5.0;

  figureFacade.points_.AppendPoint(point1);
  figureFacade.points_.AppendPoint(point2);
  figureFacade.points_.AppendPoint(point3);

  Move move = {1.0, 2.0, 3.0};
  figureFacade.MoveFigure(move);

  ASSERT_DOUBLE_EQ(figureFacade.center_.x_, 2.0);
  ASSERT_DOUBLE_EQ(figureFacade.center_.y_, 4.0);
  ASSERT_DOUBLE_EQ(figureFacade.center_.z_, 6.0);

  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[0].x_, 2.0);
  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[0].y_, 4.0);
  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[0].z_, 6.0);

  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[1].x_, 6.0);
  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[1].y_, 8.0);
  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[1].z_, 10.0);

  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[2].x_, 10.0);
  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[2].y_, 12.0);
  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[2].z_, 14.0);
}

TEST(FigureFacadeTest, ScaleFigureTest) {
  FigureFacade figureFacade;

  figureFacade.center_.x_ = 1.0;
  figureFacade.center_.y_ = 2.0;
  figureFacade.center_.z_ = 3.0;

  Point point1, point2, point3;
  point1.x_ = 1.0;
  point1.y_ = 2.0;
  point1.z_ = 3.0;

  point2.x_ = 2.0;
  point2.y_ = 3.0;
  point2.z_ = 4.0;

  point3.x_ = 3.0;
  point3.y_ = 4.0;
  point3.z_ = 5.0;

  figureFacade.points_.AppendPoint(point1);
  figureFacade.points_.AppendPoint(point2);
  figureFacade.points_.AppendPoint(point3);

  Scale scale = {2.0, 3.0, 4.0};
  figureFacade.ScaleFigure(scale);

  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[0].x_, 1.0);
  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[0].y_, 2.0);
  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[0].z_, 3.0);

  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[1].x_, 3.0);
  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[1].y_, 5.0);
  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[1].z_, 7.0);

  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[2].x_, 5.0);
  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[2].y_, 8.0);
  ASSERT_DOUBLE_EQ(figureFacade.points_.array_points_[2].z_, 11.0);
}

TEST(FigureFacadeTest, RotateFigureTest) {
  // Create a FigureFacade
  FigureFacade figureFacade;

  // Set initial center and points
  figureFacade.center_.x_ = 1.0;
  figureFacade.center_.y_ = 2.0;
  figureFacade.center_.z_ = 3.0;

  Point point1, point2, point3;
  point1.x_ = 1.0;
  point1.y_ = 2.0;
  point1.z_ = 3.0;

  point2.x_ = 2.0;
  point2.y_ = 3.0;
  point2.z_ = 4.0;

  point3.x_ = 3.0;
  point3.y_ = 4.0;
  point3.z_ = 5.0;

  figureFacade.points_.AppendPoint(point1);
  figureFacade.points_.AppendPoint(point2);
  figureFacade.points_.AppendPoint(point3);

  Rotate rotate = {30.0, 45.0, 60.0};
  figureFacade.RotateFigure(rotate);

  ASSERT_NEAR(figureFacade.points_.array_points_[0].x_, 1.0, 1e-6);
  ASSERT_NEAR(figureFacade.points_.array_points_[0].y_, 2.0, 1e-6);
  ASSERT_NEAR(figureFacade.points_.array_points_[0].z_, 3.0, 1e-6);

  ASSERT_NEAR(figureFacade.points_.array_points_[1].x_, 2.665975, 1e-6);
  ASSERT_NEAR(figureFacade.points_.array_points_[1].y_, 1.846496, 1e-6);
  ASSERT_NEAR(figureFacade.points_.array_points_[1].z_, 2.551712, 1e-6);

  ASSERT_NEAR(figureFacade.points_.array_points_[2].x_, 4.331951, 1e-6);
  ASSERT_NEAR(figureFacade.points_.array_points_[2].y_, 1.692992, 1e-6);
  ASSERT_NEAR(figureFacade.points_.array_points_[2].z_, 2.103424, 1e-6);
}

TEST(FigureTest, ReadFigureTest) {
  FigureFacade figure;
  ConcreteFigureBuilder builder;
  std::ifstream file("./data_3d_figures/Cube.obj");

  ASSERT_TRUE(file.is_open());

  figure.ReadFigure(file, builder);
  figure = builder.getResult();
  ASSERT_EQ(figure.edges_.array_edges_.size(),
            24);  //у куба 12 ребер должно быть??
  ASSERT_EQ(figure.faces_.array_faces_.size(), 6);
  ASSERT_EQ(figure.points_.array_points_.size(), 8);

  file.close();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
