#pragma once
#include "GameObject.h"
#include "MeshRenderComponent.h"
#include "SphereColliderComponent.h"

using namespace DirectX::SimpleMath;

class KatamariDamacyGameObject : public GameObject {
public:
	std::shared_ptr<MeshRenderComponent> mesh;
	std::shared_ptr<SphereColliderComponent> collider;

	KatamariDamacyGameObject(std::string modelFileName, LPCWSTR textureFileName, float colliderRadius);
	KatamariDamacyGameObject(std::string modelFileName, LPCWSTR textureFileName, float colliderRadius, float importScale);

	void Initialize() override;
	void Update() override;
};
