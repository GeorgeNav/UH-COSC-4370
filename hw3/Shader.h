

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
public:
  GLuint Program;
  // Constructor generates the shader on the fly
  Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
  {
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensures ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try
    {
      // Open files
      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);
      std::stringstream vShaderStream, fShaderStream;
      // Read file's buffer contents into streams
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();
      // close file handlers
      vShaderFile.close();
      fShaderFile.close();
      // Convert stream into string
      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
      std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    // 2. Compile shaders
    // Vertex Shader
    GLuint vertex = CompileShader(GL_VERTEX_SHADER, vertexCode.c_str());
    // Fragment Shader
    GLuint fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());
    // Shader Program
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);

    // Print linking errors if any
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                << infoLog << std::endl;
    }
    
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }

  GLuint CompileShader(GLuint type, const GLchar *code) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    
    // Print compile errors if any
    GLint success;
    std::string typeString = "?";
    if(type == GL_VERTEX_SHADER)
      typeString = "Vertex";
    else if(type == GL_FRAGMENT_SHADER)
      typeString = "Fragment";
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      GLchar infoLog[512];
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::" << typeString << "::COMPILATION_FAILED\n"
                << infoLog << std::endl;
      return 0;
    }
    return shader;
  }

  // Uses the current shader
  void Use()
  {
    glUseProgram(this->Program);
  }

  void SetVec3(const std::string &name, const glm::vec3 &value)
  { 
    GLuint uniformVariable = glGetUniformLocation(this->Program, name.c_str());
    glUniform3fv(uniformVariable, 1, &value[0]); 
  }
  void SetMat4(const std::string &name, const glm::mat4 &mat)
  {
    GLuint uniformVariable = glGetUniformLocation(this->Program, name.c_str());
    glUniformMatrix4fv(uniformVariable, 1, GL_FALSE, &mat[0][0]);
  }
  void SetInt(const std::string &name, int value)
  { 
    GLuint uniformVariable = glGetUniformLocation(this->Program, name.c_str());
    glUniform1i(uniformVariable, (GLint)value); 
  }
};

#endif
