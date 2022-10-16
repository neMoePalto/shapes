#include "shape.h"


GLuint pyramid_real::create(GLfloat size) {
  GLuint n = glGenLists(1);

  glNewList(n, GL_COMPILE);
  glBegin(GL_TRIANGLE_FAN);
  glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
  glVertex3f(0.0, size, 0.0);
  glVertex3f(-size, -size, size);
  glVertex3f(size, -size, size);
  glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
  glVertex3f(size, -size, -size);
  glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
  glVertex3f(-size, -size, -size);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glVertex3f(-size, -size, size);
  glEnd();

  glBegin(GL_QUADS);
  glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
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

  glNewList(n, GL_COMPILE);

  glBegin(GL_QUADS);
  glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
  glVertex3f(-size, -size, size);
  glVertex3f(size, -size, size);
  glVertex3f(size, -size, -size);
  glVertex3f(-size, -size, -size);
  glEnd();
  glEndList();

  return n;
}
