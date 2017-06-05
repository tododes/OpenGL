#pragma once
class Time
{
private:
	Time();

public:
	static float deltaTime;
	static float time;
	static void Tick();
};

