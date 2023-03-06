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

void SolarSystemGameObject::FixedUpdate() {
	GameObject::FixedUpdate();

	if (transform->parent) {
		Vector3 offset =
			Vector3::Transform(
				*transform->localPosition,
				Matrix::CreateFromAxisAngle(
					rotateAroundAxis,
					rotateAroundSpeed * Game::instance->deltaTime
				)
			);

		*transform->localPosition = *transform->parent->localPosition/* + offset*/;
	}
	else {
		*transform->localPosition = 
			Vector3::Transform(
				*transform->localPosition,
				Matrix::CreateFromAxisAngle(
					rotateAroundAxis,
					rotateAroundSpeed * Game::instance->deltaTime
				)
			);
	}

	*transform->localRotation *= Quaternion::CreateFromAxisAngle(localRotationAxis, localRotationSpeed * Game::instance->deltaTime);
}

void SolarSystemGameObject::Configure() {
	AddComponent(mesh);

	if (transform->parent) 
		*transform->localPosition = *transform->parent->localPosition + Vector3::Forward * orbitRadius;
	else
		*transform->localPosition += Vector3::Forward * orbitRadius;
}
