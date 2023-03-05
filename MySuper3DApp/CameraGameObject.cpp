#include "pch.h"
#include "CameraGameObject.h"
#include "TransformComponent.h"

void CameraGameObject::CreatePerspectiveFieldOFView() {
    projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
        fov,
        static_cast<float>(Game::instance->GetDisplay()->GetClientWidth()) / Game::instance->GetDisplay()->GetClientHeight(),
        nearPlane,
        farPlane
    );
}

void CameraGameObject::CreateOrthographic() {
    projectionMatrix = DirectX::SimpleMath::Matrix::CreateOrthographic(
        Game::instance->GetDisplay()->GetClientWidth() / 50,
        Game::instance->GetDisplay()->GetClientHeight() / 50,
        nearPlane,
        farPlane
    );
}

void CameraGameObject::Initialize() {
    GameObject::Initialize();
    //Game::instance->inputDevice->MouseMove.AddRaw(this, &CameraGameObject::MouseEventHandler, 10);
    velocity = 5.0f;
}

void CameraGameObject::Update() {
    GameObject::Update();
    
    
    if (Game::instance->inputDevice->IsKeyDown(Keys::Right))
        yaw += 0.1 * cameraRotationSpeed;
    if (Game::instance->inputDevice->IsKeyDown(Keys::Left))
        yaw -= 0.1 * cameraRotationSpeed;
    if (Game::instance->inputDevice->IsKeyDown(Keys::Up))
        pitch += 0.1 * cameraRotationSpeed;
    if (Game::instance->inputDevice->IsKeyDown(Keys::Down))
        pitch -= 0.1 * cameraRotationSpeed;

    if (Game::instance->inputDevice->IsKeyDown(Keys::A))
        *transform->localPosition += velocity * Game::instance->deltaTime * DirectX::SimpleMath::Vector3::Left;
    if (Game::instance->inputDevice->IsKeyDown(Keys::D))
        *transform->localPosition += velocity * Game::instance->deltaTime * DirectX::SimpleMath::Vector3::Right;
    if (Game::instance->inputDevice->IsKeyDown(Keys::W))
        *transform->localPosition += velocity * Game::instance->deltaTime * DirectX::SimpleMath::Vector3::Forward;
    if (Game::instance->inputDevice->IsKeyDown(Keys::S))
        *transform->localPosition += velocity * Game::instance->deltaTime * DirectX::SimpleMath::Vector3::Backward;

    if (Game::instance->inputDevice->IsKeyDown(Keys::Space))
        *transform->localPosition += velocity * Game::instance->deltaTime * DirectX::SimpleMath::Vector3::Up;
    if (Game::instance->inputDevice->IsKeyDown(Keys::LeftShift))
        *transform->localPosition -= velocity * Game::instance->deltaTime * DirectX::SimpleMath::Vector3::Up;

    *transform->localRotation =
        DirectX::SimpleMath::Quaternion(
            DirectX::SimpleMath::Vector3::Transform(
                DirectX::SimpleMath::Vector3::Backward,
                DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(yaw, pitch, 0)
            ),
            0.0f
        );

    viewMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(
        *transform->localPosition,
        transform->localRotation->ToEuler(),
        DirectX::SimpleMath::Vector3::Up
    );

    if (perspective)
        CreatePerspectiveFieldOFView();
    else
        CreateOrthographic();
}

void CameraGameObject::FixedUpdate() {
    GameObject::FixedUpdate();
}

DirectX::SimpleMath::Matrix CameraGameObject::GetCameraMatrix() {
    return viewMatrix * projectionMatrix;
}

//void CameraGameObject::MouseEventHandler(const InputDevice::MouseMoveEventArgs& mouseData, int payload) {
//    yaw += -mouseData.Offset.x * cameraRotationSpeed;
//    pitch += mouseData.Offset.y * cameraRotationSpeed;
//
//    if (pitch > DirectX::XM_PIDIV2 - 0.01)
//        pitch = DirectX::XM_PIDIV2 - 0.01;
//    if (pitch < -DirectX::XM_PIDIV2 + 0.01)
//        pitch = -DirectX::XM_PIDIV2 + 0.01;
//}
