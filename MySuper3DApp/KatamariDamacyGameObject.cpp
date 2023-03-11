#include "pch.h"
#include "KatamariDamacyGameObject.h"
#include "TransformComponent.h"

KatamariDamacyGameObject::KatamariDamacyGameObject() {
	mesh = std::make_shared<SphereRenderComponent>(
		L"Textures/Player.png",
		1.5f,
		32,
		32
	);
}

void KatamariDamacyGameObject::Initialize() {
	AddComponent(mesh);
	GameObject::Initialize();
}

void KatamariDamacyGameObject::Update() {
	GameObject::Update();

	if (transform->parent) {
		*transform->localPosition =
			transform->parent->GetPosition() +
			Vector3::Transform(
				offsetFromParent,
				*transform->parent->localRotation
			);

		*transform->localRotation = *transform->parent->localRotation;
	}
}

void KatamariDamacyGameObject::AttachTo(KatamariDamacyGameObject& other) {
	transform->parent = other.transform;
	offsetFromParent = *transform->localPosition - *transform->parent->localPosition;
	offsetFromParent.Normalize();
	offsetFromParent *= 3.0f;
}
