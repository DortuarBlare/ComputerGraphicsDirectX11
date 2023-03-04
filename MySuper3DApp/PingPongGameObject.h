#pragma once
#include "pch.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"

class PingPongGameObject : public GameObject {
public:
	std::shared_ptr<BoxColliderComponent> collider;

	PingPongGameObject();
	PingPongGameObject(DirectX::SimpleMath::Vector3 position);

	virtual void FixedUpdate();

	void Reflect(BoxColliderComponent boxCollider);
	void SetPosition(DirectX::SimpleMath::Vector3 newPosition) override;
	void Translate(DirectX::SimpleMath::Vector3 translation) override;
};
