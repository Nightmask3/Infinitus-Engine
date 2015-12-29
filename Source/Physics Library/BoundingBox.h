#ifndef AABB_H
#define AABB_H

#include <iostream>
#include "IntersectData.h"
#include "..\Component Library\TransformComponent.h"
#include "..\Component Library\PhysicsComponent.h"
#include "Bounding.h"
#include "..\Math Library\Vector3D.h"
class BoundingBox : public Bounding
{

private:
	const Vector3D minExtends;
	const Vector3D maxExtends;
	float halfWidth;
	float halfHeight;
	float halfDepth;
public:
	Vector3D mCenter;
	BoundingBox(const Vector3D & min, const Vector3D & max) :
	minExtends(min), maxExtends(max), halfWidth(0), halfHeight(0), halfDepth(0), Bounding(Bounding::AABB){}
	void SetCenter(const Vector3D & center) {
		TransformComponent * t = static_cast<TransformComponent *>(mOwner->mOwner->GetComponent(Component::TRANSFORM));
		halfWidth = t->mScale.m[0][0] / 2;
		halfHeight = t->mScale.m[1][1] / 2;
		halfDepth = t->mScale.m[2][2] / 2;
		Vector3DSet(&mCenter, center.x, center.y, center.z, 1);
	}
	
	IntersectData IntersectAABB(const BoundingBox& other) const;
	inline const Vector3D & GetCenter() { return mCenter; }
	inline const Vector3D & GetMinExtends() const { return minExtends; }
	inline const Vector3D & GetMaxExtends() const { return maxExtends; }
	inline const float GetHalfWidth() const { return halfWidth; }
	inline const float GetHalfHeight() const { return halfHeight; }
	inline const float GetHalfDepth() const { return halfDepth; }
};
#endif