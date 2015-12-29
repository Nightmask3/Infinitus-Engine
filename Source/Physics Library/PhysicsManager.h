#pragma once
#define GRAVITY 10.0f
#include <vector>
// Manager Header files
#include "..\Manager Library\FrameRateController.h"
#include "..\Manager Library\EventManager.h"
// Component Header files
#include "..\Component Library\PhysicsComponent.h"
#include "..\Component Library\SpriteComponent.h"
// Bounding box header file for types of bodies
#include "Bounding.h"
#include "BoundingSphere.h"
#include "BoundingBox.h"
#include "Plane.h"

class CollideEvent : public Event
{
	public:
	GameObject * mpObject1;
	GameObject * mpObject2;

	CollideEvent() : Event(COLLIDE) { mpObject1 = nullptr; mpObject2 = nullptr; }
	virtual ~CollideEvent() {}
};

class PhysicsManager
{
private:
	FrameRateController & frameManager;
public:
	bool mGameOver;
	void SetBoundingBoxType(Bounding::RigidBodyType type);
	std::vector<Component *> PhysicsObjectsList;
	PhysicsManager(FrameRateController & frc) : frameManager(frc){ mGameOver = false; }
	void Simulation();
	void DetectCollision();
	void HandleCollision();
	void Update();
	void CheckCollision(Bounding const & shape1, Bounding const & shape2);
	void Resolution();
	virtual ~PhysicsManager();
};

