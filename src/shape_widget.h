#pragma once

#include <vector>

#include <QtOpenGLWidgets/QOpenGLWidget>

#include "shape.h"


enum class shape_type {
  pyramid,
  cube,
  sphere
};


class shape_widget : public QOpenGLWidget {
  Q_OBJECT

public:
  shape_widget(shape_type default_type, GLfloat default_size, QWidget* p = nullptr);
  void change_shape(int index);
  void change_size(double size);

signals:
  void closed();

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void closeEvent(QCloseEvent* event) override;

private:
  const std::vector<std::shared_ptr<shape>> shapes_;
  const std::shared_ptr<shape>* curr_shape_ = nullptr;
  const float default_size_;

  GLuint  points_        = 0;
  GLfloat x_rotate_      = 0.;
  GLfloat y_rotate_      = 0.;
  QPoint  capture_point_;
};
