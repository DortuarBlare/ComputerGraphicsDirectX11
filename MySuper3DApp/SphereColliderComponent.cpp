#include "pch.h"
#include "SphereColliderComponent.h"
#include "TransformComponent.h"

SphereColliderComponent::SphereColliderComponent(Vector3 center, float radius) {
	boundingSphere = std::make_shared<BoundingSphere>(center, radius);
}

void SphereColliderComponent::Initialize() {}

void SphereColliderComponent::Update() {
	boundingSphere->Center = *owner->transform->localPosition;
}

bool SphereColliderComponent::Intersects(SphereColliderComponent& other) {
	if (other.enabled)
		return boundingSphere->Intersects(*other.boundingSphere);
	
	return false;
}
