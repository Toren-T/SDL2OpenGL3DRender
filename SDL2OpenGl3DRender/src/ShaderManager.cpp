#include "ShaderManager.h"

#include <GL/glew.h>

#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

Shader::Shader(const char *vertex, const char *fragment){
  //Manage and create shaders
  //Vertex shader manages the location and the shape of the shader
  GLuint vertexShader = Compile(vertex, GL_VERTEX_SHADER);
  //Fragment shader manages the colour and how the shader looks
  GLuint fragmentShader = Compile(fragment, GL_FRAGMENT_SHADER);

  //Create and check shader program.
  shaderProgram = glCreateProgram();
  if(!shaderProgram)
    throw std::runtime_error("Create OpenGL shader program failure.");

  //Link shaders to program
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  //Link the program
  glLinkProgram(shaderProgram);

  //Clean up
  glDetachShader(shaderProgram, vertexShader);
  glDetachShader(shaderProgram, fragmentShader);

  //Check link
  GLint status;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
  if(status == GL_FALSE)
    throw std::runtime_error("OpenGL shader linking failure.");
}

//Get shader object
GLuint Shader::sObject() const{
  return shaderProgram;
}

GLint Shader::attribute(const char *name) const{
  //Set OpenGL shader attribute
  GLint attrib = glGetAttribLocation(shaderProgram, name);
  //Check if valid attribute
  if(attrib == -1)
    throw std::runtime_error("Attribute \"" + std::string(name) + "\" not found.");

  return attrib;
}

GLint Shader::uniform(const char *name) const{
  //Set OpenGL shader uniform
  GLint uni = glGetUniformLocation(shaderProgram, name);
  //Check if valid uniform
  if(uni == -1)
    throw std::runtime_error("Uniform \"" + std::string(name) + "\" not found.");

  return uni;
}

GLuint Shader::Compile(const char *shaderData, GLenum shaderType){
  //Create shader from input type
  GLuint shaderObject = glCreateShader(shaderType);
  if(!shaderObject)
    throw std::runtime_error("Sharder creation failure.");

  //Get OpenGL version and add it to string
  static std::string version;
  if(version.empty()){
    version = "#version ";
    std::string glsl = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
    for(char c : glsl){
      if(std::isspace(c))
        break;
      if(std::isdigit(c))
        version += c;
    }
    version += '\n';
  }
  //Get length of shaderfile
  size_t length = std::strlen(shaderData);
  //Determan amount of lines in file
  std::vector<GLchar> text(version.length() + length + 1);
  //Copy shaderfile
  std::memcpy(&text.front(), version.data(), version.length());
  std::memcpy(&text.front() + version.length(), shaderData, length);
  //Put null terminator on last line
  text[version.length() + length] = '\0';

  //Use copy to make OpenGL shaderfile
  const GLchar *cText = &text.front();
  //Compile and apply shader
  glShaderSource(shaderObject, 1, &cText, nullptr);
  glCompileShader(shaderObject);

  //Get status of shader
  GLint status;
  glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &status);
  //Check for shader errors
  if(status == GL_FALSE){
    //Output version of OpenGL and shaderdata
    std::string error = version;
    error += std::string(shaderData, length);

    //Error data
    static const int SIZE = 4096;
    GLchar eMessage[SIZE];
    GLsizei length;

    //Put Error log together
    glGetShaderInfoLog(shaderObject, SIZE, &length, eMessage);
    error += std::string(eMessage, length);
    //Output error to debugger //Todo 1
    std::printf("%s \n", error.c_str());
    throw std::runtime_error("Shader compilation failure.");
  }

  return shaderObject;
}

