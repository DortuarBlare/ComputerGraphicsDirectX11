#include "Games/PingPongGame.h"

int main() {
	//PingPongGame::CreateInstance(L"Ping Pong", 1920, 1080, false);
	PingPongGame::CreateInstance(L"Ping Pong", 1280, 720, true);
	PingPongGame::instance->Run();
}
