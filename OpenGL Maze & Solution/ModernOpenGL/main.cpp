#include <stdio.h>
#include "Window.h"
#include "SDL.h"
#include "GLSL.h"
#include "Mesh.h"
#include "Texture.h"
#include <math.h>
#include <fstream>
#include "GameObject.h"
#include "Time.h"
#include "GameWorld.h"
#include <vector>
#include "Cube.h"
#include "Camera.h"
#include <thread>
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

using namespace std;

int indexOf(Mesh* m, vector<Mesh*>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i]->X == m->X && vec[i]->Y == m->Y)
		{
			return i;
		}
	}
	return -1;
}

void Delete(Mesh* m, vector<Mesh*>& vec)
{
	int index = 0;
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i]->X == m->X && vec[i]->Y == m->Y)
		{
			index = i;
			break;
		}
	}

	Mesh* temp = vec[index];
	vec[index] = vec[vec.size() - 1];
	vec[vec.size() - 1] = temp;

	vec.pop_back();
}

float getDistance(Mesh* a, Mesh* b)
{
	float r = pow((b->X - a->X), 2) + pow((b->Y - a->Y), 2);
	return sqrt(r);
}

vector<Mesh*> RetrievePath(Mesh* Initial, Mesh* End)
{
	Mesh* current = End;
	vector<Mesh*> meshes;
	while (current != Initial)
	{
		meshes.push_back(current);
		current = current->pathParent;
	}
	meshes.push_back(Initial);
	return meshes;
}

vector<Mesh*> GetSolutionPath(Mesh* Initial, Mesh* End, vector<Mesh*> &ms)
{
	vector<Mesh*> path;
	Mesh* current = Initial;
	current->Cost = 0.0f;
	while (current != End)
	{
		for (int i = 0; i < current->neighbours.size(); i++)
		{
			if (current->neighbours[i]->NotWall && current->neighbours[i]->Cost < 10000.0f)
			{
				//count distance
				current->neighbours[i]->Cost = current->Cost + getDistance(current, current->neighbours[i]);
				current->neighbours[i]->pathParent = current;
			}
		}
		current->Cost = 10000.0f;

		for (int i = 0; i < ms.size(); i++)
		{
			if (ms[i]->Cost < current->Cost)
				current = ms[i];
		}
		
	}
	path = RetrievePath(Initial, End);
	return path;
}

vector<Mesh*> GenerateMaze(Mesh* Initial, vector<Mesh*>& frontiers)
{
	vector<Mesh*> meshes;
	Mesh* current = Initial;
	frontiers.push_back(current);
	while (frontiers.size() > 0)
	{
		current->Visited = true;
		cout << current->X << " " << current->Y << endl;
		
		for (int i = 0; i < current->connectors.size(); i++)
		{
			if (indexOf(current->connectors[i], frontiers) == -1 && !current->connectors[i]->Visited)
			{
				current->connectors[i]->parent = current;
				frontiers.push_back(current->connectors[i]);
			}
		}

		Delete(current, frontiers);
		if (frontiers.size() > 0)
		{
			srand(time(NULL));
			int rnd = rand() % (frontiers.size()) + 0;
			current = frontiers[rnd];
			meshes.push_back(current->parent->neighbours[indexOf(current, current->parent->connectors)]);
		}
	}
	return meshes;
}


//struct FloorNode
//{
//	Cube floor;
//	FloorNode* next;
//	FloorNode* prev;
//
//	FloorNode() {}
//	FloorNode(Cube& c) { floor = c; }
//};
//
//struct FloorManager
//{
//	FloorNode* curr;
//	FloorNode* head;
//	FloorNode* tail;
//
//	FloorManager(){ curr = head = tail = NULL; }
//
//	void Push(FloorNode* f)
//	{
//		curr = f;
//		tail->next = curr;
//		curr->prev = tail;
//		curr->next = NULL;
//		tail = curr;
//	}
//
//	void Pop()
//	{
//		FloorNode* temp = head;
//		head = head->next;
//		head->prev = NULL;
//		temp->next = NULL;
//		delete temp;
//		temp = NULL;
//	}
//
//	void PopAll()
//	{
//		while (tail->prev != NULL)
//		{
//			Pop();
//		}
//		delete tail;
//		tail = NULL;
//
//		if (curr != NULL) { delete curr; curr = NULL; }
//		if (head != NULL) { delete head; head = NULL; }
//	}
//};

int main(int argc, char** args)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	GameWorld& world = GameWorld::singleton();
	Window window(1024, 768, "Game");
	vector<Mesh*> meshes;
	vector<Mesh*> NonWallMeshes;
	vector<Mesh*> solutionPaths;
	const int X = 17;
	const int Y = 17;
	Mesh* cubes[X][Y];
	Camera camera(vec3(0, 0, -0.2f), 60.0f, 1024/768, 0.01f, 1000.0f, vec3(0, 0, 1));

	int brightnessIndex = 0;

	//Mesh playerSprite(vec3(0, 0, 0), vec3(0.1, 0.1, 1), "SP2.png", "GLSL", 0, 0);

	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			cubes[i][j] = new Mesh(vec3(0.125f * (i - 9), 0.125f * (j - 9), 1), vec3(0.0625f, 0.0625f, 0.0625f), "Sand.jpg", "GLSL", i, j);
			if (i % 2 != 0 && j % 2 != 0)
			{
				cubes[i][j]->ReloadTexture("Wall Texture.jpg");
				cubes[i][j]->ReloadShader("ColorOverTime");
				cubes[i][j]->NotWall = true;
				NonWallMeshes.push_back(cubes[i][j]);
			}
			printf("Init");
		}
	}

	for (int i = 1; i < X; i++)
	{
		for (int j = 1; j < Y; j++)
		{
			for (int k = i - 1; k <= i + 1; k++)
			{
				for (int l = j - 1; l <= j + 1; l++)
				{
					if (k >= 1 && k < X-1 && l >= 1 && l < Y-1 && !(i == k && j == l) && !(i != k && j != l))
						cubes[i][j]->AddNeighbour(cubes[k][l]);
				}
			}
		}
	}

	for (int i = 1; i < X; i += 2)
	{
		for (int j = 1; j < Y; j += 2)
		{
			for (int k = i - 2; k <= i + 2; k += 2)
			{
				for (int l = j - 2; l <= j + 2; l += 2)
				{
					if (k >= 1 && k < X-1 && l >= 1 && l < Y-1 && !(i == k && j == l) && !(i != k && j != l))
						cubes[i][j]->AddConnector(cubes[k][l]);
				}
			}
		}
	}

	vector<Mesh*> meshToBeDestroyed = GenerateMaze(cubes[1][1], meshes);
	int ctr = 0;

	while (window.isRunning())
	{
		window.clear(0, 0, 0, 1);
		Time::Tick();

		for (int i = 0; i < X; i++)
		{
			for (int j = 0; j < Y; j++)
			{
				cubes[i][j]->Update();
				cubes[i][j]->Draw(camera);
			}
		}

		if (ctr <= meshToBeDestroyed.size() - 1)
		{
			if (indexOf(meshToBeDestroyed[ctr], NonWallMeshes) == -1)
				NonWallMeshes.push_back(meshToBeDestroyed[ctr]);
			meshToBeDestroyed[ctr]->NotWall = true;
			meshToBeDestroyed[ctr]->ReloadTexture("Wall Texture.jpg");
			meshToBeDestroyed[ctr]->ReloadShader("ColorOverTime");
			ctr++;
		}
		else if (ctr == meshToBeDestroyed.size())
		{
			solutionPaths = GetSolutionPath(cubes[1][1], cubes[X-2][Y-2], NonWallMeshes);
			for (int i = 0; i < solutionPaths.size(); i++)
			{
				solutionPaths[i]->ReloadShader("pathShader");
			}
			ctr++;
		}
		else
		{
			for (int i = 0; i < solutionPaths.size(); i++)
			{
				if (i == brightnessIndex){
					solutionPaths[i]->brightness = 1;
				}
				else if (i == brightnessIndex - 1 || i == brightnessIndex + 1){
					solutionPaths[i]->brightness = 0.75f;
				}
				else if (i == brightnessIndex - 2 || i == brightnessIndex + 2){
					solutionPaths[i]->brightness = 0.5f;
				}
				else{
					solutionPaths[i]->brightness = 0.25f;
				}
				solutionPaths[i]->Update();
				solutionPaths[i]->BindBrightness();
				solutionPaths[i]->Draw(camera);
			}
			brightnessIndex++;
			if (brightnessIndex >= solutionPaths.size())
				brightnessIndex = 0;
		}

		window.update();
		this_thread::sleep_for(chrono::milliseconds(70));
	}

	world.DestroyInstance();
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			if (cubes[i][j])
			{
				delete cubes[i][j];
				cubes[i][j] = NULL;
			}
		}
	}
	return 0;
} 