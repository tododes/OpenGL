#pragma once
#include "Color.h"
#include "glm.hpp"

using namespace glm;

class Vertex
{
public:
	Color color;
	vec3 position;
	Vertex();
	Vertex(vec3& pos, Color& col);
	~Vertex();
};

