#pragma once
#include "gtx\transform.hpp"
#include "glm.hpp"

using namespace glm;

class Transform
{
private:
	vec3 pos;
	vec3 rot;
	vec3 size;
public:
	Transform()
	{
		size = vec3(1, 1, 1);
	}
	inline mat4 GetModel()
	{
		mat4 posMat = translate(pos);
		mat4 rotX = rotate(rot.x, vec3(1, 0, 0));
		mat4 rotY = rotate(rot.y, vec3(0, 1, 0));
		mat4 rotZ = rotate(rot.z, vec3(0, 0, 1));
		mat4 rotMat = rotZ * rotY * rotX;
		mat4 scaleMat = scale(size);
		return posMat * rotMat * scaleMat;
	}

	inline vec3& getPos(){ return pos; }
	inline vec3& getRot(){ return rot; }
};
