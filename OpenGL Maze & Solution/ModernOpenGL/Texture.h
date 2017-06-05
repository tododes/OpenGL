#pragma once
#include "glew.h"
#include <string>

using namespace std;

class Texture
{
private:
	GLuint ID;
public:
	Texture();
	Texture(const string& fileName);
	~Texture();
	void LoadTexture(const string& fileName);
	void DestroyTexture();
	void Bind(int unit);
};

