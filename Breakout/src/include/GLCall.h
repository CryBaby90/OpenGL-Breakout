#ifndef GLCALL_H
#define GLCALL_H

#include <glad/glad.h>  //glad.c 需要包含在项目目录中
#include <GLFW/glfw3.h>

#include <iostream>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ") :" << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

#endif


