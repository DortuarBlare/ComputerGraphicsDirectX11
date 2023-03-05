#pragma once
#include "pch.h"
#include "GameObject.h"
#include "InputDevice.h"

using namespace DirectX::SimpleMath;

class CameraGameObject : public GameObject {
private:
	bool perspective = true;
	float fov = DirectX::XM_PIDIV2;
	float nearPlane = 0.1f;
	float farPlane = 1000.0f;

	float cameraRotationSpeed = 0.005f;

	float yaw = 0; // Better use localRotation later
	float pitch = 0; // Better use localRotation later
	
	Matrix viewMatrix;
	Matrix projectionMatrix;

	Matrix CreatePerspectiveMatrix();
	Matrix CreateOrthographicMatrix();

public:
	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;

	Matrix GetCameraMatrix();
	
	//void MouseEventHandler(const InputDevice::MouseMoveEventArgs& mouseData, int payload);

	// Methods

	// GetVector
	// invert get up...

	//CreatePerspectiveFieldOFView

	//CameraController
	// 
	// Yaw and Pitch without third
	// inputDevice AddRaw(...)
};
