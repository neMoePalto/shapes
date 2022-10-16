#include "shape_widget.h"

#include <cassert>
#include <memory>

#include <QOpenGLFunctions>
#include <QMouseEvent>


shape_widget::shape_widget(QWidget *parent /*= nullptr*/)
  : QOpenGLWidget(parent)
  , shapes_{std::make_shared<pyramid_real>(),
            std::make_shared<cube>()} {

  curr_shape_ = &shapes_.at(0);
}


//shape_widget::~shape_widget() {
//  for (const auto* s : shapes_) {
//    delete s;
//  }
//}


void shape_widget::initializeGL() {
  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
  f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  f->glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_FLAT);
  points_ = curr_shape_->get()->create(1.2f);
}


void shape_widget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
}


void shape_widget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -3.0);

  glRotatef(x_rotate_, 1.0, 0.0, 0.0);
  glRotatef(y_rotate_, 0.0, 1.0, 0.0);

  glCallList(points_);
}


void shape_widget::mousePressEvent(QMouseEvent *event) {
  qDebug() << "mousePressEvent()";
  capture_point_ = event->pos();
}


void shape_widget::mouseMoveEvent(QMouseEvent *event) {
  x_rotate_ += 180 * static_cast<GLfloat>((event->position().y() - capture_point_.y()) / height());
  y_rotate_ += 180 * static_cast<GLfloat>((event->position().x() - capture_point_.x()) / width());
  update();
  capture_point_ = event->pos();
}


void shape_widget::change_shape(int index)  {
  qDebug() << "index = " << index;
  assert(static_cast<std::size_t>(index) < shapes_.size());
  curr_shape_ = &shapes_.at(index);
  points_ = curr_shape_->get()->create(1.2f);
//  initializeGL();
  update();
}
