#include "shape_widget.h"

#include <memory>

#include <QOpenGLFunctions>
#include <QMouseEvent>


shape_widget::shape_widget(shape_type default_type, GLfloat default_size, QWidget* p /*= nullptr*/)
  : QOpenGLWidget(p)
  , shapes_{std::make_shared<pyramid>(),
            std::make_shared<cube>(),
            std::make_shared<sphere>()}
  , default_size_(default_size) {
  Q_ASSERT(static_cast<std::size_t>(default_type) < shapes_.size());

  curr_shape_ = &shapes_.at(static_cast<std::size_t>(default_type));
}


void shape_widget::change_shape(int index)  {
  Q_ASSERT(static_cast<std::size_t>(index) < shapes_.size());

  curr_shape_ = &shapes_.at(index);
  points_ = curr_shape_->get()->create(default_size_);
  update();
}


void shape_widget::change_size(double size) {
  points_ = curr_shape_->get()->create(size);
  update();
}


void shape_widget::initializeGL() {
  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
  f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  f->glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_FLAT);
  points_ = curr_shape_->get()->create(default_size_);
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
  capture_point_ = event->pos();
}


void shape_widget::mouseMoveEvent(QMouseEvent *event) {
  x_rotate_ += 180 * static_cast<GLfloat>((event->position().y() - capture_point_.y()) / height());
  y_rotate_ += 180 * static_cast<GLfloat>((event->position().x() - capture_point_.x()) / width());
  update();
  capture_point_ = event->pos();
}


void shape_widget::closeEvent(QCloseEvent* /*event*/) {
  emit closed();
}
