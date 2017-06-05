#pragma once
#include "Mesh.h"
#include "Camera.h"

class GameObject : public Mesh
{
public:
	bool Active;
	float gravityScale;
	void Update();
	void Draw(Camera& camera) override;
	GameObject();
	GameObject(vec3 pos, vec3 size, const string& textureName, const string& shaderPath, float _gravityScale);
	GameObject(Vertex* vertices, int numVertices, const string& textureName, const string& shaderPath, float _gravityScale);
	~GameObject();
};

