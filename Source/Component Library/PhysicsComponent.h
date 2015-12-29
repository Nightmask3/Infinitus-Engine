#pragma once
#include "..\Entity Library\GameObject.h"
#include "TransformComponent.h"
#include "..\Math Library\Vector3D.h"
#include "..\Physics Library\Bounding.h"

struct VertexCollider
{
	GLfloat X, Y, Z;	 // Position
	GLfloat R, G, B, A;	 // Color
	GLfloat U = 0, V = 0;// Texture Coordinates
};
class PhysicsComponent : public Component
{
public:
	/* -------- VARIABLES ---------- */
	struct Derivative
	{
		Vector3D mDerivedVelocity;
		Vector3D mDerivedAcceleration;
		Derivative()
		{
			Vector3DZero(&mDerivedAcceleration);
			Vector3DZero(&mDerivedVelocity);
		}
	};
	Vector3D mPositionCurr;
	Vector3D mPositionPrev;
	Vector3D mVelocity;
	Vector3D mForce;
	Vector3D mMomentum;
	bool mIsPlayer;
	float mMass;
	float mInverseMass;
	bool mAcceleration;
	int mLifeCount;
	Bounding * mpShape; // Pointer to the kind of collision bounding box to be used for this object
	std::vector<VertexCollider> VertexList;
	std::vector<GLuint> IndexList;
	/* -------- FUNCTIONS ---------- */
	// GETTERS
	inline const Bounding & GetCollider() const { return static_cast<const Bounding &>(*mpShape); }
	inline const std::vector<VertexCollider> & GetVertexListCollider() { return VertexList; }
	inline const std::vector<GLuint> & GetIndexListCollider() { return IndexList; }
	// SETTERS
	inline void SetMass(float mass) { mMass = mass; mInverseMass = 1 / mMass; }
	void Update(){}
	void Serialize(std::string & Contents, unsigned int & Count);
	void UpdateTransform();
	void Recalculate();
	void Integrate(double t, double dt);
	void HandleEvent(Event *);
	Derivative Evaluate(double t, double dt, const Derivative &);
	Vector3D Acceleration(float t);
	PhysicsComponent() : Component(Component::PHYSICS)
	{
		Vector3DZero(&mVelocity);
		Vector3DZero(&mPositionCurr);
		Vector3DZero(&mPositionPrev);
		Vector3DZero(&mMomentum);
		Vector3DZero(&mForce);
		mMass = 0.0f;
		mInverseMass = 0.0f;
		mAcceleration = true;
		mIsPlayer = false;
		mLifeCount = 3;

	}
	~PhysicsComponent(){}
};

