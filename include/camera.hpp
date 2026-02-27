#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <math.hpp>

namespace EcoSim
{
    class Camera
    {
    public:
        Camera();
        Camera(Vector2 pos);
        ~Camera();

        Vector2 GetGlobalToLocal(Vector2 pos);
        Vector2 GetLocalToGlobal(Vector2 pos);

        void SetZoom(float target);
        float GetZoom() const;
        float GetTargetZoom() const;

        void Update(float deltaTime);

        Vector2 pos;
        float zoomSpeed = 5.0f;

    protected:
        float zoom = 1.0f;
        float targetZoom = 5.0f;
    };
}

#endif