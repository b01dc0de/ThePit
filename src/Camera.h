#ifndef THEPIT_CAMERA_H
#define THEPIT_CAMERA_H

#include "Common.h"

namespace ThePit
{
    // Perspective camera
    struct CameraP
    {
        glm::mat4 vp{};

        void LookAt(const glm::vec3& in_cam_pos, const glm::vec3& in_lookat_obj);
    };

    static const glm::vec3 default_cam_pos{ 0.0f, 0.0f, 0.0f };
    static const glm::vec3 default_look_dir{ 0.0f, 0.0f, 1.0f };
    static const float default_cam_move_speed = 0.25f;
    static const float default_cam_turn_speed = 0.0125f;
    struct FPSView
    {
        glm::vec3 cam_pos;

        glm::vec3 up;
        glm::vec3 dir;
        glm::vec3 right;

        float fov_degrees = 45.0f;
        float near_z = 0.1f;
        float far_z = 1000.0f;

        CameraP cam;

        glm::mat4 GetMVP();
        void UpdateCamera();
        void Init(const glm::vec3& in_cam_pos = default_cam_pos, const glm::vec3& in_lookat_obj = default_look_dir);
        void UpdateState();
    };

    extern const glm::vec3 cam_global_up;
    extern const float cam_fov_degrees;
} // namespace ThePit

#endif // THEPIT_CAMERA_H