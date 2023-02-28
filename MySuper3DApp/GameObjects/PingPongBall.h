#pragma once
#include "PingPongGameObject.h"

class PingPongBall : public PingPongGameObject {
public:
	std::shared_ptr<CircleRenderComponent> mesh;

	PingPongBall();
	PingPongBall(DirectX::SimpleMath::Vector4 position);
};
