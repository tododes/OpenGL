#version 120

varying vec4 color;
varying vec2 texCoord;
uniform float time;
uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord) * vec4(color.r + sin(time * 8), color.g - sin(time * 8), color.b + cos(time * 8), color.a);
}