#pragma once
#include "pch.h"
#include "PingPongGameObject.h"
#include "CircleRenderComponent.h"

class PingPongBall : public PingPongGameObject {
public:
	std::shared_ptr<CircleRenderComponent> mesh;

	PingPongBall();
	PingPongBall(DirectX::SimpleMath::Vector4 position);
};
