#pragma once
// C++ header files
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <sstream>
// Math Library header files
//#include "..\Math Library\Math2D.h"
#include "..\Math Library\Matrix3D.h"
#include "..\Math Library\Vector3D.h"
// Component header files
#include "Component.h"
#include "..\..\Dependencies\GLEW\glew.h"
class TransformComponent : public Component
{
	public:
		Matrix3D mTranslation;			// Stores the translation matrix of the component
		Matrix3D mRotation;				// Stores the rotation matrix of the component
		Matrix3D mScale;				// Stores the scaling matrix of the component
		Vector3D mOriginalScale;		// Used to create a bounding box scaled to the original dimensions of the object
	public:
		TransformComponent();// : Component(ComponentType::TRANSFORM){ Matrix3DIdentity(&mTranslation); Matrix3DIdentity(&mRotation); Matrix3DIdentity(&mScale); } // Initialization of matrices done in the Math library
		~TransformComponent();
		void Translate(float X, float Y, float Z);
		void Rotate(float AngleX, float AngleY, float AngleZ);
		void Scale(float X, float Y, float Z);
		// Scales the sprite along with its collider
		void ScaleWithCollider(float X, float Y, float Z);
		void Update();
		void Serialize(std::string &, unsigned int &);
};

