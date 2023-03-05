#pragma once
#include "pch.h"
#include "GameObjectComponent.h"

class TransformComponent : public GameObjectComponent {
public:
	std::shared_ptr<TransformComponent> parent = nullptr;

	std::shared_ptr<DirectX::SimpleMath::Vector3> localPosition;
	std::shared_ptr<DirectX::SimpleMath::Quaternion> localRotation;

	TransformComponent();

	void Initialize();
	void Update();
	void FixedUpdate();
	void Draw();
	void Reload();
	void DestroyResources();

	DirectX::SimpleMath::Vector3 GetPosition();
	void SetPosition(DirectX::SimpleMath::Vector3 position);

	DirectX::SimpleMath::Quaternion GetRotation();
	void SetRotation(DirectX::SimpleMath::Quaternion rotation);

	DirectX::SimpleMath::Matrix GetLocalModel();
	DirectX::SimpleMath::Matrix GetModel();

	DirectX::SimpleMath::Vector3 LocalForward();
	DirectX::SimpleMath::Vector3 LocalUp();
	DirectX::SimpleMath::Vector3 LocalRight();
	DirectX::SimpleMath::Vector3 Forward();
	DirectX::SimpleMath::Vector3 Up();
	DirectX::SimpleMath::Vector3 Right();
};
