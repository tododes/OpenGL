#include "Window.h"


Window::Window(int width, int height, const string& title)
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);

	GLenum status = glewInit();
	running = true;
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}

void Window::update()
{
	
	SDL_Event e;
	SDL_GL_SwapWindow(window);
	if (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			running = false;
	}
}

bool Window::isRunning()
{
	return running;
}

void Window::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Window::~Window()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
