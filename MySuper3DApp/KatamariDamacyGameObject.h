#pragma once
#include "GameObject.h"
#include "MeshRenderComponent.h"
#include "SphereColliderComponent.h"
#include "SphereRenderComponent.h"

using namespace DirectX::SimpleMath;

class KatamariDamacyGameObject : public GameObject {
public:
	std::shared_ptr<MeshRenderComponent> mesh;
	std::shared_ptr<SphereColliderComponent> collider;
	std::shared_ptr<SphereRenderComponent> colliderDebugSphere;

	float targetRadius;

	KatamariDamacyGameObject(std::string modelFileName, LPCWSTR textureFileName, float colliderRadius);
	KatamariDamacyGameObject(std::string modelFileName, LPCWSTR textureFileName, float colliderRadius, float importScale);
	KatamariDamacyGameObject(std::string modelFileName, LPCWSTR textureFileName, float colliderRadius, float importScale, Vector3 importTranslation);

	void Initialize() override;
	void Update() override;

	void AttachTo(std::shared_ptr<TransformComponent>& parentTransform);
};
