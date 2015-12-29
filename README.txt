
· Debug Drawing
	o WIREFRAME DEBUG : P
	o COLLISION DEBUG : C
	o Player blue when not colliding and red when colliding
	o Walls turn green when touched
· Object Architecture
	o Basic C++ Objects
	o Component Based Design
· Communication
	o Basic Events
· Data Driven Design
	o Basic Text Serialization. 
	o Creation of objects from data files.
	o Level Files (Binary Map, Exported.txt)
· Frame rate Controller
	o Locked at 60	
· Input
	o Input Manager providing keyboard and mouse key and 	button “IsPressed”, “IsTriggered” and “IsReleased” 	detection.
· Graphics
	o Hardware accelerated sprite rendering (textured quads 	in OpenGL)
	o Basic Sprite transformation (Translation, Rotation, and 	Scale).
	o Movement translates the player for instance
	o Compatability for drawing with Element Buffer Arrays	(i.e. Indexed drawing)
· Physics
	o Basic collision detection between circles.
	o Basic Collision response (bouncing etc). 
	o Collision between different bodies types
		o Sphere vs plane
		o Sphere vs Sphere
		o Sphere vs AABB
· Game Requirements
	o Human player control of a ship, avatar, or character
	o Game runs at 30 fps most of the time. 
	o At least 2 different types of enemies with different 	behaviors.
		o LEFT - RIGHT
		o UP - DOWN
o Collision between player and enemies
o In-game controls screen 
	o Press M to see controls
o Game must have a win / lose condition.
	o WIN : Reach top left of the map
	o LOSE : Touch an enemy 3 times
· Other Features
o Full 3D Pipeline
o 3D Physics Engine with easy support for adding collison between different types of bodies