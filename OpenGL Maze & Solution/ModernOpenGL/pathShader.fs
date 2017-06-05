#version 120

varying vec2 texCoord;
varying vec4 color;

uniform sampler2D diffuse;
uniform float time;
uniform float brightness;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord) * vec4(brightness, brightness, 0, color.a);
}