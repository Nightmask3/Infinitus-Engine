#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include "Bounding.h"
#include "BoundingSphere.h"
#include "..\Math Library\Vector3D.h"

class Plane : public Bounding
{
private:
	const Vector3D mNormal;
	const float mDistance;
public:
	Plane(const Vector3D & Normal, float dist) :
		mNormal(Normal),
		mDistance(dist), Bounding(Bounding::PLANE){}
	IntersectData IntersectSphere(const BoundingSphere & other) const;
	inline const Vector3D & GetNormal() const { return mNormal; }
	inline const float GetDistance() const { return mDistance; }
	Plane Normalized() const;
};
#endif