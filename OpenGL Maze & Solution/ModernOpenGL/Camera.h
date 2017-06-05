#pragma once
#include "gtx\transform.hpp"
#include "glm.hpp"

using namespace glm;

class Camera
{
private:
	mat4 cameraPerspective;
	
public:
	vec3 position;
	vec3 look;

	Camera();
	Camera(vec3& pos, float fov, float aspect, float zNear, float zFar, vec3& l = vec3(0, 0, 1));
	void Translate(vec3& v);
	mat4 getProjectionView();
	~Camera();
};

