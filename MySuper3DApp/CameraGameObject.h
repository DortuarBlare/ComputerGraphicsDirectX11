#pragma once
#include "pch.h"
#include "GameObject.h"
#include "InputDevice.h"

class InputDevice;

using namespace DirectX::SimpleMath;

class CameraGameObject : public GameObject {
private:
	bool perspective = true;
	float fov = DirectX::XM_PIDIV2;
	float nearPlane = 0.1f;
	float farPlane = 1000.0f;

	float yaw = 0;
	float pitch = 0;
	float cameraRotationSpeed = 0.005f;
	
	Matrix viewMatrix;
	Matrix projectionMatrix;

	Matrix CreatePerspectiveMatrix();
	Matrix CreateOrthographicMatrix();

public:
	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;

	Matrix GetCameraMatrix();
	
	void MouseEventHandler(const InputDevice::MouseMoveEventArgs& mouseData);

	// Methods

	// GetVector
	// invert get up...

	//CreatePerspectiveFieldOFView

	//CameraController
	// 
	// Yaw and Pitch without third
	// inputDevice AddRaw(...)
};
