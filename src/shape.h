#pragma once

#include <GL/gl.h>


class shape {
public:
  shape() = default;
  virtual ~shape() = default;
  virtual GLuint create(GLfloat size = 1.0f) = 0;
};


class pyramid_real : public shape {
public:
  GLuint create(GLfloat size = 1.0f) override;
};


class cube : public shape {
public:
  GLuint create(GLfloat size = 1.0f) override;

};
