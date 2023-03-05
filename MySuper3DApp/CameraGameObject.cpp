#include "pch.h"
#include "CameraGameObject.h"
#include "TransformComponent.h"

Matrix CameraGameObject::CreatePerspectiveMatrix() {
    return
        Matrix::CreatePerspectiveFieldOfView(
            fov,
            static_cast<float>(Game::instance->GetDisplay()->GetClientWidth()) / Game::instance->GetDisplay()->GetClientHeight(),
            nearPlane,
            farPlane
        );
}

Matrix CameraGameObject::CreateOrthographicMatrix() {
    return
        Matrix::CreateOrthographic(
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
    *transform->localRotation = Quaternion::LookRotation(Vector3::Forward, Vector3::Up);
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
        *transform->localPosition += velocity * Game::instance->deltaTime * Vector3::Left;
    if (Game::instance->inputDevice->IsKeyDown(Keys::D))
        *transform->localPosition += velocity * Game::instance->deltaTime * Vector3::Right;
    if (Game::instance->inputDevice->IsKeyDown(Keys::W))
        *transform->localPosition += velocity * Game::instance->deltaTime * Vector3::Forward;
    if (Game::instance->inputDevice->IsKeyDown(Keys::S))
        *transform->localPosition += velocity * Game::instance->deltaTime * Vector3::Backward;

    if (Game::instance->inputDevice->IsKeyDown(Keys::Space))
        *transform->localPosition += velocity * Game::instance->deltaTime * Vector3::Up;
    if (Game::instance->inputDevice->IsKeyDown(Keys::LeftShift))
        *transform->localPosition -= velocity * Game::instance->deltaTime * Vector3::Up;

    // Change velocity
    // Normalize
    // rotMatrix.Forward() * velDirection.x + Vector3::Up * velDirection.y + rotMatrix.Right() * velDirection.z;
    // Normalize if has something
    // cameraPos = cameraPos * velDir * VelocityMagnitude * deltaTime
    // viewMatrix = createLookAt(cameraPos, cameraPos + rotMatrix + forward, vector3::up)

    /**transform->localRotation =
        DirectX::SimpleMath::Quaternion(
            DirectX::SimpleMath::Vector3::Transform(
                DirectX::SimpleMath::Vector3::Backward,
                DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(yaw, pitch, 0)
            ),
            0.0f
        );*/

    Vector3 target = *transform->localPosition +
        Vector3::Transform(
            Vector3::Backward,
            Matrix::CreateFromYawPitchRoll(yaw, pitch, 0)
        );

    viewMatrix = Matrix::CreateLookAt(
        *transform->localPosition,
        target,
        Vector3::Up
    );

    /*Matrix translationMatrix = Matrix::CreateTranslation(*transform->localPosition);
    Matrix rotationMatrix = Matrix::CreateFromQuaternion(*transform->localRotation);
    viewMatrix = (rotationMatrix * translationMatrix).Invert();*/

    if (perspective)
        projectionMatrix = CreatePerspectiveMatrix();
    else
        projectionMatrix = CreateOrthographicMatrix();

    std::cout <<
        "Camera position: " <<
        transform->localPosition->x << ' ' <<
        transform->localPosition->y << ' ' <<
        transform->localPosition->z <<
        std::endl;
}

void CameraGameObject::FixedUpdate() {
    GameObject::FixedUpdate();
}

Matrix CameraGameObject::GetCameraMatrix() {
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
