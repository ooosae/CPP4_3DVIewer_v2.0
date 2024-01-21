#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#define GL_SILENCE_DEPRECATION
#include <stdlib.h>

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>

#include "controller.h"
#include "figure.h"

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  MyOpenGLWidget(QWidget *parent = nullptr);
  ~MyOpenGLWidget() = default;
  FigureFacade &get_figure();
  FigureFacade &get_image();
  void copy_image(FigureFacade &, FigureFacade &);

 public slots:
  void background_color_changed(QColor *new_color);
  void edges_color_changed(QColor *new_color);
  void vertices_color_changed(QColor *new_color);
  void vertices_width_changed(float *new_width);
  void edges_width_changed(float *new_width);
  void edges_type_changed(edges_type_t *new_type);
  void vertices_type_changed(vertex_type_t *new_type);
  void projection_changed(projection_t *new_projection);
  void init_model(QString file_name);
  void redraw();

 protected:
  void initializeGL() override;
  void paintGL() override;

 private:
  bool OK;

  QColor background_color;
  QColor edges_color;
  QColor vertices_color;

  float vertices_width;
  float edges_width;

  FigureFacade figure;
  FigureFacade image;

  edges_type_t edges_type;
  vertex_type_t vertex_type;
  projection_t projection;

  void init_camera();
  void init_settings();
  void draw_edges();
  void draw_vertices();
  int init_image(FigureFacade &, FigureFacade &);
  void image_default();
  void figure_default();

  double current_move_x;
  double current_move_y;
  double current_move_z;
  double current_turn_x;
  double current_turn_y;
  double current_turn_z;
  double current_scale;

 signals:
  void model_information(FigureFacade &);
};

#endif  // MYOPENGLWIDGET_H
