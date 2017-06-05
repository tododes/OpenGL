#include "Mesh.h"
#include <vector>

using namespace std;

Mesh::Mesh()
{

}

Mesh::Mesh(vec3& pos, vec3& size, const string& shaderName)
{
	glsl = new GLSL(shaderName);
	transform = new Transform();
	Vertex vertices[6] =
	{
		Vertex(vec3(pos.x - size.x / 2.0f, pos.y - size.y / 2.0f, 0), Color(0, 1, 0, 1)),
		Vertex(vec3(pos.x - size.x / 2.0f, pos.y + size.y / 2.0f, 0), Color(0, 1, 0, 1)),
		Vertex(vec3(pos.x + size.x / 2.0f, pos.y - size.y / 2.0f, 0), Color(0, 1, 0, 1)),
		Vertex(vec3(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f, 0), Color(0, 1, 0, 1)),
		Vertex(vec3(pos.x - size.x / 2.0f, pos.y + size.y / 2.0f, 0), Color(0, 1, 0, 1)),
		Vertex(vec3(pos.x + size.x / 2.0f, pos.y - size.y / 2.0f, 0), Color(0, 1, 0, 1))
	};
	cout << vertices[0].position.x << " " << vertices[0].position.y << endl;
	count = sizeof(vertices) / sizeof(vertices[0]);

	vector<vec3> positions;
	vector<Color> colors;
	for (int i = 0; i < count; i++)
	{
		positions.push_back(vertices[i].position);
		colors.push_back(vertices[i].color);
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(colors[0]), &colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

Mesh::Mesh(Vertex* vertices, int ctr, const string& shaderName)
{
	glsl = new GLSL(shaderName);
	transform = new Transform();

	count = ctr;

	vector<vec3> positions;
	vector<Color> colors;

	for (int i = 0; i < count; i++)
	{
		positions.push_back(vertices[i].position);
		colors.push_back(vertices[i].color);
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(colors[0]), &colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);

}

void Mesh::ChangeColor(Color& c)
{
	vector<Color> colors;
	for (int i = 0; i < 6; i++)
	{
		colors.push_back(c);
	}

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(colors[0]), &colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void Mesh::Draw()
{
	glsl->use();
	glsl->update(*transform);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, count);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	if (glsl){
		delete glsl;
		glsl = NULL;
	}

	if (transform){
		delete transform;
		transform = NULL;
	}
}
