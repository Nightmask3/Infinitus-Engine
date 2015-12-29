#include "Camera.h"

void Camera::Update()
{
	GLfloat cameraSpeed = 5.0f * FrameMan.getFrameTime().asSeconds();
	if (InMan.isKeyPressed(sf::Keyboard::W))
	{
		// Forward Movement
		// Scales Target Vector by camera speed before adding to CameraPos
		Vector3DScaleAdd(&CameraPos, &CameraDir, &CameraPos, cameraSpeed);
	}
	if (InMan.isKeyPressed(sf::Keyboard::A))
	{
		// Left Movement
		Vector3D RightVec;
		RightVec = Vector3DCrossProduct(&CameraDir, &UpVec);
		// Normalize target vector before scaling and subtracting from camera position
		Vector3DNormalize(RightVec, RightVec);
		Vector3DScale(&RightVec, &RightVec, cameraSpeed);
		Vector3DSub(CameraPos, CameraPos, RightVec);
	}
	if (InMan.isKeyPressed(sf::Keyboard::S))
	{
		// Backward Movement 
		// Scale sub doesn't work out as expected here, modifies input values at runtime while processing, which leads to other errors
		Vector3D temp;
		Vector3DScale(&temp, &CameraDir, cameraSpeed);
		Vector3DSub(CameraPos, CameraPos, temp);
	}
	if (InMan.isKeyPressed(sf::Keyboard::D))
	{
		// Right Movement
		Vector3D RightVec;
		RightVec = Vector3DCrossProduct(&CameraDir, &UpVec);
		// Normalize before adding
		Vector3DNormalize(RightVec, RightVec);
		Vector3DScaleAdd(&CameraPos, &RightVec, &CameraPos, cameraSpeed);
	}
	//PrevMousePos = InMan.GetMousePosition();
	// MOUSE UPDATE - EDITOR VIEW ONLY ALLOWS THIS WHEN RIGHT CLICK IS ACTIVATED AS WELL
	if (InMan.isMouseButtonPressed(sf::Mouse::Right))
	{
		PrevMousePos = InMan.GetMousePosition();
		CurrentMousePos = InMan.GetMousePosition();
		GLfloat changeXPos, changeYPos;
		changeXPos = CurrentMousePos.x - PrevMousePos.x;
		changeYPos = PrevMousePos.y - CurrentMousePos.y; // Flipped as Y values range from bottom to top
		PrevMousePos = CurrentMousePos;					 // Sets previous mouse Position to the current mouse position
		// Affects the changes by sensitivity
		changeXPos *= Sensitivity;
		changeYPos *= Sensitivity;
		// Affects the yaw and pitch
		CameraYaw += changeXPos;
		CameraPitch += changeYPos;
		// Cap the pitch values to ensure non - weird movement
		if (CameraYaw > MAX_PITCH)
			CameraYaw = MAX_PITCH;
		if (CameraYaw < -MAX_PITCH)
			CameraYaw = -MAX_PITCH;
		Vector3D temp;
		temp.x = cosf(CameraPitch) * cosf(CameraYaw);
		temp.y = sinf(CameraPitch);
		temp.z = cosf(CameraPitch) * sinf(CameraYaw);
		Vector3DNormalize(CameraDir, temp);
	}
}


Camera::~Camera()
{
}
