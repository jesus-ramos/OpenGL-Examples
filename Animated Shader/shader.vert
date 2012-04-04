attribute vec2 coord2d;
attribute vec3 vert_color;

varying vec3 frag_color;

void main(void)
{
    gl_Position = vec4(coord2d, 0.0, 1.0);
    frag_color = vert_color;
}
