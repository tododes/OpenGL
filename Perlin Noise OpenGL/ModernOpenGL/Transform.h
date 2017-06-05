#pragma once
#include "glm.hpp"
#include "gtx\transform.hpp"

using namespace glm;

class Transform
{
public:
	vec3 position;
	vec3 rotation;
	vec3 size;

	Transform(vec3& pos = vec3(0, 0, 0), vec3& rot = vec3(0, 0, 0), vec3& sz = vec3(1, 1, 1))
	{
		position = pos;
		rotation = rot;
		size = sz;
	}

	mat4 getModel()
	{
		mat4 PosMat = translate(position);
		mat4 RotMatX = rotate(rotation.x, vec3(1, 0, 0));
		mat4 RotMatY = rotate(rotation.y, vec3(0, 1, 0));
		mat4 RotMatZ = rotate(rotation.z, vec3(0, 0, 1));
		mat4 RotMat = RotMatZ * RotMatY * RotMatX;
		mat4 ScaleMat = scale(size);
		return PosMat * RotMat * ScaleMat;
	}
};