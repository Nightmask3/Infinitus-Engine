#pragma once

#define MAX_PITCH 90.0f
#define MAX_YAW 90.0f	// Not used but defined anyway
#define SENSITIVITY 0.01f
#include "..\Math Library\Vector3D.h"
#include "..\Math Library\Matrix3D.h"
#include "..\SFML Library\SFMLInputManager.h"
#include "..\Manager Library\FrameRateController.h"
#include "..\Component Library\Component.h"
#include "..\..\Dependencies\GLEW\glew.h"


class SFMLInputManager;
class Camera
{
private:
	// VIEW MATRIX VARIABLES
	Vector3D CameraPos;
	Vector3D CameraDir;
	Vector3D UpVec;
	// EULER ANGLE VARIABLES
	Vector3D CurrentMousePos;
	Vector3D PrevMousePos;
	GLfloat CameraPitch; // Holds the current Pitch of the camera (rotation around Y axis)
	GLfloat CameraYaw;	 // Holds the current Yaw of the camera   (rotation around X axis)
	GLfloat Sensitivity; // Affects the camera sensitivity
	SFMLInputManager & InMan;
	FrameRateController & FrameMan;
public:
	// GETTERS
	Vector3D & GetCameraPos() { return CameraPos; }
	Vector3D & GetCameraDir(){ return CameraDir; }
	Vector3D & GetUpVec(){ return UpVec; }
	// SETTERS
	void SetCameraPos(float x, float y, float z, float w) { CameraPos.x = x; CameraPos.y = y; CameraPos.z = z; CameraPos.w = w; }
	void SetCameraDir(float x, float y, float z, float w) { CameraDir.x = x; CameraDir.y = y; CameraDir.z = z; CameraDir.w = w; }
	void SetUpVec(float, float, float, float);
	void Update();
	Camera();
	Camera(Vector3D const & eye, Vector3D const & target, Vector3D const & up, SFMLInputManager & in, FrameRateController & fr) : InMan(in), FrameMan(fr)
	{
		CameraPos = eye;
		CameraDir = target;
		UpVec = up;
		CameraPitch = 0.0f;
		CameraYaw = 0.0f;
		Sensitivity = SENSITIVITY;
	};
	
	virtual ~Camera();
};

