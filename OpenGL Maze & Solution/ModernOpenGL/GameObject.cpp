#include "GameObject.h"
#include "GameWorld.h"
#include "Time.h"

GameObject::GameObject()
{

}

GameObject::GameObject(vec3 pos, vec3 size, const string& textureName, const string& shaderPath, float _gravityScale) : Mesh(pos, size, textureName, shaderPath, 0, 0)
{
	Active = true;
	gravityScale = _gravityScale;
}

GameObject::GameObject(Vertex* vertices, int numVertices, const string& textureName, const string& shaderPath, float _gravityScale) : Mesh(vertices, numVertices, textureName, shaderPath)
{
	Active = true;
	gravityScale = _gravityScale;
}

void GameObject::Update()
{
	transform->getPos().y -= GameWorld::singleton().gravity * Time::deltaTime * gravityScale;
}

void GameObject::Draw(Camera& camera)
{
	if (Active)
	{
		glsl->use();
		glsl->update(*transform, camera);
		texture->Bind(0);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, drawCount);
		glBindVertexArray(0);
	}
}


GameObject::~GameObject()
{
}
