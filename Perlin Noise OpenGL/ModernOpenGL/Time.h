#pragma once
class Time
{
private:
	Time();
	~Time();
public:
	static Time* instance;
	static float time;
	static float deltaTime;
	void Tick();
	
	static Time& singleton();
	static void destroy();
};

