#pragma once
#include "pch.h"
#include "GameObjectComponent.h"

class TransformComponent : public GameObjectComponent {
public:
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


};
