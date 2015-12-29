#pragma once
enum EventType
{
	COLLIDE,	// When two game objects collide
	UNCOLLIDE,	// When two game objects uncollide
	SPAWNED,	// When a game object is spawned
	DESTROYED,	// When a game object is destroyed
	EVENTCOUNT	// Keeps track of the maximum number of events
};
class Event
{
public:
	EventType mType;

	Event(EventType type) { mType = type; }
	virtual ~Event() {}
};