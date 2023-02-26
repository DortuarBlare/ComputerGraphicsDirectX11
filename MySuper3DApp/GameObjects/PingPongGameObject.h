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

	void FixedUpdate() override;

	void Reflect(BoxColliderComponent forNormalVector);
	void SetPosition(DirectX::SimpleMath::Vector4 newPosition) override;
	void Translate(DirectX::SimpleMath::Vector4 translation) override;
};
