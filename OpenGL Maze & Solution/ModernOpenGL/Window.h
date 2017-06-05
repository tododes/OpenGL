#pragma once
#include <SDL.h>
#include <glew.h>
#include <string>
#include "Time.h"
#include "GameWorld.h"
#include "GameObject.h"
#include "glm.hpp"

using namespace glm;
using namespace std;

class Window
{
public:
	Window(int width, int height, const string& title);
	void update();
	void clear(float r, float g, float b, float a);
	bool isRunning();
	~Window();
private:
	SDL_Window* window;
	SDL_GLContext context;
	bool running;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
};

