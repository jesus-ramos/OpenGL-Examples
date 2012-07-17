#include "mesh.hpp"

Mesh::~Mesh()
{
    delete_buffers(&vbo_verts);
    delete_buffers(&vbo_normals);
    delete_buffers(&ibo_elements);
}

void Mesh::upload()
{

}

void Mesh::draw()
{

}

void Mesh::draw_bounding_box()
{
    
}
