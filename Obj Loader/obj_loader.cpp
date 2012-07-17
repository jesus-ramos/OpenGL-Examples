#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>

#include <glm/glm.hpp>

using namespace std;

void load_obj(const char *filename, vector<glm::vec4> &vertices, vector<glm::vec3> &normals,
              vector<GLushort> &elements)
{
    ifstream in(filename, ios::in);
    string line;
    int i;

    if (!in)
    {
        cerr << "Cannot open " << filename << endl;
        exit(EXIT_FAILURE);
    }

    while (getline(in, line))
    {
        istringstream s(line.substr(2));
        switch (line[0])
        {
            case 'v':
            {
                glm::vec4 v;
                s >> v.x;
                s >> v.y;
                s >> v.z;
                v.w = 1.0f;
                vertices.push_back(v);
                break;
            }
            case 'f':
                GLushort a, b, c;
                s >> a;
                s >> b;
                s >> c;
                elements.push_back(--a);
                elements.push_back(--b);
                elements.push_back(--c);
                break;
        }
    }
}
