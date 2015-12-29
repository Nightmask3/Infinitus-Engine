#include "Bounding.h"
#include "BoundingSphere.h"
#include "BoundingBox.h"
#include "Plane.h"
IntersectData Bounding::Intersect(const Bounding & other) const
{
	if (mType == Bounding::SPHERE && other.mType == Bounding::PLANE)
	{	
		// Get a read only reference to a Plane and Sphere to use for intersection
		const BoundingSphere self = static_cast<BoundingSphere const &>(*this);
		const Plane otherPlane = static_cast<Plane const &>(other);
		// Checks if plane and sphere are intersecting
		return otherPlane.IntersectSphere(self);
	}
	else if (mType == Bounding::AABB && other.mType == Bounding::SPHERE)
	{
		// Get a read only reference to Sphere and an AABB to use for intersection
		const BoundingBox self = static_cast<BoundingBox const &>(*this);
		const BoundingSphere otherSphere = static_cast<BoundingSphere const &>(other);
		// Checks if AABB and sphere are intersecting
		return otherSphere.IntersectAABB(self);
	}
	else if (mType == Bounding::SPHERE && other.mType == Bounding::SPHERE)
	{
		// Get a read only reference to Sphere and an AABB to use for intersection
		const BoundingSphere self = static_cast<BoundingSphere const &>(*this);
		const BoundingSphere otherSphere = static_cast<BoundingSphere const &>(other);
		// Checks if AABB and sphere are intersecting
		return otherSphere.IntersectBoundingSphere(self);
	}
	/*std::cerr << "Error: Collisions not implemented between specified bounding shapes!\n";*/

	return IntersectData(false, 0);
}
void Bounding::UpdateCenter()
{
	if (mType == SPHERE)
	{
		BoundingSphere * sphere = nullptr;
		TransformComponent * transform = nullptr;
		transform = static_cast<TransformComponent *>(mOwner->mOwner->GetComponent(Component::TRANSFORM));
		sphere = static_cast<BoundingSphere *>(this);
		Vector3D center;
		Vector3DSet(&center, transform->mTranslation.m[0][3], transform->mTranslation.m[1][3], transform->mTranslation.m[2][3], 1);
		sphere->SetCenter(center);
	}
	else if (mType == AABB)
	{
		BoundingBox * box = nullptr;
		TransformComponent * transform = nullptr;
		transform = static_cast<TransformComponent *>(mOwner->mOwner->GetComponent(Component::TRANSFORM));
		box = static_cast<BoundingBox *>(this);
		Vector3D center;
		Vector3DSet(&center, transform->mTranslation.m[0][3], transform->mTranslation.m[1][3], transform->mTranslation.m[2][3], 1);
		box->SetCenter(center);
	}
}
Bounding::~Bounding()
{
}
