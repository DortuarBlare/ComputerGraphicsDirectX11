#pragma once
#include "GameObject.h"
#include "SphereRenderComponent.h"
#include "SphereColliderComponent.h"

using namespace DirectX::SimpleMath;

class KatamariDamacyGameObject : public GameObject {
public:
	std::shared_ptr<SphereRenderComponent> mesh;
	std::shared_ptr<SphereColliderComponent> collider;

	Vector3 offsetFromParent;

	KatamariDamacyGameObject();

	void Initialize() override;
	void Update() override;

	void AttachTo(KatamariDamacyGameObject& other);
};
