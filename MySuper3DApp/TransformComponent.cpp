#include "pch.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent() {
	localPosition = std::make_shared<DirectX::SimpleMath::Vector4>(DirectX::SimpleMath::Vector4::Zero);
	localRotation = std::make_shared<DirectX::SimpleMath::Quaternion>(DirectX::SimpleMath::Quaternion::Identity);
}

TransformComponent::TransformComponent(DirectX::SimpleMath::Vector4 localPosition, DirectX::SimpleMath::Vector4 localRotation) {
	this->localPosition = std::make_shared<DirectX::SimpleMath::Vector4>(localPosition);
	this->localRotation = std::make_shared<DirectX::SimpleMath::Quaternion>(localRotation);
}

void TransformComponent::Initialize() {}

void TransformComponent::Update() {}

void TransformComponent::FixedUpdate() {}

void TransformComponent::Draw() {}

void TransformComponent::Reload() {}

void TransformComponent::DestroyResources() {}
