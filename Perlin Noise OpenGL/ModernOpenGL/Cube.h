#pragma once
#include "Mesh.h"
#include "Vertex.h"
#include "glm.hpp"
#include "GLSL.h"
#include "Transform.h"
#include <vector>

using namespace std;

class Cube
{
private:
	Mesh* mesh[6];

public:
	Transform* transform;
	void Draw();
	Cube(vec3& pos, vec3& size, const string& shaderName);
	~Cube();
};

