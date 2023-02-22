#pragma once
#include "ColliderComponent.h"

class BoxColliderComponent : public ColliderComponent {
private:
	std::shared_ptr<DirectX::BoundingBox> boundingBox;

public:
	BoxColliderComponent();
	BoxColliderComponent(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 extents);

	void Initialize();
	void Update();
	void FixedUpdate();
	void Draw();
	void Reload();
	void DestroyResources();
};
