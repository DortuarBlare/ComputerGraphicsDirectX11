#pragma once
#include "GameObject.h"
#include "SphereRenderComponent.h"

using namespace DirectX::SimpleMath;

class KatamariDamacyGameObject : public GameObject {
private:
	std::shared_ptr<SphereRenderComponent> mesh;

public:
	Vector3 offsetFromParent;

	KatamariDamacyGameObject();

	void Initialize() override;
	void Update() override;

	void AttachTo(KatamariDamacyGameObject& other);
};
