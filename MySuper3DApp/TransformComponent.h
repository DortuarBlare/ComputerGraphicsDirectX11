#pragma once
#include "pch.h"
#include "GameObjectComponent.h"

using namespace DirectX::SimpleMath;

class TransformComponent : public GameObjectComponent {
public:
	std::shared_ptr<TransformComponent> parent = nullptr;

	std::shared_ptr<Vector3> localPosition;
	std::shared_ptr<Quaternion> localRotation;
	std::shared_ptr<Vector3> scale;

	TransformComponent();

	void Translate(Vector3 translation);

	Vector3 GetPosition();
	void SetPosition(Vector3 position);

	Quaternion GetRotation();
	void SetRotation(Quaternion rotation);

	Matrix GetLocalModel();
	Matrix GetModel();
	Matrix GetLocalView();
	Matrix GetView();

	Vector3 LocalForward();
	Vector3 LocalUp();
	Vector3 LocalRight();
	Vector3 Forward();
	Vector3 Up();
	Vector3 Right();
};
