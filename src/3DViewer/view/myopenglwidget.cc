#include "myopenglwidget.h"

#include <QMessageBox>

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  OK = false;
  image_default();
  figure_default();
}

FigureFacade &MyOpenGLWidget::get_figure() { return figure; }

FigureFacade &MyOpenGLWidget::get_image() { return image; }

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(background_color.redF(), background_color.greenF(),
               background_color.blueF(), 1.0f);
}

void MyOpenGLWidget::paintGL() {
  glClearColor(background_color.redF(), background_color.greenF(),
               background_color.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  init_camera();
  if (OK) {
    draw_edges();
    draw_vertices();
  } else {
    figure_default();
    image_default();
    OK = true;
  }
}

void MyOpenGLWidget::init_model(QString filename) {
  figure_default();
  image_default();

  std::string str = filename.toStdString();
  const char *p = str.c_str();
  ConcreteFigureBuilder builder;
  figure.DownloadFigure(p, builder);
  figure = builder.getResult();
  emit model_information(figure);

  if (init_image(figure, image))
    QMessageBox::critical(this, "Error", "Memory allocate error");
}

void MyOpenGLWidget::init_camera() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection == PERSPECTIVE) {
    double min_x = -1.0;
    double max_x = 1.0;
    double min_y = -1.0;
    double max_y = 1.0;
    double min_z = 1.0;
    double max_z = 10.0;

    if (!figure.points_.array_points_.empty())
      figure.points_.FindMinMaxPoints(min_x, max_x, min_y, max_y, min_z, max_z);

    double padding = 2.0;

    double width = max_x - min_x + 2 * padding;
    double height = max_y - min_y + 2 * padding;
    double depth = max_z - min_z + 2 * padding;

    double centerX = (max_x + min_x) / 2;
    double centerY = (max_y + min_y) / 2;
    double centerZ = (max_z + min_z) / 2;

    double halfWidth = width / 2;
    double halfHeight = height / 2;
    double halfDepth = depth / 2;

    double diagonal = sqrt(halfWidth * halfWidth + halfHeight * halfHeight +
                           halfDepth * halfDepth);

    min_x = centerX - diagonal;
    max_x = centerX + diagonal;
    min_y = centerY - diagonal;
    max_y = centerY + diagonal;
    min_z = centerZ - diagonal;
    max_z = centerZ + diagonal;

    glFrustum(min_x / 10.0, max_x / 10.0, min_y / 10.0, max_y / 10.0, 1,
              1000000);
    glTranslatef(0, 0, -fabs(min_z));
  } else {
    double min_x = -1.0;
    double max_x = 1.0;
    double min_y = -1.0;
    double max_y = 1.0;
    double min_z = 1.0;
    double max_z = 10.0;
    if (!figure.points_.array_points_.empty())
      figure.points_.FindMinMaxPoints(min_x, max_x, min_y, max_y, min_z, max_z);
    double padding = 2.0;

    double width = max_x - min_x + 2 * padding;
    double height = max_y - min_y + 2 * padding;
    double depth = max_z - min_z + 2 * padding;

    double centerX = (max_x + min_x) / 2;
    double centerY = (max_y + min_y) / 2;
    double centerZ = (max_z + min_z) / 2;

    double halfWidth = width / 2;
    double halfHeight = height / 2;
    double halfDepth = depth / 2;

    double diagonal = sqrt(halfWidth * halfWidth + halfHeight * halfHeight +
                           halfDepth * halfDepth);

    min_x = centerX - diagonal;
    max_x = centerX + diagonal;
    min_y = centerY - diagonal;
    max_y = centerY + diagonal;
    min_z = centerZ - diagonal;
    max_z = centerZ + diagonal;

    glOrtho(min_x, max_x, min_y, max_y, 0, 1000000);
    glTranslatef(0.0f, 0.0f, -fabs(min_z));
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void MyOpenGLWidget::init_settings() {
  background_color.setRgbF(0.0f, 0.0f, 0.0f);
  edges_color.setRgbF(1, 0, 0);
  vertices_color.setRgbF(0, 0, 1);
  current_move_y = 0;
  current_move_z = 0;
  current_turn_x = 0;
  current_turn_y = 0;
  current_turn_z = 0;
  current_scale = 0;
  vertex_type = NONE;
  edges_type = SOLID;
}

void MyOpenGLWidget::draw_edges() {
  if (edges_type == DOTTED) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  }

  glColor3f(edges_color.redF(), edges_color.greenF(), edges_color.blueF());
  glLineWidth(edges_width);

  glBegin(GL_LINES);
  for (size_t i = 0; i < image.edges_.array_edges_.size(); ++i) {
    int v1 = image.edges_.array_edges_[i].first_point - 1;
    int v2 = image.edges_.array_edges_[i].second_point - 1;
    glVertex3f(image.points_.array_points_[v1].x_,
               image.points_.array_points_[v1].y_,
               image.points_.array_points_[v1].z_);
    glVertex3f(image.points_.array_points_[v2].x_,
               image.points_.array_points_[v2].y_,
               image.points_.array_points_[v2].z_);
  }
  glEnd();

  if (edges_type == DOTTED) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void MyOpenGLWidget::draw_vertices() {
  if (vertex_type != NONE) {
    if (vertex_type == CIRCLE) glEnable(GL_POINT_SMOOTH);
    glColor3f(vertices_color.redF(), vertices_color.greenF(),
              vertices_color.blueF());
    glPointSize(vertices_width);
    glBegin(GL_POINTS);

    for (size_t i = 0; i < image.points_.array_points_.size(); i++) {
      glVertex3f(image.points_.array_points_[i].x_,
                 image.points_.array_points_[i].y_,
                 image.points_.array_points_[i].z_);
    }

    glEnd();
    if (vertex_type == CIRCLE) glDisable(GL_POINT_SMOOTH);
  }
}

void MyOpenGLWidget::background_color_changed(QColor *new_color) {
  background_color.setRed(new_color->red());
  background_color.setGreen(new_color->green());
  background_color.setBlue(new_color->blue());
  update();
}

void MyOpenGLWidget::edges_color_changed(QColor *new_color) {
  edges_color.setRed(new_color->red());
  edges_color.setGreen(new_color->green());
  edges_color.setBlue(new_color->blue());
  update();
}

void MyOpenGLWidget::vertices_color_changed(QColor *new_color) {
  vertices_color.setRed(new_color->red());
  vertices_color.setGreen(new_color->green());
  vertices_color.setBlue(new_color->blue());
  update();
}

void MyOpenGLWidget::vertices_width_changed(float *new_width) {
  vertices_width = *new_width;
  update();
}

void MyOpenGLWidget::edges_width_changed(float *new_width) {
  edges_width = *new_width;
  update();
}

void MyOpenGLWidget::edges_type_changed(edges_type_t *new_type) {
  edges_type = *new_type;
  update();
}

void MyOpenGLWidget::vertices_type_changed(vertex_type_t *new_type) {
  vertex_type = *new_type;
  update();
}

void MyOpenGLWidget::projection_changed(projection_t *new_projection) {
  projection = *new_projection;
  update();
}

void MyOpenGLWidget::redraw() { update(); }

int MyOpenGLWidget::init_image(FigureFacade &src, FigureFacade &dst) {
  copy_image(src, dst);
  return EXIT_SUCCESS;
}

void MyOpenGLWidget::copy_image(FigureFacade &src, FigureFacade &dst) {
  dst.faces_.array_faces_ = src.faces_.array_faces_;
  dst.points_.array_points_ = src.points_.array_points_;
  dst.edges_.array_edges_ = src.edges_.array_edges_;
  dst.points_.points_table_ = src.points_.points_table_;
  dst.center_ = src.center_;
}

void MyOpenGLWidget::image_default() {
  image.points_.array_points_.clear();
  image.edges_.array_edges_.clear();
  image.points_.points_table_.clear();
  image.faces_.array_faces_.clear();
  image.center_.x_ = 0;
  image.center_.y_ = 0;
  image.center_.z_ = 0;
}

void MyOpenGLWidget::figure_default() {
  figure.points_.array_points_.clear();
  figure.edges_.array_edges_.clear();
  figure.points_.points_table_.clear();
  figure.faces_.array_faces_.clear();
  figure.center_.x_ = 0;
  figure.center_.y_ = 0;
  figure.center_.z_ = 0;
}
