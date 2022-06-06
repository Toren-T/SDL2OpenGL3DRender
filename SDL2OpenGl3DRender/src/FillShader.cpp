#include "FillShader.h"

#include "ShaderManager.h"

#include <GL/glew.h>

#include <stdexcept>

namespace {
  Shader newShader;

  GLuint vao;
  GLuint vbo;
}

void FillShader::init(){
  //GLSL shaders that are compiled at run time
  //Vertex shader file
  static const char *vertexCode =
      "layout(location = 0) in vec3 loc;\n"

      "void main(){\n"
      "  gl_Position = vec4(loc, 1.0);\n"
      "}\n";

  //Fragment shader file
  static const char *fragmentCode =
      "out vec3 color;\n"
      "void main(){\n"
      "  color = vec3(0.8f, 0.8f, 0.8f);\n"
      "}\n";

  //Create new shader
  newShader = Shader(vertexCode, fragmentCode);

  //Create vertex array and set as current
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //Create buffer and set as current
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  //Create square for shading
  GLfloat vertexData[] = {
    -1.f, -1.f,
     1.f, -1.f,
    -1.f,  1.f,
     1.f,  1.f
  };
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

  //Unbind the vertex array and vertex buffer
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void FillShader::fill(){
  //Error check if shader is created
  if(!newShader.sObject())
    throw std::runtime_error("FillShader drawn before initialized.");

  //Use the current shader
  glUseProgram(newShader.sObject());
  glBindVertexArray(vao);

  //TODO code to resize shader

  //Draw background
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  //Unbind shader object
  glBindVertexArray(0);
  glUseProgram(0);
}
