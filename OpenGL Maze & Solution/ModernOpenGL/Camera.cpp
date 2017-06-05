#include "Camera.h"

Camera::Camera() 
{

}

Camera::Camera(vec3& pos, float fov, float aspect, float zNear, float zFar, vec3& l)
{
	cameraPerspective = perspective(fov, aspect, zNear, zFar);
	position = pos;
	look = l;
}

mat4 Camera::getProjectionView()
{
	return cameraPerspective * lookAt(position, position + look, vec3(0, 1, 0));
}

void Camera::Translate(vec3& v)
{
	position += v;
}

Camera::~Camera()
{

}
