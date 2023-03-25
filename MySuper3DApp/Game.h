#pragma once
#include "pch.h"

#include "InputDevice.h"

#include "Time.h"
#include "RenderSystem.h"
#include "ShadowRenderSystem.h"
#include "GameObject.h"
#include "CameraGameObject.h"
#include "LightGameObject.h"

class InputDevice;
class ShadowRenderSystem;
class GameObject;
class CameraGameObject;

using namespace std::chrono;

class Game {
protected:
	static std::unique_ptr<Game> instance; // Singleton
	LPCWSTR	name;

	Game(LPCWSTR name);

	virtual void Initialize();
	virtual void Update();
	virtual void UpdateInternal();
	virtual void DestroyResources();

public:
	std::unique_ptr<RenderSystem> renderSystem;
	std::unique_ptr<ShadowRenderSystem> shadowRenderSystem;
	std::unique_ptr<InputDevice> inputDevice;
	std::unique_ptr<CameraGameObject> camera;
	std::unique_ptr<LightGameObject> lightGameObject;

	std::vector<std::shared_ptr<GameObject>> gameObjects;

	static std::unique_ptr<Game>& Instance();
	static void CreateInstance(LPCWSTR name);

	virtual void Run(int clientWidth, int clientHeight, bool fullscreen);
	void Exit();

	LRESULT MessageHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);