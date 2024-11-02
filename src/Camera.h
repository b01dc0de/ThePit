#ifndef THEPIT_CAMERA_H
#define THEPIT_CAMERA_H

#include "Common.h"

namespace ThePit
{
    // Perspective camera
    struct CameraP
    {
        HMM_Mat4 vp{};

        void LookAt(const HMM_Vec3& in_cam_pos, const HMM_Vec3& in_lookat_obj);
    };

    static const v3 default_cam_pos{ 0.0f, 0.0f, 0.0f };
    static const v3 default_look_dir{ 0.0f, 0.0f, 1.0f };
    static const float default_cam_move_speed = 0.25f;
    static const float default_cam_turn_speed = 0.0125f;
    struct FPSView
    {
        v3 cam_pos;

        v3 up;
        v3 dir;
        v3 right;

        float fov_degrees = 45.0f;
        float near_z = 0.1f;
        float far_z = 1000.0f;

        CameraP cam;

        HMM_Mat4 GetMVP();
        void UpdateCamera();
        void Init(const v3& in_cam_pos = default_cam_pos, const v3& in_lookat_obj = default_look_dir);
        void UpdateState();
    };

    extern const HMM_Vec3 cam_global_up;
    extern const float cam_fov_degrees;
} // namespace ThePit

#endif // THEPIT_CAMERA_H