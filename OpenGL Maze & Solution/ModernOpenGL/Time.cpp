#include "Time.h"

float Time::deltaTime = 0.0167f;
float Time::time = 0.0f;

Time::Time()
{

}

void Time::Tick()
{
	time += deltaTime;
}