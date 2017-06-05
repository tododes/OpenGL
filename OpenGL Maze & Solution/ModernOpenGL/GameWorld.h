#pragma once
class GameWorld
{
private:
	static GameWorld* instance;
	GameWorld();
	~GameWorld();
public:
	float gravity;
	float windSpeed;
	static GameWorld& singleton();
	static void DestroyInstance();
};

