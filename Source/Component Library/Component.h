#pragma once
#include <iostream>


class GameObject;
class Component				// Pure virtual class // Abstract Base Class
{
	
	public:
		enum ComponentType
		{
			TRANSFORM,
			SPRITE,
			PHYSICS,
			BODY,
			TypeCount
		};
		virtual ~Component();
		GameObject * mOwner;	// Points to the game object that own this component
		ComponentType mType;	// Type of the component being created, using for searching later on
		virtual void Update() = 0;		// TODO: Shift update functionality to the Game State Manager rather than making the objects responsible for their own updation
		virtual void Serialize(FILE **pFile) = 0; // Pure virtual functions MUST be redefined in the derived classes or else compiler throws errors
	
	protected:				// Made protected because we don't want objects of this class to be instantiated directly, but derived classes can access it
		Component(Component::ComponentType type)
		{
			mType = type;
		}
};

