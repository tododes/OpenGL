#pragma once
#include "glew.h"
#include "Color.h"
#include "Vertex.h"
#include "glm.hpp"
#include <iostream>
#include "GLSL.h"
#include "Transform.h"

using namespace std;
using namespace glm;
class Mesh
{
private:
	GLuint vao;
	GLuint vbo[2];
	GLSL* glsl;
	int count;
public:
	Transform* transform;
	void Draw();
	void ChangeColor(Color& c);
	Mesh();
	Mesh(vec3& pos, vec3& size, const string& shaderName);
	Mesh(Vertex* vertices, int ctr, const string& shaderName);
	~Mesh();
};

