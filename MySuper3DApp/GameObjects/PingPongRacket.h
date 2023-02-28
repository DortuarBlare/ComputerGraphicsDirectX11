#pragma once
#include "PingPongGameObject.h"

class PingPongRacket : public PingPongGameObject {
public:
	std::shared_ptr<RectangleRenderComponent> mesh;

	PingPongRacket();
	PingPongRacket(DirectX::SimpleMath::Vector4 position);
};
