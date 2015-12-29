#include "IntersectData.h"

IntersectData::Direction IntersectData::SetDirection(Vector3D const & vector) const
{
	Vector3D Compass[] = {
		Vector3D(0.0f, 1.0f, 0.0f, 1), // UP
		Vector3D(0.0, -1.0f, 0.0f, 1), // DOWN
		Vector3D(-1.0f, 0.0f, 0.0f, 1),// LEFT
		Vector3D(1.0f, 0.0f, 0.0f, 1), // RIGHT
		Vector3D(0.0f, 0.0f, 1.0f, 1), // FRONT
		Vector3D(0.0f, 0.0f, -1.0f, 1) // BACK
	};
	Vector3D temp;
	Vector3DNormalize(temp, vector);
	float max = 0.0f;
	int best_match = -1;
	for (int i = 0; i < 6; ++i)
	{
		float dotProduct = Vector3DDotProduct(temp, Compass[i]);
		if (dotProduct > max)
		{
			max = dotProduct;
			best_match = i;
		}
	}

	return static_cast<IntersectData::Direction>(best_match);
}