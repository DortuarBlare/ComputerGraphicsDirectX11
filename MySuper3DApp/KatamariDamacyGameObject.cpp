#include "pch.h"
#include "KatamariDamacyGameObject.h"

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
