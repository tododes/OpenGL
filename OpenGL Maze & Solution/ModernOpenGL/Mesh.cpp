#include "Mesh.h"
#include <vector>

using namespace std;

Mesh::Mesh(vec3 pos, vec3 size, const string& textureName, const string& shaderPath, int x, int y)
{
	Vertex vertices[] =
	{
		Vertex(vec3(pos.x - size.x, pos.y - size.y, 0), Color(1, 0, 0, 1), vec2(pos.x - size.x, pos.y - size.y)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, 0), Color(0, 1, 0, 1), vec2(pos.x - size.x, pos.y + size.y)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, 0), Color(0, 0, 1, 1), vec2(pos.x + size.x, pos.y - size.y)),
		Vertex(vec3(pos.x + size.x, pos.y + size.y, 0), Color(1, 0, 0, 1), vec2(pos.x + size.x, pos.y + size.y)),
		Vertex(vec3(pos.x - size.x, pos.y + size.y, 0), Color(0, 1, 0, 1), vec2(pos.x - size.x, pos.y + size.y)),
		Vertex(vec3(pos.x + size.x, pos.y - size.y, 0), Color(0, 0, 1, 1), vec2(pos.x + size.x, pos.y - size.y))
	};

	X = x;
	Y = y;
	name = "Name ";
	name += X;
	name += " ";
	name += Y;
	Cost = 9999.0f;
	brightness = 0.0f;
	
	glsl = new GLSL(shaderPath);
	drawCount = sizeof(vertices) / sizeof(vertices[0]);

	vector<vec3> positions;
	vector<Color> colors;
	vector<vec2> texCoords;

	for (int i = 0; i < drawCount; i++)
	{
		positions.push_back(vertices[i].position);
		colors.push_back(vertices[i].color);
		texCoords.push_back(vertices[i].texCoord);
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, drawCount * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, drawCount * sizeof(colors[0]), &colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, drawCount * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	texture = new Texture(textureName);
	transform = new Transform();
	
	NotWall = false;
	Visited = false;
}

Mesh::Mesh(Vertex* vertices, int numVertices, const string& textureName, const string& shaderPath)
{
	glsl = new GLSL(shaderPath);
	drawCount = numVertices;

	vector<vec3> positions;
	vector<Color> colors;
	vector<vec2> texCoords;

	for (int i = 0; i < drawCount; i++)
	{
		positions.push_back(vertices[i].position);
		colors.push_back(vertices[i].color);
		texCoords.push_back(vertices[i].texCoord);
	}

	glGenVertexArrays(1, &vao); 
	glBindVertexArray(vao);

	glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, drawCount * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, drawCount * sizeof(colors[0]), &colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, drawCount * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	texture = new Texture(textureName);
	transform = new Transform();
	
	Visited = false;
}

Mesh::Mesh()
{

}

void Mesh::AddNeighbour(Mesh* n)
{
	neighbours.push_back(n);
}

void Mesh::AddConnector(Mesh* c)
{
	connectors.push_back(c);
}

Mesh::~Mesh()
{
	if (glsl)
		delete glsl;
	if (texture)
		delete texture;
	if (transform)
		delete transform;
}

void Mesh::Translate(vec3& t)
{
	transform->getPos().x += t.x;
	transform->getPos().y += t.y;
	transform->getPos().z += t.z;
}

void Mesh::SetPosition(vec3& t)
{
	transform->getPos().x = t.x;
	transform->getPos().y = t.y;
	transform->getPos().z = t.z;
}

void Mesh::Update()
{

}

void Mesh::Draw(Camera& c)
{
	if (this->Active)
	{
		glsl->use();
		glsl->update(*transform, c);
		texture->Bind(0);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, drawCount);
		glBindVertexArray(0);
		
	}

}

void Mesh::ReloadTexture(const string& fileName)
{
	texture->DestroyTexture();
	texture->LoadTexture(fileName);
}

void Mesh::ReloadShader(const string& fileName)
{
	glsl->DestroyShader();
	glsl->InitShader(fileName);
}

void Mesh::BindBrightness()
{
	glsl->BindBrightness(brightness);
}
