#include "shape.h"

#include <math.h>

#include <QColor>


void set_gl_color(QColor c) {
  glColor4f(c.rgba64().red(),
            c.rgba64().green(),
            c.rgba64().blue(),
            c.rgba64().alpha());
}


GLuint pyramid::create(GLfloat size) {
  GLuint n = glGenLists(1);

  glNewList(n, GL_COMPILE);
  glBegin(GL_TRIANGLE_FAN);
  set_gl_color(Qt::green);
  glVertex3f(0.0, size, 0.0);
  glVertex3f(-size, -size, size);
  glVertex3f(size, -size, size);
  set_gl_color(Qt::yellow);
  glVertex3f(size, -size, -size);
  set_gl_color(Qt::blue);
  glVertex3f(-size, -size, -size);
  set_gl_color(Qt::black);
  glVertex3f(-size, -size, size);
  glEnd();

  glBegin(GL_QUADS);
  set_gl_color(Qt::cyan);
  glVertex3f(-size, -size, size);
  glVertex3f(size, -size, size);
  glVertex3f(size, -size, -size);
  glVertex3f(-size, -size, -size);
  glEnd();
  glEndList();

  return n;
}


GLuint cube::create(GLfloat size) {
  GLuint n = glGenLists(1);

  auto left   = -size;
  auto right  =  size;
  auto bottom = -size;
  auto top    =  size;
  auto far    = -size;
  auto near   =  size;

  glNewList(n, GL_COMPILE);
  glBegin(GL_QUADS);
  set_gl_color(Qt::red);
  glVertex3f(-size, -size, far);
  glVertex3f( size, -size, far);
  glVertex3f( size,  size, far);
  glVertex3f(-size,  size, far);

  set_gl_color(Qt::green);
  glVertex3f(-size, -size, near);
  glVertex3f( size, -size, near);
  glVertex3f( size,  size, near);
  glVertex3f(-size,  size, near);

  set_gl_color(Qt::black);
  glVertex3f(-size, bottom,  size);
  glVertex3f( size, bottom,  size);
  glVertex3f( size, bottom, -size);
  glVertex3f(-size, bottom, -size);

  set_gl_color(Qt::blue);
  glVertex3f(-size, top,  size);
  glVertex3f( size, top,  size);
  glVertex3f( size, top, -size);
  glVertex3f(-size, top, -size);

  set_gl_color(Qt::yellow);
  glVertex3f(left, -size, -size);
  glVertex3f(left,  size, -size);
  glVertex3f(left,  size,  size);
  glVertex3f(left, -size,  size);

  set_gl_color(Qt::cyan);
  glVertex3f(right, -size, -size);
  glVertex3f(right,  size, -size);
  glVertex3f(right,  size,  size);
  glVertex3f(right, -size,  size);
  glEnd();
  glEndList();

  return n;
}


GLuint sphere::create(GLfloat radius) {
  const int lats = 40;
  const int longs = 20;

  GLuint n = glGenLists(1);
  glNewList(n, GL_COMPILE);

  for (int i = 0; i <= lats; i++) {
    double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
    double z0  = sin(lat0);
    double zr0 = cos(lat0);

    double lat1 = M_PI * (-0.5 + (double) i / lats);
    double z1  = sin(lat1);
    double zr1 = cos(lat1);

    glBegin(GL_QUAD_STRIP);

    bool special_color_used = false;
    for(int j = 0; j <= longs; j++) {
      if (j % 5 == 0) {
        set_gl_color(Qt::black);
        special_color_used = true;
      } else if (special_color_used) {
        set_gl_color(Qt::red);
        special_color_used = false;
      }

      double lng = 2 * M_PI * (double) (j - 1) / longs;
      double x = cos(lng);
      double y = sin(lng);

      glNormal3f(x * zr0, y * zr0, z0);
      glVertex3f(radius * x * zr0, radius * y * zr0, radius * z0);
      glNormal3f(x * zr1, y * zr1, z1);
      glVertex3f(radius * x * zr1, radius * y * zr1, radius * z1);
    }
    glEnd();
  }
  glEndList();

  return n;
}
