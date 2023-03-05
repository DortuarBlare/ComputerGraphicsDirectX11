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
	if (parent) {
		DirectX::SimpleMath::Vector4 temp =
			DirectX::SimpleMath::Vector4::Transform(
				DirectX::SimpleMath::Vector4(localPosition->x, localPosition->y, localPosition->z, 1.0f),
				parent->GetModel()
			);

		return DirectX::SimpleMath::Vector3(temp.x, temp.y, temp.z);
	}

	return *localPosition;
}

void TransformComponent::SetPosition(DirectX::SimpleMath::Vector3 position) {

}

DirectX::SimpleMath::Quaternion TransformComponent::GetRotation() {
	if (parent)
		return parent->GetRotation() * *localRotation;

	return *localRotation;
}

void TransformComponent::SetRotation(DirectX::SimpleMath::Quaternion rotation) {

}

DirectX::SimpleMath::Matrix TransformComponent::GetLocalModel() {
	return DirectX::SimpleMath::Matrix::CreateFromQuaternion(*localRotation) * DirectX::SimpleMath::Matrix::CreateTranslation(*localPosition);
}

DirectX::SimpleMath::Matrix TransformComponent::GetModel() {
	return !parent ? GetLocalModel() : parent->GetModel() * GetLocalModel();
}

DirectX::SimpleMath::Vector3 TransformComponent::LocalForward() {
	return *localRotation * DirectX::SimpleMath::Vector3::Forward;
}

DirectX::SimpleMath::Vector3 TransformComponent::LocalUp() {
	return *localRotation * DirectX::SimpleMath::Vector3::Up;
}

DirectX::SimpleMath::Vector3 TransformComponent::LocalRight() {
	return *localRotation * DirectX::SimpleMath::Vector3::Right;
}

DirectX::SimpleMath::Vector3 TransformComponent::Forward() {
	return GetRotation() * DirectX::SimpleMath::Vector3::Forward;
}

DirectX::SimpleMath::Vector3 TransformComponent::Up() {
	return GetRotation() * DirectX::SimpleMath::Vector3::Up;
}

DirectX::SimpleMath::Vector3 TransformComponent::Right() {
	return GetRotation() * DirectX::SimpleMath::Vector3::Right;
}
