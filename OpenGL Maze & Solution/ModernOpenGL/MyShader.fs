#version 120
varying vec4 color;
varying vec2 texCoord;
uniform sampler2D diffuse;
uniform float time;

void main()
{
	gl_FragColor = vec4(color.r * 2 * cos(time), 
						color.g * sin(time) , 
						color.b * -1 * cos(time), 
						color.a);
}
