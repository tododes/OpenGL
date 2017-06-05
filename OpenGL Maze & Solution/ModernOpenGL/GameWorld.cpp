#include "GameWorld.h"
#include <stdio.h>

GameWorld* GameWorld::instance = NULL;

GameWorld::GameWorld()
{
	gravity = 0.01f;
	windSpeed = 0.0f;
}


GameWorld::~GameWorld()
{
	
}

GameWorld& GameWorld::singleton()
{
	if (instance == NULL){
		instance = new GameWorld();
	}
	return *instance;
}

void GameWorld::DestroyInstance()
{
	GameWorld* gw = &singleton();
	delete gw;
}
