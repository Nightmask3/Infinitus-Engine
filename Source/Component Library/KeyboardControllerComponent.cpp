#include "KeyboardControllerComponent.h"

void KeyboardControllerComponent::Update(void)
{
	TransformComponent * t;
	PhysicsComponent * p;
	t = static_cast<TransformComponent *>(mOwner->GetComponent(ComponentType::TRANSFORM));
	p = static_cast<PhysicsComponent *>(mOwner->GetComponent(ComponentType::PHYSICS));
	if (InputManager.isKeyPressed(sf::Keyboard::Up))
	{
		// Forward Movement
		t->Translate(0, 0, MOVE_SPEED * FrameController.frametime);
	}
	if (InputManager.isKeyPressed(sf::Keyboard::Down))
	{
		// Backward Movement
		t->Translate(0, 0, -MOVE_SPEED * FrameController.frametime);
	}
	if (InputManager.isKeyPressed(sf::Keyboard::Left))
	{
		// Left Movement
		t->Translate(MOVE_SPEED * FrameController.frametime, 0, 0);
		
	}
	if (InputManager.isKeyPressed(sf::Keyboard::Right))
	{
		// Right Movement
		t->Translate(-MOVE_SPEED * FrameController.frametime, 0, 0);
	}
	if (t->mTranslation.m[0][3] >= 15 && t->mTranslation.m[2][3] >= 15)
		mGameWon = true;
	if (InputManager.isKeyPressed(sf::Keyboard::Space))
	{
		// Right Movement
		t->Translate(0, MOVE_SPEED * FrameController.frametime, 0);
	}
	Vector3DSet(&p->mPositionCurr, t->mTranslation.m[0][3], t->mTranslation.m[1][3], t->mTranslation.m[2][3], 1);
}

void KeyboardControllerComponent::Serialize(std::string &, unsigned int &)
{
}