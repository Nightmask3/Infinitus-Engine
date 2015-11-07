#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent() :Component()	// TODO ADD TYPE OF COMPONENT BEING CONSTRUCTED
{
	Vector2DZero(&mVelocity);
	Vector2DZero(&mAcceleration);

	Vector2DZero(&mPositionCurr);
	Vector2DZero(&mPositionPrev);

	Vector2DZero(&mForce);
	mMass = 0.0f;
	mInverseMass = 0.0f;
}


PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Serialize(FILE **pFile)
{
	fscanf_s(*pFile, "%s\n", &mMass);

	if (mMass)	// To prevent dividing by zero
		mInverseMass = 1.0f / mMass;
	else
		mInverseMass = 0.0f;

	char shapeName[256];
	memset(shapeName, 0, 256 * sizeof(char));

	fscanf_s(*pFile, "%255s\n", shapeName, sizeof(shapeName));	 // READS THE COMPONENT NAME FROM THE TEXT FILE

	if (strcmp(shapeName, "Circle") == 0)
	{
		mpShape = new ShapeCircle();
	}
		
}

void PhysicsComponent::Integrate(float Gravity, float DeltaTime)
{
	// Sets previous position to be equal to current position
	Vector2DSet(&mPositionPrev, mPositionCurr.x, mPositionCurr.y);


	// Computes change in position using velocity
	mVelocity.x += mAcceleration.x * DeltaTime;
	mVelocity.y += mAcceleration.y * DeltaTime;

	// Computes change in velocity using acceleration
	mPositionCurr.x += mVelocity.x * DeltaTime;
	mPositionCurr.y += mVelocity.y * DeltaTime;

	// Account for gravity in the force acting on the body
	mForce.y += Gravity;

	// Compute the acceleration
	mAcceleration.x = mForce.x * mInverseMass;
	mAcceleration.y = mForce.y * mInverseMass;
}