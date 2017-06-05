#version 120

attribute vec3 position;
attribute vec4 myColor;
attribute vec2 myTexCoord;

varying vec4 color;
varying vec2 texCoord;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	color = myColor;
	texCoord = myTexCoord;
}