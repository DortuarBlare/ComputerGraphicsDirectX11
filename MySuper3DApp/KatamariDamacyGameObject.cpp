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

	colliderDebugSphere = std::make_shared<SphereRenderComponent>(
		L"Textures/Red.jpg",
		D3D11_FILL_WIREFRAME,
		colliderRadius,
		32,
		32
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

	colliderDebugSphere = std::make_shared<SphereRenderComponent>(
		L"Textures/Red.jpg",
		D3D11_FILL_WIREFRAME,
		colliderRadius,
		32,
		32
	);
}

KatamariDamacyGameObject::KatamariDamacyGameObject(std::string modelFileName, LPCWSTR textureFileName, float colliderRadius, float importScale, Vector3 importTranslation) {
	mesh = std::make_shared<MeshRenderComponent>(
		modelFileName,
		textureFileName,
		importScale,
		importTranslation
	);

	collider = std::make_shared<SphereColliderComponent>(
		*transform->localPosition,
		colliderRadius
	);

	colliderDebugSphere = std::make_shared<SphereRenderComponent>(
		L"Textures/Red.jpg",
		D3D11_FILL_WIREFRAME,
		colliderRadius,
		32,
		32
	);
}

void KatamariDamacyGameObject::Initialize() {
	AddComponent(mesh);
	AddComponent(collider);
	AddComponent(colliderDebugSphere);

	GameObject::Initialize();
}

void KatamariDamacyGameObject::Update() {
	GameObject::Update();
}

void KatamariDamacyGameObject::AttachTo(std::shared_ptr<TransformComponent>& parentTransform) {
	Vector3 position = transform->GetPosition();
	Quaternion rotation = transform->GetRotation();
	transform->parent = parentTransform;
	transform->SetPosition(position);
	transform->SetRotation(rotation);
	collider->enabled = false;
}
