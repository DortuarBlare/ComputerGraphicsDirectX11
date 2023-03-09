#include "pch.h"
#include "KatamariDamacyGameObject.h"

KatamariDamacyGameObject::KatamariDamacyGameObject() {
	mesh = std::make_shared<SphereRenderComponent>(
		D3D11_FILL_SOLID,
		1.5f,
		32,
		32,
		Color(1.0f, 1.0f, 1.0f),
		Color(0.5f, 0.5f, 0.5f)
	);
}

void KatamariDamacyGameObject::Initialize() {
	AddComponent(mesh);
	GameObject::Initialize();
}
