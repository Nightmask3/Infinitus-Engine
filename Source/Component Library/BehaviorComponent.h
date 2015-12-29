#pragma once
#include "Component.h"
class BehaviorComponent : public Component
{
public:
	BehaviorComponent() : mColliding(false), mMoveDir(0), countdown(10), random(0), moveCoordinate(0.1f), Component(ComponentType::BEHAVIOR) {}
	virtual ~BehaviorComponent() {}


	bool mColliding;
	int mMoveDir;
	int countdown;
	int random; 
	float moveCoordinate;
	void Update();
	void Serialize(std::string &, unsigned int &) {}
	void HandleEvent(Event *pEvent);
};