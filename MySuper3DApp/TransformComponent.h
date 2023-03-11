#pragma once
#include "pch.h"
#include "GameObjectComponent.h"

using namespace DirectX::SimpleMath;

class TransformComponent : public GameObjectComponent {
public:
	std::shared_ptr<TransformComponent> parent = nullptr;

	std::shared_ptr<Vector3> localPosition;
	std::shared_ptr<Quaternion> localRotation;

	TransformComponent();

	void Initialize();
	void Update();
	void Draw();
	void Reload();
	void DestroyResources();

	Vector3 GetPosition();
	void SetPosition(Vector3 position);
	void Translate(Vector3 translation);

	Quaternion GetRotation();
	void SetRotation(Quaternion rotation);

	Matrix GetLocalModel();
	Matrix GetModel();
	Matrix GetLocalView();

	Vector3 LocalForward();
	Vector3 LocalUp();
	Vector3 LocalRight();
	Vector3 Forward();
	Vector3 Up();
	Vector3 Right();
};
