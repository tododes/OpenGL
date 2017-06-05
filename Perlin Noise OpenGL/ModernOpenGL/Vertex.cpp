#include "Vertex.h"


Vertex::Vertex()
{
}

Vertex::Vertex(vec3& pos, Color& col)
{
	position = pos;
	color = col;
}


Vertex::~Vertex()
{
}
