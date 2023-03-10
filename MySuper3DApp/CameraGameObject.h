#pragma once
#include "pch.h"
#include "GameObject.h"
#include "InputDevice.h"

class InputDevice;

using namespace DirectX;
using namespace DirectX::SimpleMath;

class CameraGameObject : public GameObject {
private:
	float fov = XM_PIDIV2;
	float nearPlane = 0.1f;
	float farPlane = 1000.0f;

	float yaw = 0;
	float pitch = 0;
	Vector3 target;
	Vector3 up;
	float rotationSpeed = 0.005f;
	float orbitApproximationSpeed = 0.0025f;
	
	Matrix viewMatrix;
	Matrix projectionMatrix;

	Matrix CreateViewMatrix();
	Matrix CreatePerspectiveMatrix();
	Matrix CreateOrthographicMatrix();

	void MouseEventHandler(const InputDevice::MouseMoveEventArgs& mouseData);

public:
	bool perspective = true;
	bool orbitMode = false;
	Vector3 orbitOffset;

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;

	void AttachTo(std::shared_ptr<TransformComponent> transform);
	void Detach();

	Matrix GetCameraMatrix();
	Vector3 Forward();
	Vector3 OrbitForwardXZ();
	Vector3 OrbitRightXZ();
	Vector3 Right();
};
