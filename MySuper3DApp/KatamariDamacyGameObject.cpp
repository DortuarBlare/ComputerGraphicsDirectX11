#include "pch.h"
#include "KatamariDamacyGameObject.h"
#include "TransformComponent.h"

KatamariDamacyGameObject::KatamariDamacyGameObject() {
	mesh = std::make_shared<MeshRenderComponent>(
		"Models/LegoBrick.fbx",
		L"Textures/LegoBrick.png"
	);

	collider = std::make_shared<SphereColliderComponent>(
		*transform->localPosition,
		1.5f
	);
}

void KatamariDamacyGameObject::Initialize() {
	AddComponent(mesh);
	AddComponent(collider);

	GameObject::Initialize();
}

void KatamariDamacyGameObject::Update() {
	GameObject::Update();

	/*if (transform->parent) {
		*transform->localPosition =
			*transform->parent->localPosition +
			Vector3::Transform(offsetFromParent, *transform->parent->localRotation);

		*transform->localRotation = *transform->parent->localRotation;
	}*/
}

void KatamariDamacyGameObject::AttachTo(KatamariDamacyGameObject& other) {
	transform->parent = other.transform;
	offsetFromParent = *transform->localPosition - *transform->parent->localPosition;

	offsetFromParent.Normalize();
	offsetFromParent *= other.collider->boundingSphere->Radius * 2;
	collider->enabled = false;
}
