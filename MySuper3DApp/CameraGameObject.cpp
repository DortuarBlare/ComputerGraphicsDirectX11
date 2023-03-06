#include "pch.h"
#include "CameraGameObject.h"
#include "TransformComponent.h"

void CameraGameObject::Initialize() {
    GameObject::Initialize();
    Game::instance->inputDevice->MouseMove.AddRaw(this, &CameraGameObject::MouseEventHandler);

    velocity = 5.0f;
    transform->localPosition->y += 10;
}

void CameraGameObject::Update() {
    GameObject::Update();

    Matrix rotationMatrix = Matrix::CreateFromYawPitchRoll(yaw, pitch, 0);

    Vector3 forward = Vector3::Transform(Vector3::Forward, rotationMatrix);
    Vector3 right = Vector3::Transform(Vector3::Right, rotationMatrix);

    if (Game::instance->inputDevice->IsKeyDown(Keys::A))
        *transform->localPosition -= velocity * Game::instance->deltaTime * right;
    if (Game::instance->inputDevice->IsKeyDown(Keys::D))
        *transform->localPosition += velocity * Game::instance->deltaTime * right;
    if (Game::instance->inputDevice->IsKeyDown(Keys::W))
        *transform->localPosition += velocity * Game::instance->deltaTime * forward;
    if (Game::instance->inputDevice->IsKeyDown(Keys::S))
        *transform->localPosition -= velocity * Game::instance->deltaTime * forward;

    if (Game::instance->inputDevice->IsKeyDown(Keys::Space))
        *transform->localPosition += velocity * Game::instance->deltaTime * Vector3::Up;
    if (Game::instance->inputDevice->IsKeyDown(Keys::LeftShift))
        *transform->localPosition -= velocity * Game::instance->deltaTime * Vector3::Up;

    Vector3 target = *transform->localPosition +
        Vector3::Transform(
            Vector3::Forward,
            Matrix::CreateFromYawPitchRoll(yaw, pitch, 0)
        );

    /*Vector3 target = *transform->localPosition +
        Vector3::Transform(
            Vector3::Forward,
            Matrix::CreateFromQuaternion(*transform->localRotation)
        );*/

    Vector3 up = 
        Vector3::Transform(
            Vector3::Up,
            Matrix::CreateFromQuaternion(*transform->localRotation)
        );

    viewMatrix = Matrix::CreateLookAt(
        *transform->localPosition,
        target,
        up
    );

    if (perspective)
        projectionMatrix = CreatePerspectiveMatrix();
    else
        projectionMatrix = CreateOrthographicMatrix();

    /*std::cout <<
        "Camera position: " <<
        transform->localPosition->x << ' ' <<
        transform->localPosition->y << ' ' <<
        transform->localPosition->z <<
        std::endl;*/
}

void CameraGameObject::FixedUpdate() {
    GameObject::FixedUpdate();
}

Matrix CameraGameObject::GetCameraMatrix() {
    return viewMatrix * projectionMatrix;
}

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

void CameraGameObject::MouseEventHandler(const InputDevice::MouseMoveEventArgs& mouseData) {
    /**transform->localRotation *=
        Quaternion::CreateFromYawPitchRoll(
            -mouseData.Offset.x * cameraRotationSpeed,
            -mouseData.Offset.y * cameraRotationSpeed,
            0
        );*/

    /**transform->localRotation =
        Quaternion::CreateFromAxisAngle(Vector3::Up, -mouseData.Offset.x * cameraRotationSpeed) *
        Quaternion::CreateFromAxisAngle(Vector3::Transform(
            Vector3::Right, Matrix::CreateFromQuaternion(*transform->localRotation)),
            -mouseData.Offset.y * cameraRotationSpeed
        ) *
        *transform->localRotation;*/

    yaw += -mouseData.Offset.x * cameraRotationSpeed;
    pitch += -mouseData.Offset.y * cameraRotationSpeed;

    if (pitch > DirectX::XM_PIDIV2 - 0.01)
        pitch = DirectX::XM_PIDIV2 - 0.01;
    if (pitch < -DirectX::XM_PIDIV2 + 0.01)
        pitch = -DirectX::XM_PIDIV2 + 0.01;

    if (velocity + mouseData.WheelDelta / 10 > 0)
        velocity += mouseData.WheelDelta / 10;
}
