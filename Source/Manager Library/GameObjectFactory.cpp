#include "GameObjectFactory.h"

void GameObjectFactory::CreateGameObject()
{
	GameObject gObject;
	ObjectLibrary.push_back(gObject);	// Pushes the game object into the object list
}