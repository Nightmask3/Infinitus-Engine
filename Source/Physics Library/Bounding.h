#ifndef BOUNDING_H
#define BOUNDING_H
#include "IntersectData.h"
// Forward Declaration
class PhysicsComponent;
class Bounding
{
// Accessible to children but not external objects/methods
public:
	enum RigidBodyType
	{
		SPHERE,
		AABB,
		PLANE,
		COUNT
	};
	void UpdateCenter();
	IntersectData Intersect(const Bounding &) const;
	// Holds the physics component that owns this Bounding box
	PhysicsComponent * mOwner;
	// Type of rigid body (used in searching later)
	RigidBodyType mType;
	// Direction of Intersection Data (used in Behavior Component)
	Vector3D mCollisionDir;
	Bounding(RigidBodyType type) : mType(type) {}
	virtual ~Bounding();
};
#endif

