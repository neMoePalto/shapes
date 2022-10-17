#pragma once

#include <GL/gl.h>


class shape {
public:
  shape() = default;
  virtual ~shape() = default;
  virtual GLuint create(GLfloat size) = 0;
};


class pyramid : public shape {
public:
  GLuint create(GLfloat size) override;
};


class cube : public shape {
public:
  GLuint create(GLfloat size) override;
};


class sphere : public shape {
public:
  GLuint create(GLfloat radius) override;
};
