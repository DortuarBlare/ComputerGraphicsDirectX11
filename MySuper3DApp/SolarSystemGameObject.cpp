#include "pch.h"
#include "SolarSystemGameObject.h"
#include "TransformComponent.h"

SolarSystemGameObject::SolarSystemGameObject(SolarSystemGameObjectDescription description) : GameObject() {
	this->localRotationSpeed = description.localRotationSpeed;
	this->localRotationAxis = description.localRotationAxis;

	this->rotateAroundSpeed = description.rotateAroundSpeed;

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
					Vector3::Up,
					rotateAroundSpeed * Game::instance->deltaTime
				)
			);

		std::cout << "Offset: " << offset.x << ' ' << offset.y << ' ' << offset.z << std::endl;

		*transform->localPosition = *transform->parent->localPosition + offset;
	}

	*transform->localRotation *= Quaternion::CreateFromAxisAngle(localRotationAxis, localRotationSpeed * Game::instance->deltaTime);
}

void SolarSystemGameObject::Configure() {
	AddComponent(mesh);

	/*if (transform->parent) 
		*transform->localPosition = *transform->parent->localPosition + Vector3::Forward * 2.5f;*/
}
