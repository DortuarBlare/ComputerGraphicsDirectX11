#pragma once
#include "pch.h"
#include "ColliderComponent.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class BoxColliderComponent : public ColliderComponent {
private:
	std::shared_ptr<BoundingBox> boundingBox;

	Vector3 PointOnBounds(Vector3 direction);

public:
	std::vector<std::shared_ptr<GameObject>> noCollisionGameObjects;

	BoxColliderComponent();
	BoxColliderComponent(XMFLOAT3 center, XMFLOAT3 extents);

	void Initialize() override;
	void Update() override;

	bool Intersects(Vector3 translation);
	bool Intersects(Vector3 direction, float outDistance);

	XMFLOAT3& GetCenter();
	XMFLOAT3& GetExtents();
};
