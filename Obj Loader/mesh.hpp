#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>

using namespace std;

class Mesh
{
private:
    GLuint vbo_verts, vbo_normals, ibo_elements;
public:
    vector<glm::vec4> vertices;
    vector<glm::vec3> normals;
    vector<GLushort> elements;
    glm::mat4 obj_to_world;

    Mesh() : vbo_verts(0), vbo_normals(0), ibo_elements(0),
             obj_to_world(glm::mat4(1)) { }
    ~Mesh();

    void upload();
    void draw();
    void draw_bounding_box();
};

inline void delete_buffers(GLuint *buff)
{
    if (*buff)
        glDeleteBuffers(1, buff);
}

#endif /* MESH_HPP */
