#pragma once
#include <iostream>
class GameObject;
class Event;
class Component				// Pure virtual class 
{
	
	public:
		enum ComponentType
		{
			TRANSFORM,
			SPRITE,
			KBCONTROLLER,
			PHYSICS,
			BODY,
			BEHAVIOR,
			TypeCount
		};
		
		GameObject * mOwner;	// Points to the game object that own this component
		ComponentType mType;	// Type of the component being created, using for searching later on
		virtual void Update() = 0;		// TODO: Shift update functionality to the Game State Manager rather than making the objects responsible for their own updation
		virtual void Serialize(std::string &, unsigned int &) = 0; // Pure virtual functions MUST be redefined in the derived classes or else compiler throws errors
		virtual void HandleEvent(Event *pEvent) {}
		virtual ~Component() {}
	
	protected:				// Made protected because we don't want objects of this class to be instantiated directly, but derived classes can access it
		Component(ComponentType type) : mType(type) {}
};

