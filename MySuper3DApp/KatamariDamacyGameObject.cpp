#include "pch.h"
#include "KatamariDamacyGameObject.h"
#include "TransformComponent.h"

KatamariDamacyGameObject::KatamariDamacyGameObject(std::string modelFileName, LPCWSTR textureFileName, float colliderRadius) {
	mesh = std::make_shared<MeshRenderComponent>(
		modelFileName,
		textureFileName
	);

	collider = std::make_shared<SphereColliderComponent>(
		*transform->localPosition,
		colliderRadius
	);
}

KatamariDamacyGameObject::KatamariDamacyGameObject(std::string modelFileName, LPCWSTR textureFileName, float colliderRadius, float importScale) {
	mesh = std::make_shared<MeshRenderComponent>(
		modelFileName,
		textureFileName,
		importScale
	);

	collider = std::make_shared<SphereColliderComponent>(
		*transform->localPosition,
		colliderRadius
	);
}

void KatamariDamacyGameObject::Initialize() {
	AddComponent(mesh);
	AddComponent(collider);

	GameObject::Initialize();
}

void KatamariDamacyGameObject::Update() {
	GameObject::Update();
}
