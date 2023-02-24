#pragma once
#include "GameObject.h"
#include "Components/Render/RectangleRenderComponent.h"
#include "Components/Colliders/BoxColliderComponent.h"

class PingPongGameObject : public GameObject {
public:
	std::shared_ptr<RectangleRenderComponent> mesh;
	std::shared_ptr<BoxColliderComponent> collider;

	PingPongGameObject();
	PingPongGameObject(DirectX::SimpleMath::Vector4 position);

	void Translate(DirectX::SimpleMath::Vector4 newPosition) override;
};
