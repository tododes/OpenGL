#pragma once
#include "glm.hpp"
#include <string>
#include "Mesh.h"
#include "GameObject.h"
#include <vector>
#include <iostream>
#include <math.h>
#include "Time.h"
#include "Camera.h"

using namespace glm;
using namespace std;

class Cube
{
private:

public:
	bool Active;
	Cube();
	Cube(vec3 pos, vec3 size, const string& textureName, const string& shaderName, float gravityScale);
	vec3 position;
	vec3 size;
	GameObject* objects[6];
	bool CollideWith(Camera& c);
	void Update();
	void Draw(Camera& c);
	~Cube();
};

