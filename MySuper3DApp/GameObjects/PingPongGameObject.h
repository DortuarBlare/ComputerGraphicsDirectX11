#pragma once
#include "GameObject.h"
#include "Components/Render/RectangleRenderComponent.h"
#include "Components/Render/CircleRenderComponent.h"
#include "Components/Colliders/BoxColliderComponent.h"

class PingPongGameObject : public GameObject {
public:
	std::shared_ptr<BoxColliderComponent> collider;

	PingPongGameObject();
	PingPongGameObject(DirectX::SimpleMath::Vector4 position);

	virtual void FixedUpdate();

	void Reflect(BoxColliderComponent boxCollider);
	void SetPosition(DirectX::SimpleMath::Vector4 newPosition) override;
	void Translate(DirectX::SimpleMath::Vector4 translation) override;
};
