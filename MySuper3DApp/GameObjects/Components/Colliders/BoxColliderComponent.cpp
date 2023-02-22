#include "BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent() {
	boundingBox = std::make_shared<DirectX::BoundingBox>();
}

BoxColliderComponent::BoxColliderComponent(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 extents) {
	boundingBox = std::make_shared<DirectX::BoundingBox>(center, extents);
}
