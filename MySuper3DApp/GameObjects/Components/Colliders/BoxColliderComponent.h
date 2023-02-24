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

	bool Intersects(DirectX::SimpleMath::Vector3 direction);

	DirectX::XMFLOAT3& GetCenter();
	DirectX::XMFLOAT3& GetExtents();
};