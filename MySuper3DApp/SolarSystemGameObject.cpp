#include "pch.h"
#include "SolarSystemGameObject.h"
#include "TransformComponent.h"

SolarSystemGameObject::SolarSystemGameObject(SolarSystemGameObjectDescription description) : GameObject() {
	this->localRotationSpeed = description.localRotationSpeed;
	this->localRotationAxis = description.localRotationAxis;

	this->rotateAroundSpeed = description.rotateAroundSpeed;
	this->rotateAroundAxis = description.rotateAroundAxis;
	this->orbitRadius = description.orbitRadius;

	mesh = std::make_shared<SphereRenderComponent>(
		description.fillMode,
		description.radius,
		description.sliceCount,
		description.stackCount,
		description.topColor,
		description.bottomColor
	);
}

void SolarSystemGameObject::Initialize() {
	AddComponent(mesh);

	if (transform->parent) {
		offset = Vector3::Forward * orbitRadius;
		*transform->localPosition = *transform->parent->localPosition + offset;
	}
	else
		*transform->localPosition += Vector3::Forward * orbitRadius;

	GameObject::Initialize();
}

void SolarSystemGameObject::Update() {
	GameObject::Update();

	if (transform->parent) {
		offset =
			Vector3::Transform(
				offset,
				Matrix::CreateFromAxisAngle(
					rotateAroundAxis,
					rotateAroundSpeed * Time::DeltaTime()
				)
			);

		*transform->localPosition = *transform->parent->localPosition + offset;
	}
	else {
		*transform->localPosition = 
			Vector3::Transform(
				*transform->localPosition,
				Matrix::CreateFromAxisAngle(
					rotateAroundAxis,
					rotateAroundSpeed * Time::DeltaTime()
				)
			);
	}

	*transform->localRotation *= Quaternion::CreateFromAxisAngle(localRotationAxis, localRotationSpeed * Time::DeltaTime());
}
