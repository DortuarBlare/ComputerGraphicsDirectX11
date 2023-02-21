#pragma once

class Camera {
	// Add plane component

	// Fields
	// 
	// view matrix - identity
	// projection matrix
	// fov
	
	// Methods
	// 
	// GetCameraMatrix
	//viewMatrix * projectionMatrix

	// GetVector
	// invert get up...

	//CreatePerspectiveFieldOFView

	//CameraController
	// 
	// Yaw and Pitch without third
	// inputDevice AddRaw(...)

	// Update
	// Change velocity
	// Normalize
	// rotMatrix.Forward() * velDirection.x + Vector3::Up * velDirection.y + rotMatrix.Right() * velDirection.z;
	// Normalize if has something
	// cameraPos = cameraPos * velDir * VelocityMagnitude * deltaTime
	// viewMatrix = createLookAt(cameraPos, cameraPos + rotMatrix + forward, vector3::up)
};
