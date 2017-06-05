#include "Cube.h"


Cube::Cube(vec3& pos, vec3& size, const string& shaderName)
{
	Vertex vertices1[] = 
	{
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z + size.z), Color(1, 0, 0, 1)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z + size.z), Color(1, 0, 0, 1)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z + size.z), Color(1, 0, 0, 1)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z + size.z), Color(1, 0, 0, 1)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z + size.z), Color(1, 0, 0, 1)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z + size.z), Color(1, 0, 0, 1))
	};

	Vertex vertices2[] =
	{
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z - size.z), Color(1, 1, 0, 1)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z - size.z), Color(1, 1, 0, 1)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z - size.z), Color(1, 1, 0, 1)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z - size.z), Color(1, 1, 0, 1)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z - size.z), Color(1, 1, 0, 1)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z - size.z), Color(1, 1, 0, 1))
	};

	Vertex vertices3[] =
	{
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z - size.z), Color(1, 0, 1, 1)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z - size.z), Color(1, 0, 1, 1)),
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z + size.z), Color(1, 0, 1, 1)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z + size.z), Color(1, 0, 1, 1)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z - size.z), Color(1, 0, 1, 1)),
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z + size.z), Color(1, 0, 1, 1))
	};

	Vertex vertices4[] =
	{
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z - size.z), Color(0, 0, 0, 1)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z - size.z), Color(0, 0, 0, 1)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z + size.z), Color(0, 0, 0, 1)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z + size.z), Color(0, 0, 0, 1)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z - size.z), Color(0, 0, 0, 1)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z + size.z), Color(0, 0, 0, 1))
	};

	Vertex vertices5[] =
	{
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z - size.z), Color(0, 0, 1, 1)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z - size.z), Color(0, 0, 1, 1)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z + size.z), Color(0, 0, 1, 1)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z - size.z), Color(0, 0, 1, 1)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, pos.z + size.z), Color(0, 0, 1, 1)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, pos.z + size.z), Color(0, 0, 1, 1))
	};

	Vertex vertices6[] =
	{
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z - size.z), Color(0, 1, 1, 1)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z - size.z), Color(0, 1, 1, 1)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z + size.z), Color(0, 1, 1, 1)),
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z - size.z), Color(0, 1, 1, 1)),
		Vertex(vec3(pos.x - size.x, pos.y - size.y, pos.z + size.z), Color(0, 1, 1, 1)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, pos.z + size.z), Color(0, 1, 1, 1))
	};


	mesh[0] = new Mesh(vertices1, sizeof(vertices1) / sizeof(vertices1[0]), shaderName);
	mesh[1] = new Mesh(vertices2, sizeof(vertices2) / sizeof(vertices2[0]), shaderName);
	mesh[2] = new Mesh(vertices3, sizeof(vertices3) / sizeof(vertices3[0]), shaderName);
	mesh[3] = new Mesh(vertices4, sizeof(vertices4) / sizeof(vertices4[0]), shaderName);
	mesh[4] = new Mesh(vertices5, sizeof(vertices5) / sizeof(vertices5[0]), shaderName);
	mesh[5] = new Mesh(vertices6, sizeof(vertices6) / sizeof(vertices6[0]), shaderName);
	
	transform = new Transform();

}

void Cube::Draw()
{
	for (int i = 0; i < 6; i++)
	{
		mesh[i]->Draw();
	}
}


Cube::~Cube()
{
	for (int i = 0; i < 6; i++)
	{
		if (mesh[i])
		{
			delete mesh[i];
			mesh[i] = NULL;
		}
	}

	if (transform)
	{
		delete transform;
		transform = NULL;
	}
}
