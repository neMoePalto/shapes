#pragma once

#include <vector>

#include <QtOpenGLWidgets/QOpenGLWidget>

#include "shape.h"


class shape_widget : public QOpenGLWidget {
public:
  shape_widget(QWidget *parent = nullptr);
  ~shape_widget() = default;
  void change_shape(int index);

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

private:
  const std::vector<std::shared_ptr<shape>> shapes_;
  const std::shared_ptr<shape>* curr_shape_ = nullptr;

  GLuint  points_;
  GLfloat x_rotate_ = 0.0; // is need ?
  GLfloat y_rotate_ = 0.0; // is need ?
  QPoint  capture_point_;
};
