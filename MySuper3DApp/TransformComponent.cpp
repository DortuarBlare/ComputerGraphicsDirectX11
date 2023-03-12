#include "pch.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent() {
	localPosition = std::make_shared<Vector3>(Vector3::Zero);
	localRotation = std::make_shared<Quaternion>(Quaternion::Identity);
	scale = std::make_shared<Vector3>(Vector3::One);
}


// Moves the position in the direction and distance of "translation"
void TransformComponent::Translate(Vector3 translation) {
	*localPosition += translation;
}


Vector3 TransformComponent::GetPosition() {
	if (parent)
		return Vector3::Transform(*localPosition, parent->GetModel());

	return *localPosition;
}

void TransformComponent::SetPosition(Vector3 position) {
	if (parent)
		*localPosition = Vector3::Transform(position, parent->GetView());
	else
		*localPosition = position;
}


Quaternion TransformComponent::GetRotation() {
	if (parent)
		return parent->GetRotation() * (*localRotation);

	return *localRotation;
}

void TransformComponent::SetRotation(Quaternion rotation) {
	if (parent) {
		Quaternion quaternion;
		parent->GetRotation().Inverse(quaternion);
		*localRotation = rotation * quaternion;
	}
	else
		*localRotation = rotation;
}


Matrix TransformComponent::GetLocalModel() {
	return 
		Matrix::CreateScale(*scale) * 
		Matrix::CreateFromQuaternion(*localRotation) * 
		Matrix::CreateTranslation(*localPosition);
}

Matrix TransformComponent::GetModel() {
	if (parent)
		return GetLocalModel() * parent->GetModel();

	return GetLocalModel();
}

Matrix TransformComponent::GetLocalView() {
	return Matrix::CreateTranslation(-(*localPosition)) * Matrix::CreateFromQuaternion(*localRotation).Transpose();
}

Matrix TransformComponent::GetView() {
	if (parent)
		return parent->GetView() * GetLocalView();

	return GetLocalView();
}


Vector3 TransformComponent::LocalForward() {
	return Vector3::TransformNormal(Vector3::Forward, GetLocalModel());
}

Vector3 TransformComponent::LocalUp() {
	return Vector3::TransformNormal(Vector3::Up, GetLocalModel());
}

Vector3 TransformComponent::LocalRight() {
	return Vector3::TransformNormal(Vector3::Left, GetLocalModel());
}

Vector3 TransformComponent::Forward() {
	return Vector3::Transform(Vector3::Forward, GetRotation());
}

Vector3 TransformComponent::Up() {
	return Vector3::TransformNormal(Vector3::Up, GetModel());
}

Vector3 TransformComponent::Right() {
	return Vector3::TransformNormal(Vector3::Left, GetModel());
}
