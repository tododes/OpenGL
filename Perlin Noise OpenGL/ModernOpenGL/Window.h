#pragma once
#include "SDL.h"
#include "glew.h"


class Window
{
private: 
	static Window* instance;
	SDL_Window* window;
	SDL_GLContext context;
	SDL_Event event;
	Window(int w, int h);

public:
	bool Running;
	static Window& getInstance();
	static void destroyInstance();
	void Clear();
	void PollEvents();
	void Update();
	~Window();
};

