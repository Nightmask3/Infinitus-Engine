#pragma once
#include "Component.h"
#include "..\Source\Math Library\Vector2D.h"
/*#include "Shape.h"
#include "ShapeCircle.h"*/

// Forward Declaration
class Shape;
class PhysicsComponent : public Component
{
public:
	void Serialize(FILE **pFile);

	Vector2D mPositionCurr;
	Vector2D mPositionPrev;

	Vector2D mVelocity;
	Vector2D mAcceleration;

	Vector2D mForce;
	float mMass;
	float mInverseMass;

	Shape * mpShape;

	void Integrate(float Gravity, float DeltaTime);
	PhysicsComponent();
	~PhysicsComponent();
};

