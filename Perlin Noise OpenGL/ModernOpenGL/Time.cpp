#include "Time.h"
#include <stdio.h>

Time* Time::instance = NULL;
float Time::time = 0.0f;
float Time::deltaTime = 0.0167f;

Time::Time()
{

}

void Time::Tick()
{
	time += deltaTime;
}

Time::~Time()
{
}

Time& Time::singleton()
{
	if (!instance){
		instance = new Time();
	}
	return *instance;
}

void Time::destroy()
{
	Time* instance = &singleton();
	delete instance;
}
