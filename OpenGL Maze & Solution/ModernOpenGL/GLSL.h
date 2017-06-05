#pragma once
#include "glew.h"
#include "Transform.h"
#include <string>
#include "Camera.h"
using namespace std;

class GLSL
{
private:
	GLuint ID;
	GLuint shaderID[2];
	GLint attributeCounter;
public:
	GLuint CompileShader(const string& text, GLenum type);
	GLuint uniformID[1];
	string LoadShader(const string& fileName);
	void AddAttribute(const string& name);
	void InitShader(const string& fileName);
	void DestroyShader();
	void use();
	void update(Transform& transform, Camera& camera);
	void BindBrightness(float brightness);
	GLuint getUniform(const string& name);
	GLSL();
	GLSL(const string& fileName);
	~GLSL();
};

