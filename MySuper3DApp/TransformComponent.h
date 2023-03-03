#pragma once
#include "pch.h"
#include "GameObjectComponent.h"

class TransformComponent : public GameObjectComponent {
public:
	std::shared_ptr<DirectX::SimpleMath::Vector4> localPosition;
	//std::shared_ptr<DirectX::SimpleMath::Vector4> position;
	std::shared_ptr<DirectX::SimpleMath::Quaternion> localRotation;
	//std::shared_ptr<DirectX::SimpleMath::Quaternion> rotation;

	TransformComponent();
	TransformComponent(DirectX::SimpleMath::Vector4 localPosition, DirectX::SimpleMath::Vector4 localRotation);

	void Initialize();
	void Update();
	void FixedUpdate();
	void Draw();
	void Reload();
	void DestroyResources();
};
