#pragma once
#include "PingPongGameObject.h"

class PingPongRacket : public PingPongGameObject {
public:
	std::shared_ptr<RectangleRenderComponent> mesh;
	std::shared_ptr<DirectX::SimpleMath::Vector3> translateDirection;

	PingPongRacket();
	PingPongRacket(DirectX::SimpleMath::Vector4 position);

	void FixedUpdate() override;
};
