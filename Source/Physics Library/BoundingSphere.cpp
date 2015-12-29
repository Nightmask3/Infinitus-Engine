#include "BoundingSphere.h"
#include "BoundingBox.h"
#include "..\Entity Library\GameObject.h"
#include "..\Component Library\PhysicsComponent.h"
#include "..\Component Library\BehaviorComponent.h"


IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere & other) const
{
	float radiusDistance = mRadius + other.GetRadius(); // Distance between two centers for the spheres to be intersecting
	Vector3D distance;
	float centerDistance = Vector3DDistance(other.GetCenter(), mCenter);
	/*if (centerDistance < radiusDistance) 
		std::cout << "Intersection!\n";*/
	// If distance between centers is lesser than radius distance, the spheres are intersecting
	return IntersectData(centerDistance < radiusDistance, centerDistance - radiusDistance);
}

IntersectData BoundingSphere::IntersectAABB(const BoundingBox & other) const
{
	// Clamp the circle to the closest point on the AABB
	Vector3D Snap; 
	Vector3D Difference;
	float distance = 0;
	
	float LeftFaceX = other.mCenter.x - other.GetHalfWidth();
	float RightFaceX = other.mCenter.x + other.GetHalfWidth();

	float TopFaceY = other.mCenter.y + other.GetHalfHeight();
	float BottomFaceY = other.mCenter.y - other.GetHalfHeight();

	float FrontFaceZ = other.mCenter.z + other.GetHalfDepth();
	float BackFaceZ = other.mCenter.z - other.GetHalfDepth();

	if (mCenter.x < LeftFaceX)
		Snap.x = LeftFaceX;
	else if (mCenter.x > RightFaceX)
		Snap.x = RightFaceX;

	if (mCenter.y > TopFaceY)
		Snap.y = TopFaceY;
	else if (mCenter.y < BottomFaceY)
		Snap.y = BottomFaceY;

	if (mCenter.z > FrontFaceZ)
		Snap.z = FrontFaceZ;
	else if (mCenter.z < BackFaceZ)
		Snap.z = BackFaceZ;
	
	Vector3DSub(Difference, mCenter, Snap);
	distance = Vector3DLength(Difference);
	IntersectData data(distance <= mRadius, distance, Difference);
	
	if (data.GetDoesIntersect())
	{				
		data.mDirection = data.SetDirection(Difference);
		if (data.mDirection == IntersectData::UP || IntersectData::DOWN)
		{
			// Ignores UP and DOWN collisions for the moment (i.e. Y axis plays no part in movement of enemies)
		}
		else
		{
			BehaviorComponent * b = nullptr;
			b = static_cast<BehaviorComponent *>(mOwner->mOwner->GetComponent(Component::BEHAVIOR));
			if(b != nullptr)
				b->mColliding = true;
		}
		return data;
	}
	else
		return IntersectData(false, 0);
}