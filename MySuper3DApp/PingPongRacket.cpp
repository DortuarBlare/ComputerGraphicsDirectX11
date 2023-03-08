#include "pch.h"
#include "PingPongRacket.h"

PingPongRacket::PingPongRacket() : PingPongGameObject() {
	translateDirection = std::make_shared<DirectX::SimpleMath::Vector3>();
}

void PingPongRacket::FixedUpdate() {
	if (*translateDirection != DirectX::SimpleMath::Vector3::Zero) {
		if (!collider->Intersects(*translateDirection)) {
			DirectX::SimpleMath::Vector3 finalDirection = { translateDirection->x, translateDirection->y, 0.0f };
			Translate(finalDirection * velocity * Time::DeltaTime());
		}
	}
}
