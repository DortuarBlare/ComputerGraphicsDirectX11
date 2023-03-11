#pragma once
#include "ColliderComponent.h"

class SphereColliderComponent : public ColliderComponent {
public:
	std::shared_ptr<BoundingSphere> boundingSphere;

	SphereColliderComponent() = delete;
	SphereColliderComponent(Vector3 center, float radius);

	void Initialize();
	void Update();

	bool Intersects(SphereColliderComponent& other);
};
