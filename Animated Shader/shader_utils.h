#ifndef _SHADER_UTILS_H
#define _SHADER_UTILS_H

#include <GL/glew.h>

GLuint create_shader(const char *filename, GLenum type);
int link_shaders(GLuint program);

#endif
