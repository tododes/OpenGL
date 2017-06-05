#include <stdio.h>
#include <iostream>
#include "Window.h"
#include "GLSL.h"
#include "Mesh.h"
#include "Cube.h"
#include <time.h>
#include "PerlinNoise.h"
#include <vector>
#include "Color.h"
#include <Windows.h>
#include "Time.h"

using namespace std;

int main(int argc, char** argv)
{
	Window window = Window::getInstance();
	Time& t = Time::singleton();
	
	const int minX = 0;
	const int maxX = 21;
	const int minY = 0;
	const int maxY = 40;
	const int minZ = 0;
	const int maxZ = 21;

	const int field = maxX * maxY * maxZ;
	int columnHeight = 0;

	vector<Mesh*> meshes;
	vector<int> columnHeights;

	srand(time(NULL));
	PerlinNoise perlinNoise(rand() % 10000 + 1000);
	for (int i = minX; i < maxX; i++){
		for (int j = minZ; j < maxZ; j++){
			meshes.push_back(new Mesh(vec3((i * 0.1f) - 1.0f, (j * 0.1f) - 1.0f, 0), vec3(0.1f, 0.1f, 0.1f), "MyShader"));
			columnHeights.push_back(2 + perlinNoise.getNoise(i - minX, j - minZ, maxY - minY - 2));
		}
	}

	
	while (window.Running)
	{
		t.Tick();
		window.Clear();
		window.PollEvents();
		if (GetAsyncKeyState(VK_UP)){
			perlinNoise.ResetSeed(rand() % 10000 + 1000);
			columnHeights.clear();
			for (int i = minX; i < maxX; i++){
				for (int j = minZ; j < maxZ; j++){
					columnHeights.push_back(2 + perlinNoise.getNoise(i - minX, j - minZ, maxY - minY - 2));
				}
			}
		}

		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i]->ChangeColor(Color(0.0f, columnHeights[i] / 20.0f, 0.0f, 1));
			meshes[i]->Draw();
		}
		window.Update();
	}

	for (int i = 0; i < meshes.size(); i++)
	{
		delete meshes[i];
		meshes[i] = NULL;
	}

	Time::destroy();
	Window::destroyInstance();
	
	return 0;
}