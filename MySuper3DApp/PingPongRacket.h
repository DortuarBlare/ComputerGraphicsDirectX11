#pragma once
#include "pch.h"
#include "PingPongGameObject.h"
#include "RectangleRenderComponent.h"

class PingPongRacket : public PingPongGameObject {
public:
	std::shared_ptr<RectangleRenderComponent> mesh;
	std::shared_ptr<DirectX::SimpleMath::Vector3> translateDirection;

	PingPongRacket();
	PingPongRacket(DirectX::SimpleMath::Vector3 position);

	void FixedUpdate() override;
};
