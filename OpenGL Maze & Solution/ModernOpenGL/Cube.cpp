#include "Cube.h"

Cube::Cube()
{

}

Cube::Cube(vec3 pos, vec3 size, const string& textureName, const string& shaderName, float gravityScale)
{

	Vertex vertices[] = {
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z + size.z), Color(1, 0, 0, 1), vec2(pos.x - size.x, pos.y - size.y)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z + size.z), Color(1, 0, 0, 1), vec2(pos.x + size.x, pos.y - size.y)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z + size.z), Color(1, 0, 0, 1), vec2(pos.x - size.x, pos.y + size.y)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z + size.z), Color(1, 0, 0, 1), vec2(pos.x + size.x, pos.y + size.y)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z + size.z), Color(1, 0, 0, 1), vec2(pos.x - size.x, pos.y + size.y)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z + size.z), Color(1, 0, 0, 1), vec2(pos.x + size.x, pos.y - size.y))
	};//front

	Vertex vertices2[] = {
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z - size.z), Color(1, 0, 0, 1), vec2(pos.x - size.x, pos.y - size.y)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z - size.z), Color(1, 0, 0, 1), vec2(pos.x + size.x, pos.y - size.y)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z - size.z), Color(1, 0, 0, 1), vec2(pos.x - size.x, pos.y + size.y)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z - size.z), Color(1, 0, 0, 1), vec2(pos.x + size.x, pos.y + size.y)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z - size.z), Color(1, 0, 0, 1), vec2(pos.x - size.x, pos.y + size.y)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z - size.z), Color(1, 0, 0, 1), vec2(pos.x + size.x, pos.y - size.y))
	};//back

	Vertex vertices3[] = {
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z - size.z), Color(1, 0, 0, 1), vec2(pos.x - size.x, pos.y - size.y)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z - size.z), Color(1, 0, 0, 1), vec2(pos.x + size.x, pos.y - size.y)),
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z + size.z), Color(1, 0, 0, 1), vec2(pos.x - size.x, pos.y + size.y)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z + size.z), Color(1, 0, 0, 1), vec2(pos.x + size.x, pos.y + size.y)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z - size.z), Color(1, 0, 0, 1), vec2(pos.x - size.x, pos.y + size.y)),
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z + size.z), Color(1, 0, 0, 1), vec2(pos.x + size.x, pos.y - size.y))
	};//left

	Vertex vertices4[] = {
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z - size.z), Color(1, 0, 0, 1), vec2(pos.x - size.x, pos.y - size.y)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z - size.z), Color(1, 0, 0, 1), vec2(pos.x + size.x, pos.y - size.y)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z + size.z), Color(1, 0, 0, 1), vec2(pos.x - size.x, pos.y + size.y)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z + size.z), Color(1, 0, 0, 1), vec2(pos.x + size.x, pos.y + size.y)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z - size.z), Color(1, 0, 0, 1), vec2(pos.x - size.x, pos.y + size.y)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z + size.z), Color(1, 0, 0, 1), vec2(pos.x + size.x, pos.y - size.y))
	};//right

	Vertex vertices5[] = {
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z - size.z), Color(1, 0, 1, 1), vec2(0, 0)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z - size.z), Color(1, 0, 1, 1), vec2(0, 0.5f)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z + size.z), Color(1, 0, 1, 1), vec2(0.5f, 0.5f)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z - size.z), Color(1, 0, 1, 1), vec2(0, 0)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z + size.z), Color(1, 0, 1, 1), vec2(0.5f, 0)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z + size.z), Color(1, 0, 1, 1), vec2(0.5f, 0.5f))
	};//up

	Vertex vertices6[] = {
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z - size.z), Color(1, 0, 1, 1), vec2(0, 0)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z - size.z), Color(1, 0, 1, 1), vec2(0, 0.5f)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z + size.z), Color(1, 0, 1, 1), vec2(0.5f, 0.5f)),
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z - size.z), Color(1, 0, 1, 1), vec2(0, 0)),
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z + size.z), Color(1, 0, 1, 1), vec2(0.5f, 0)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z + size.z), Color(1, 0, 1, 1), vec2(0.5f, 0.5f))
	};//down

	objects[0] = new GameObject(vertices, sizeof(vertices) / sizeof(vertices[0]), textureName, shaderName, 0.0f);
	objects[1] = new GameObject(vertices2, sizeof(vertices2) / sizeof(vertices2[0]), textureName, shaderName, 0.0f);
	objects[2] = new GameObject(vertices3, sizeof(vertices3) / sizeof(vertices3[0]), textureName, shaderName, 0.0f);
	objects[3] = new GameObject(vertices4, sizeof(vertices4) / sizeof(vertices4[0]), textureName, shaderName, 0.0f);
	objects[4] = new GameObject(vertices5, sizeof(vertices5) / sizeof(vertices5[0]), textureName, shaderName, 0.0f);
	objects[5] = new GameObject(vertices6, sizeof(vertices6) / sizeof(vertices6[0]), textureName, shaderName, 0.0f);
	Active = true;

	this->position = pos;
	this->size = size;
}

void Cube::Update()
{
	if (Active)
	{
		for (int i = 0; i < 6; i++)
		{
			objects[i]->Update();
			//objects[i]->transform->getPos().y += 0.1f * Time::deltaTime;
			/*objects[i]->transform->getRot().x += 0.1f * Time::deltaTime;
			objects[i]->transform->getRot().z += 0.1f * Time::deltaTime;*/
		}
	}
	
}

bool Cube::CollideWith(Camera& camera)
{
	if (camera.position.x >= position.x - size.x || camera.position.x <= position.x + size.x)
	{
		if (camera.position.y >= position.y - size.y || camera.position.y <= position.y + size.y)
		{
			if (camera.position.z >= position.z - size.z || camera.position.z <= position.z + size.z)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

void Cube::Draw(Camera& c)
{
	if (Active)
	{
		for (int i = 0; i < 6; i++)
		{
			objects[i]->Draw(c);
		}
	}
}


Cube::~Cube()
{
	for (int i = 0; i < 6; i++)
	{
		if (objects[i] != NULL)
		{
			delete objects[i];
			objects[i] = NULL;
		}
		
	}
}
