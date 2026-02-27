#include <camera.hpp>
#include <math.h>
#include <iostream>

namespace EcoSim
{
    Camera::Camera()
    {
        pos = Vector2();
    }
    Camera::Camera(Vector2 pos)
    {
        this->pos = pos;
    }

    Camera::~Camera() {}

    Vector2 Camera::GetGlobalToLocal(Vector2 pos)
    {
        return Vector2(pos.x - this->pos.x, pos.y - this->pos.y);
    }

    Vector2 Camera::GetLocalToGlobal(Vector2 pos)
    {
        return Vector2(pos.x + this->pos.x, pos.y + this->pos.y);
    }

    void Camera::SetZoom(float target)
    {
        // clamp da ne ode u ludilo
        if (target < 0.1f)
            target = 0.1f;
        if (target > 5.0f)
            target = 5.0f;

        targetZoom = target;
    }

    void Camera::Update(float deltaTime)
    {
        // exponential smoothing (najlepši osećaj)
        zoom += (targetZoom - zoom) * zoomSpeed * deltaTime;
    }

    float Camera::GetZoom() const
    {
        return zoom;
    }

    float Camera::GetTargetZoom() const
    {
        return targetZoom;
    }

}
