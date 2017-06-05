#version 120
attribute vec3 position;
attribute vec2 myTexCoord;
attribute vec4 myColor;
varying vec2 texCoord;
varying vec4 color;
uniform mat4 transform;
void main()
{
	gl_Position = transform * vec4(position, 1.0);
	color = myColor;
	texCoord = myTexCoord;

}
