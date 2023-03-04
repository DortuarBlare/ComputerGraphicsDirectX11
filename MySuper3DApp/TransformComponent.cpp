#include "pch.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent() {
	localPosition = std::make_shared<DirectX::SimpleMath::Vector3>(DirectX::SimpleMath::Vector3::Zero);
	localRotation = std::make_shared<DirectX::SimpleMath::Quaternion>(DirectX::SimpleMath::Quaternion::Identity);
}

void TransformComponent::Initialize() {}

void TransformComponent::Update() {}

void TransformComponent::FixedUpdate() {}

void TransformComponent::Draw() {}

void TransformComponent::Reload() {}

void TransformComponent::DestroyResources() {}

DirectX::SimpleMath::Vector3 TransformComponent::GetPosition() {
	return DirectX::SimpleMath::Vector3();
}

void TransformComponent::SetPosition(DirectX::SimpleMath::Vector3 position) {

}

DirectX::SimpleMath::Quaternion TransformComponent::GetRotation() {
	return DirectX::SimpleMath::Quaternion();
}

void TransformComponent::SetRotation(DirectX::SimpleMath::Quaternion rotation) {

}
