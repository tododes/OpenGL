#include "GLSL.h"
#include <fstream>
#include <iostream>
#include "Time.h"

using namespace std;

GLSL::GLSL(const string& fileName)
{
	InitShader(fileName);
}

void GLSL::AddAttribute(const string& name)
{
	glBindAttribLocation(ID, attributeCounter++, name.c_str());
}

GLuint GLSL::CompileShader(const string& text, GLenum type)
{
	GLuint shader = glCreateShader(type);
	const GLchar* source[1];
	GLint sourceLengths[1];

	source[0] = text.c_str();
	sourceLengths[0] = text.length();

	glShaderSource(shader, 1, source, sourceLengths);
	glCompileShader(shader);

	return shader;
}

GLuint GLSL::getUniform(const string& name)
{
	return glGetUniformLocation(ID, name.c_str());
}

void GLSL::update(Transform& transform, Camera& camera)
{
	mat4 model = camera.getProjectionView() * transform.GetModel();
	glUniformMatrix4fv(uniformID[0], 1, GL_FALSE, &model[0][0]);
	GLuint timeUniform = glGetUniformLocation(ID, "time");
	glUniform1f(timeUniform, Time::time);
}

void GLSL::use()
{
	glUseProgram(ID);
}

void GLSL::BindBrightness(float brightness)
{
	GLuint brightnessUniform = glGetUniformLocation(ID, "brightness");
	glUniform1f(brightnessUniform, brightness);
}

void GLSL::InitShader(const string& fileName)
{
	attributeCounter = 0;
	ID = glCreateProgram();
	shaderID[0] = CompileShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	shaderID[1] = CompileShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);
	for (int i = 0; i < 2; i++)
	{
		glAttachShader(ID, shaderID[i]);
	}
	AddAttribute("position");
	AddAttribute("myColor");
	AddAttribute("myTexCoord");
	glLinkProgram(ID);
	glValidateProgram(ID);

	uniformID[0] = glGetUniformLocation(ID, "transform");
}

string GLSL::LoadShader(const string& fileName)
{
	ifstream file;
	file.open(fileName);

	string line, output;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		ofstream ofile;
		ofile.open(fileName);
		if (fileName.find(".vs") != string::npos)
		{
			ofile << "#version 120" << endl;
			ofile << "attribute vec3 position;" << endl;
			ofile << "attribute vec2 myTexCoord;" << endl;
			ofile << "varying vec2 texCoord;" << endl;
			ofile << "uniform mat4 transform;" << endl;
			ofile << "void main()" << endl;
			ofile << "{" << endl;
			ofile << "	gl_Position = transform * vec4(position, 1.0);" << endl;
			ofile << "	texCoord = myTexCoord;" << endl;
			ofile << "}" << endl;
		}
		else if (fileName.find(".fs") != string::npos)
		{
			ofile << "#version 120" << endl;
			ofile << "varying vec2 texCoord;" << endl;
			ofile << "uniform sampler2D diffuse;" << endl;
			ofile << "void main()" << endl;
			ofile << "{" << endl;
			ofile << "	gl_FragColor = texture2D(diffuse, texCoord);" << endl;
			ofile << "}" << endl;
		}
		ifstream file;
		file.open(fileName);

		string line, output;

		if (file.is_open())
		{
			while (file.good())
			{
				getline(file, line);
				output.append(line + "\n");
			}
		}
		return output;
	}
	return output;
}

GLSL::~GLSL()
{
	DestroyShader();
}

void GLSL::DestroyShader()
{
	for (int i = 0; i < 2; i++)
	{
		glDetachShader(ID, shaderID[i]);
		glDeleteShader(shaderID[i]);
	}
	glDeleteProgram(ID);
}
