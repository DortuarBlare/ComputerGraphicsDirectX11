#include "pch.h"
#include "CameraGameObject.h"
#include "TransformComponent.h"

void CameraGameObject::Initialize() {
    GameObject::Initialize();
    Game::Instance()->inputDevice->MouseMove.AddRaw(this, &CameraGameObject::MouseEventHandler);

    velocity = 5.0f;
    orbitOffset = *transform->localPosition;
}

void CameraGameObject::Update() {
    GameObject::Update();

    if (orbitMode && transform->parent) {
        *transform->localPosition = *transform->parent->localPosition + orbitOffset;
        target = *transform->parent->localPosition;
    }
    else {
        target = *transform->localPosition +
            Vector3::Transform(
                Vector3::Forward,
                Matrix::CreateFromYawPitchRoll(yaw, pitch, 0)
            );
        up = Vector3::Transform(
            Vector3::Up,
            Matrix::CreateFromYawPitchRoll(yaw, pitch, 0)
        );
    }

    viewMatrix = CreateViewMatrix();

    if (perspective)
        projectionMatrix = CreatePerspectiveMatrix();
    else
        projectionMatrix = CreateOrthographicMatrix();
}


void CameraGameObject::AttachTo(std::shared_ptr<TransformComponent> transform) {
    orbitMode = true;
    this->transform->parent = transform;

    orbitOffset = 5.0f *
        Vector3::Transform(
            Vector3::Forward + Vector3::Up,
            Matrix::CreateFromYawPitchRoll(yaw, pitch, 0)
        );

    up = Vector3::Up;
}

void CameraGameObject::Detach() {
    if (transform->parent) {
        orbitMode = false;
        transform->parent = nullptr;
    }
}


Matrix CameraGameObject::GetCameraMatrix() {
    return viewMatrix * projectionMatrix;
}

Vector3 CameraGameObject::Forward() {
    return Vector3::Transform(Vector3::Forward, Matrix::CreateFromYawPitchRoll(yaw, pitch, 0));
}

Vector3 CameraGameObject::OrbitForwardXZ() {
    Vector3 orbitOffsetWithoutY = orbitOffset;
    orbitOffsetWithoutY.y = 0;

    Vector3 result = Vector3::Forward - orbitOffsetWithoutY;
    result.Normalize();

    return result;
}

Vector3 CameraGameObject::OrbitRightXZ() {
    Vector3 orbitOffsetWithoutY = orbitOffset;
    orbitOffsetWithoutY.y = 0;
    orbitOffsetWithoutY.Normalize();

    Vector3 result = orbitOffsetWithoutY.Cross(Vector3::Up);
    result.Normalize();

    return result;
}

Vector3 CameraGameObject::Right() {
    return Vector3::Transform(Vector3::Right, Matrix::CreateFromYawPitchRoll(yaw, pitch, 0));
}

Matrix CameraGameObject::CreateViewMatrix() {
    return Matrix::CreateLookAt(*transform->localPosition, target, up);
}

Matrix CameraGameObject::CreatePerspectiveMatrix() {
    float aspectRatio =
        static_cast<float>(Game::Instance()->renderSystem->display->GetClientWidth()) /
        Game::Instance()->renderSystem->display->GetClientHeight();

    return Matrix::CreatePerspectiveFieldOfView(fov, aspectRatio, nearPlane, farPlane);
}

Matrix CameraGameObject::CreateOrthographicMatrix() {
    return
        Matrix::CreateOrthographic(
            static_cast<float>(Game::Instance()->renderSystem->display->GetClientWidth()) / 50,
            static_cast<float>(Game::Instance()->renderSystem->display->GetClientHeight()) / 50,
            nearPlane,
            farPlane
        );
}


void CameraGameObject::MouseEventHandler(const InputDevice::MouseMoveEventArgs& mouseData) {
    if (!orbitMode) {
        yaw += -mouseData.Offset.x * rotationSpeed;
        pitch += -mouseData.Offset.y * rotationSpeed;

        if (pitch > DirectX::XM_PIDIV2 - 0.01)
            pitch = DirectX::XM_PIDIV2 - 0.01;
        if (pitch < -DirectX::XM_PIDIV2 + 0.01)
            pitch = -DirectX::XM_PIDIV2 + 0.01;

        if (velocity + mouseData.WheelDelta / 10 > 0)
            velocity += mouseData.WheelDelta / 10;
    }
    else {
        Quaternion quaternionFromMouseInput =
            Quaternion::CreateFromAxisAngle(Vector3::Up, -0.005f * mouseData.Offset.x) *
            Quaternion::CreateFromAxisAngle(orbitOffset.Cross(Vector3::Up), 0.005f * mouseData.Offset.y);
        orbitOffset = Vector3::Transform(orbitOffset, Matrix::CreateFromQuaternion(quaternionFromMouseInput));
        up = Vector3::Transform(Vector3::Up, Matrix::CreateFromQuaternion(quaternionFromMouseInput));

        // Changing the distance to the planet
        orbitOffset *= 1 - orbitApproximationSpeed * mouseData.WheelDelta;
    }
}
