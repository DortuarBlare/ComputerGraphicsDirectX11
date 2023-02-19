#include "Game.h"
#include "PingPongGame.h"
#include "SquareRenderComponent.h"

int main() {
	//PingPongGame::CreateInstance(L"Ping Pong", 1920, 1080, false);
	PingPongGame::CreateInstance(L"Ping Pong", 1280, 720, true);
	PingPongGame* game = dynamic_cast<PingPongGame*>(Game::instance);
	
	GameObject go1 = {};
	SquareRenderComponent tc(game->leftPlayerOffset);

	// First square
	tc.points.push_back(DirectX::XMFLOAT4(-0.8f, 0.5f, 0.5f, 1.0f)); // Position Vertex 1
	tc.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color Vertex 1
	tc.points.push_back(DirectX::XMFLOAT4(-1.0f, -0.5f, 0.5f, 1.0f)); // Position Vertex 2
	tc.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color Vertex 2
	tc.points.push_back(DirectX::XMFLOAT4(-0.8f, -0.5f, 0.5f, 1.0f)); // Position Vertex 3
	tc.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color Vertex 3
	tc.points.push_back(DirectX::XMFLOAT4(-1.0f, 0.5f, 0.5f, 1.0f)); // Position Vertex 4
	tc.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color Vertex 4

	go1.components.push_back(&tc);

	GameObject go2 = {};
	SquareRenderComponent tc2(game->rightPlayerOffset);

	// Second square
	tc2.points.push_back(DirectX::XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f)); // Position Vertex 1
	tc2.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color Vertex 1
	tc2.points.push_back(DirectX::XMFLOAT4(0.8f, -0.5f, 0.5f, 1.0f)); // Position Vertex 2
	tc2.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color Vertex 2
	tc2.points.push_back(DirectX::XMFLOAT4(1.0f, -0.5f, 0.5f, 1.0f)); // Position Vertex 3
	tc2.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color Vertex 3
	tc2.points.push_back(DirectX::XMFLOAT4(0.8f, 0.5f, 0.5f, 1.0f)); // Position Vertex 4
	tc2.points.push_back(DirectX::XMFLOAT4(0.67f, 0.9f, 0.76f, 1.0f)); // Color Vertex 4

	go1.components.push_back(&tc2);

	PingPongGame::instance->gameObjects.push_back(&go1);
	PingPongGame::instance->gameObjects.push_back(&go2);
	PingPongGame::instance->Run();
}
