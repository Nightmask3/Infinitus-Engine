#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "..\Entity Library\GameObject.h"
#include "..\Physics Library\BoundingSphere.h"
#include "BehaviorComponent.h"
#include <time.h>
void BehaviorComponent::Update()
{
	srand(time(NULL));
	TransformComponent * t = nullptr;
	t = static_cast<TransformComponent *>(mOwner->GetComponent(Component::TRANSFORM));
	if (mMoveDir == 0)
	{
		random = rand() % 2 + 1;
	}
	// If not colliding with an object, keep moving in a random direction
	countdown--;
	if (mColliding == false)
	{
		mMoveDir = 1;
		switch (random)
		{
			case 1:
				t->Translate(0, 0, moveCoordinate);
				break;
			case 2:
				t->Translate(0, 0, -moveCoordinate);
				break;
			default:
				break;
		}
		
	}
	// If entity is colliding with an object, change direction
	if (countdown == 0)
	{
		countdown = 10;
		mMoveDir = 0;
	}
}
void BehaviorComponent::HandleEvent(Event *pEvent)
{

}