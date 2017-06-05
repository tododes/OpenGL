#pragma once
#include "glm.hpp"
#include "glew.h"
#include <stdio.h>
#include "GLSL.h"
#include "Transform.h"
#include "Texture.h"
#include "Camera.h"
#include <vector>
#include <string>

using namespace glm;
using namespace std;

class Color
{
public:
	float r, g, b, a;
	Color(){}
	Color(float r, float g, float b, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};

class Vertex
{
public:
	vec3 position;
	Color color;
	vec2 texCoord;
	Vertex(){ color = Color(0, 0, 0, 1); }
	Vertex(vec3 p, Color c)
	{
		position = p;
		color = c;
	}
	Vertex(vec3 p, Color c, vec2 t)
	{
		position = p;
		color = c;
		texCoord = t;
	}
};

class Mesh
{
protected:
	int drawCount;
	GLuint vao;
	GLuint vbo[2];
	GLSL* glsl;
	Texture* texture;
public:
	string name;
	Transform* transform;
	int X, Y;
	bool Active;

public:
	Mesh();
	vector<Mesh*> neighbours;
	vector<Mesh*> connectors;
	Mesh* parent;
	Mesh* pathParent;
	bool Visited;
	bool NotWall;
	float Cost;
	float brightness;

	void ReloadTexture(const string& fileName);
	void BindBrightness();
	void ReloadShader(const string& fileName);
	void AddNeighbour(Mesh* n);
	void AddConnector(Mesh* c);

	Mesh(vec3 pos, vec3 size, const string& textureName, const string& shaderPath, int x, int y);
	Mesh(Vertex* vertices, int numVertices, const string& textureName, const string& shaderPath);
	virtual ~Mesh();
	void Translate(vec3& t);
	void SetPosition(vec3& t);
	void Update();
	virtual void Draw(Camera& c);
	
};

