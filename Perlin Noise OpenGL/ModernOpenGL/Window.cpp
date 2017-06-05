#include "Window.h"

Window* Window::instance = NULL;

Window::Window(int w, int h)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow("Perlin Noise", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);

	GLenum status = glewInit();
	Running = true;
}

void Window::Clear()
{
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update()
{
	SDL_GL_SwapWindow(window);
	
}

void Window::PollEvents()
{
	if (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			Running = false;
		}

	}
}

Window& Window::getInstance()
{
	if (!instance)
		instance = new Window(1280, 768);
	return *instance;
}

void Window::destroyInstance()
{
	Window* w = &getInstance();
	delete w;
}

Window::~Window()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}
