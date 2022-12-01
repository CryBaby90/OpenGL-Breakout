#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <GLFW/glfw3.h>

class Texture2D
{
public:
    GLuint ID;
    GLuint Width, Height; // Width and height of loaded image in pixels
    // Texture Format
    GLuint Internal_Format; // Format of texture object
    GLuint Image_Format; // Format of loaded image

    // Texture configuration
    GLuint Wrap_S; // Wrapping mode on S axis
    GLuint Wrap_T; // Wrapping mode on T axis
    GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
    GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels


    Texture2D();

    void Generate(GLuint width, GLuint height, unsigned char* data);
    void Bind() const;
};

#endif
