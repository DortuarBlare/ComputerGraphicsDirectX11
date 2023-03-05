#include "pch.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent() {
	localPosition = std::make_shared<Vector3>(Vector3::Zero);
	localRotation = std::make_shared<Quaternion>(Quaternion::Identity);
}

void TransformComponent::Initialize() {}

void TransformComponent::Update() {}

void TransformComponent::FixedUpdate() {}

void TransformComponent::Draw() {}

void TransformComponent::Reload() {}

void TransformComponent::DestroyResources() {}

Vector3 TransformComponent::GetPosition() {
	if (parent) {
		Vector4 temp =
			Vector4::Transform(
				Vector4(localPosition->x, localPosition->y, localPosition->z, 1.0f),
				parent->GetModel()
			);

		return Vector3(temp.x, temp.y, temp.z);
	}

	return *localPosition;
}

void TransformComponent::SetPosition(Vector3 position) {}

Quaternion TransformComponent::GetRotation() {
	if (parent)
		return parent->GetRotation() * *localRotation;

	return *localRotation;
}

void TransformComponent::SetRotation(Quaternion rotation) {}

Matrix TransformComponent::GetLocalModel() {
	return Matrix::CreateFromQuaternion(*localRotation) * Matrix::CreateTranslation(*localPosition);
}

Matrix TransformComponent::GetModel() {
	return !parent ? GetLocalModel() : parent->GetModel() * GetLocalModel();
}

Vector3 TransformComponent::LocalForward() {
	return *localRotation * Vector3::Forward;
}

Vector3 TransformComponent::LocalUp() {
	return *localRotation * Vector3::Up;
}

Vector3 TransformComponent::LocalRight() {
	return *localRotation * Vector3::Right;
}

Vector3 TransformComponent::Forward() {
	return GetRotation() * Vector3::Forward;
}

Vector3 TransformComponent::Up() {
	return GetRotation() * Vector3::Up;
}

Vector3 TransformComponent::Right() {
	return GetRotation() * Vector3::Right;
}