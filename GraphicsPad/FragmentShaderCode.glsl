#version 430

out vec4 color;
in vec3 inputColor;

void main()
{
	color = vec4(inputColor, 1.0);
}