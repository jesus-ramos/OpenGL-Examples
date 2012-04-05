attribute vec2 coord2d;
attribute vec3 vert_color;

varying vec3 frag_color;

uniform mat4 transform_mat;

void main(void)
{
    gl_Position = transform_mat * vec4(coord2d, 0.0, 1.0);
    frag_color = vert_color;
}
