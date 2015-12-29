#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include <iostream>
#include "..\Math Library\Vector3D.h"
#include "Bounding.h"
#include "BoundingBox.h"
class BoundingSphere : public Bounding 
{
	private:
		Vector3D mCenter;
		const float mRadius;
	public:
		IntersectData IntersectBoundingSphere(const BoundingSphere & other) const;
		IntersectData IntersectAABB(const BoundingBox & other) const;
		inline const Vector3D & GetCenter() const { return mCenter; }
		inline const float & GetRadius() const { return mRadius; }
		inline void SetCenter(Vector3D const & vec) { Vector3DSet(&mCenter, vec.x, vec.y, vec.z, 1); };
		BoundingSphere(const Vector3D & cent, const float rad = 1.0f) : mCenter(cent), mRadius(rad), Bounding(SPHERE) { }
};
#endif