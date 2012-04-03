#include <stdlib.h>>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#include "shader_utils.h"

char *read_shader_file(const char *filename)
{
    FILE *fp;
    char *data;
    int f;
    int size;

    f = open(filename, O_RDONLY);
    if (!f)
        goto file_error;
    size = lseek(f, 0, SEEK_END);
    close(f);

    fp = fopen(filename, "rt");
    if (!fp)
        goto file_error;

    data = malloc(size + 1);
    if (!data)
    {
        printf("No memory could be allocated for shader text\n");
        return 0;
    }
    size = fread(data, sizeof(char), size, fp);
    data[size] = '\0';

    fclose(fp);

    return data;

file_error:
    printf("Failed to read shader file: %s\n", filename);
    return 0;
}

void print_error(GLuint obj)
{
    GLint log_len;
    char *log;

    if (glIsShader(obj))
        glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &log_len);
    else
        glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &log_len);

    log = malloc(log_len);
    if (glIsShader(obj))
        glGetShaderInfoLog(obj, log_len, NULL, log);
    else
        glGetProgramInfoLog(obj, log_len, NULL, log);

    printf("%s\n", log);
    free(log);
}

int compile_shader(GLuint shader, char *data)
{
    GLint buff_len;
    GLsizei str_len;
    GLint compiled;
    GLchar *log;
    int len;

    len = strlen(data);

    glShaderSource(shader, 1, (const GLchar **)&data, &len);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE)
    {
        print_error(shader);
        return 0;
    }

    return 1;
}

GLuint create_shader(const char *filename, GLenum type)
{
    GLuint shader = glCreateShader(type);
    char *data;

    data = read_shader_file(filename);
    if (!data)
        return 0;

    if (!compile_shader(shader, data))
    {
        print_error(shader);
        free(data);
        glDeleteShader(shader);
        return 0;
    }

    free(data);
    
    return shader;
}

int link_shaders(GLuint program)
{
    GLint res;

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &res);
    if (res == GL_FALSE)
    {
        print_error(program);
        return 0;
    }

    return 1;
}
