#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec3 vertexColor;

uniform mat4 modelTransformMatrix;
uniform mat4 projectionMatrix;


out vec3 inputColor;

void main()
{
	vec4 v = vec4(position, 1.0);
	vec4 newPosition = modelTransformMatrix * v;
	vec4 projectedPostion = projectionMatrix * newPosition;
	gl_Position = projectedPostion;
	inputColor = vertexColor;
}