uniform float fade;

varying vec3 frag_color;

void main(void)
{
    gl_FragColor = vec4(frag_color.x, frag_color.y, frag_color.z, fade);
}
