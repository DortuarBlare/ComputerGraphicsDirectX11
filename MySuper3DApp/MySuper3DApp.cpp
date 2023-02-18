#include "Game.h"
#include "PingPongGame.h"
#include "TriangleComponent.h"

int main() {
	PingPongGame::CreateInstance(L"Ping Pong", 1280, 720, true);
	PingPongGame* game = dynamic_cast<PingPongGame*>(Game::instance);
	
	TriangleComponent tc(game->leftPlayerOffset);

	// First square
	tc.points.push_back(DirectX::XMFLOAT4(-0.8f, 0.5f, 0.5f, 1.0f)); // Position
	tc.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color

	tc.points.push_back(DirectX::XMFLOAT4(-1.0f, -0.5f, 0.5f, 1.0f)); // Position
	tc.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color

	tc.points.push_back(DirectX::XMFLOAT4(-0.8f, -0.5f, 0.5f, 1.0f)); // Position
	tc.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color

	tc.points.push_back(DirectX::XMFLOAT4(-1.0f, 0.5f, 0.5f, 1.0f)); // Position
	tc.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color

	// Second square
	tc.points.push_back(DirectX::XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f)); // Position
	tc.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color

	tc.points.push_back(DirectX::XMFLOAT4(0.8f, -0.5f, 0.5f, 1.0f)); // Position
	tc.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color

	tc.points.push_back(DirectX::XMFLOAT4(1.0f, -0.5f, 0.5f, 1.0f)); // Position
	tc.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color

	tc.points.push_back(DirectX::XMFLOAT4(0.8f, 0.5f, 0.5f, 1.0f)); // Position
	tc.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color

	PingPongGame::instance->components.push_back(&tc);
	//PingPongGame::instance->components.push_back(&tc2);
	PingPongGame::instance->Run();
}
