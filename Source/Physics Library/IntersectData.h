#pragma once
#include "..\Math Library\Vector3D.h"
class IntersectData
{
private:
	const bool mDoesIntersect;
	const float mDistance;
	const Vector3D mDifference;
public:
	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		FRONT,
		BACK
	};
	IntersectData::Direction mDirection;
	inline const bool & GetDoesIntersect() const { return mDoesIntersect; }
	inline const float & GetDistance() const { return mDistance; }
	inline const Vector3D & GetDifference() const { return mDifference; }
	inline Direction GetDirection() const { return mDirection; }
	Direction SetDirection(Vector3D const &) const;
	IntersectData(const bool does, const float dist, const Vector3D & vec = Vector3D()) :
		mDoesIntersect(does),
		mDistance(dist),
		mDifference(vec)
	{}
};