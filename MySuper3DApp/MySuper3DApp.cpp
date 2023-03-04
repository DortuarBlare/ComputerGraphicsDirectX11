#include "pch.h"
#include "PingPongGame.h"

int main() {
	PingPongGame::CreateInstance(L"Ping Pong", 1000, 1000, true);
	PingPongGame::instance->Run();
}
