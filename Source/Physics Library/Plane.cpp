#include "Plane.h"

Plane Plane::Normalized() const
{
	float magnitude = Vector3DLength(mNormal);
	Vector3D temp;
	Vector3DNormalize(temp, mNormal);
	return Plane(GetNormal(), mDistance/magnitude);
}
IntersectData Plane::IntersectSphere(const BoundingSphere & other) const
{
	// Finds distance of center of sphere from normal, Dot product is projection of sphere center on normal direction + how far along its own normal the plane is
	Vector3D temp;
	Vector3DNormalize(temp, mNormal);
	float distancefromSphereCenter = fabs(Vector3DDotProduct(temp, other.GetCenter()) + mDistance);
	float distancefromSphere = distancefromSphereCenter - other.GetRadius();
	// If any distance at all between the two, doesn't intersect
	/*if (distancefromSphere < 0)
		std::cout << "Intersecting!\n";*/
	return IntersectData(distancefromSphere < 0, distancefromSphere);
}