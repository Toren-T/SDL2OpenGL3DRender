#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>

class Shader{
public:
  //Default constructor for redundancy
  Shader() = default;
  //Take both shader parts for compilation
  Shader(const char *vertex, const char *fragment);

  //Shader Properties pointers(const)
  GLuint sObject() const;
  GLint attribute(const char *name) const;
  GLint uniform(const char *name) const;

private:
  GLuint Compile(const char *shaderData, GLenum shaderType);

private:
    GLuint shaderProgram;
};

#endif
