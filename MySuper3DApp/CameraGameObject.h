#pragma once
#include "pch.h"
#include "GameObject.h"
#include "InputDevice.h"

class CameraGameObject : public GameObject {
private:
	bool perspective = true;
	float fov = DirectX::XM_PIDIV2;
	const float nearPlane = 0.1f;
	const float farPlane = 1000.0f;

	float cameraRotationSpeed = 0.005f;

	float yaw = 0;
	float pitch = 0;
	
	DirectX::SimpleMath::Matrix viewMatrix;
	DirectX::SimpleMath::Matrix projectionMatrix;

	void CreatePerspectiveFieldOFView();
	void CreateOrthographic();

public:
	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;

	DirectX::SimpleMath::Matrix GetCameraMatrix();
	
	//void MouseEventHandler(const InputDevice::MouseMoveEventArgs& mouseData, int payload);

	// Methods

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
