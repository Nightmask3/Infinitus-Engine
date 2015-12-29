#include "BoundingBox.h"

IntersectData BoundingBox::IntersectAABB(const BoundingBox& other) const
{
	Vector3D distance1, distance2, distance;
	// If this AABB is closer to the origin
	Vector3DSub(distance1, other.GetMinExtends(), maxExtends);
	// If the OTHER AABB is closer to the origin
	Vector3DSub(distance2, minExtends, other.GetMaxExtends());
	// The actual distance vector is the larger distance between the AABBs
	distance = Vector3DMaxBetween(distance1, distance2);
	float maxDistance = Vector3DMax(distance);
	// If there is some amount of space between the two on any axis, returns true, else false (I.E. intersection)
	if (maxDistance < 0)
		std::cout << "Intersection!\n";
	return IntersectData(maxDistance < 0, maxDistance);
}