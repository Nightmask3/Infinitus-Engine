#version 450 core
in vec4 ex_color;
in vec2 Texcoord;
out vec4 out_color;
uniform sampler2D Texture;
void main()
{
	out_color = ex_color * texture(Texture, Texcoord);
}