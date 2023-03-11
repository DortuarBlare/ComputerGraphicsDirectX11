#include "pch.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent() {
	localPosition = std::make_shared<Vector3>(Vector3::Zero);
	localRotation = std::make_shared<Quaternion>(Quaternion::Identity);
	scale = std::make_shared<Vector3>(Vector3::One);
}

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

void TransformComponent::SetPosition(Vector3 position) {
	if (!parent)
		*localPosition = position;
	else {
		Vector4 temp =
			Vector4::Transform(
				Vector4(position.x, position.y, position.z, 1.0f),
				parent->GetModel()
			);

		*localPosition = Vector3(temp.x, temp.y, temp.z);
	}
}

// Moves the position in the direction and distance of "translation"
void TransformComponent::Translate(Vector3 translation) {
	*localPosition += translation;
}

Quaternion TransformComponent::GetRotation() {
	if (parent)
		return parent->GetRotation() * (*localRotation);

	return *localRotation;
}

void TransformComponent::SetRotation(Quaternion rotation) {
	*localRotation = rotation;
}

Matrix TransformComponent::GetLocalModel() {
	return Matrix::CreateScale(*scale) * Matrix::CreateFromQuaternion(*localRotation) * Matrix::CreateTranslation(*localPosition);
}

Matrix TransformComponent::GetModel() {
	return !parent ? GetLocalModel() : parent->GetModel() * GetLocalModel();
}

Matrix TransformComponent::GetLocalView() {
	/*Matrix view = Matrix::CreateFromQuaternion(*localRotation).Transpose();
	view._13 = -localPosition->x * view._11 - localPosition->y * view._12 - localPosition->z * view._13;
	view._23 = -localPosition->x * view._21 - localPosition->y * view._22 - localPosition->z * view._23;
	view._33 = -localPosition->x * view._31 - localPosition->y * view._32 - localPosition->z * view._33;
	return view;*/

	return Matrix::CreateFromQuaternion(*localRotation).Transpose() * Matrix::CreateTranslation(*localPosition);
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
	return Vector3::Transform(Vector3::Forward, GetRotation());
}

Vector3 TransformComponent::Up() {
	return GetRotation() * Vector3::Up;
}

Vector3 TransformComponent::Right() {
	return GetRotation() * Vector3::Right;
}
