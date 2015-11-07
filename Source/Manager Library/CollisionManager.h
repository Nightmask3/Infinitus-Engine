#pragma once
#include "Shape.h"
#include "ShapeCircle.h"

class Body;
class CollisionManager
{
public:
	CollisionManager();
	virtual ~CollisionManager();

	bool(*CollisionFunctions[Shape::ShapeType::NUM][Shape::ShapeType::NUM])(Shape *p1, float posX1, float posY1, float posX2, float posY2);
	// 2D array of function pointers, that allows access to the different collision functions based on the shape type of the arguments
	// TODO : initialize this array in the constructor
};

class Contact
{
	public:
		Contact();
		~Contact();
};
