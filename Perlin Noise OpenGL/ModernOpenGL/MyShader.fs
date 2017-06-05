#version 120
varying vec4 color;
varying vec2 texCoord;
uniform sampler2D diffuse;
uniform float time;

void main()
{
	gl_FragColor = color;
}
