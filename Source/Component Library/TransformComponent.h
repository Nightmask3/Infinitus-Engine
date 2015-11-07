#pragma once
#include <iostream>

#include "Component.h"
#include "..\Source\Math Library\Math2D.h"
#include "../Source\Math Library\Matrix2D.h"
#include "../Source\Math Library\Vector2D.h"
class TransformComponent : public Component
{
	private:
		Vector2D Position;				// Stores the position vector of the component
		Vector2D Rotation;				// Stores the rotation vector of the component
		Vector2D Scale;					// Stores the scale vector of the component
	public:
		TransformComponent();
		~TransformComponent();
		void Update();
		void Serialize(FILE **pFile);
};

