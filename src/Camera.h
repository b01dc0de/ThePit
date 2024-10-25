#ifndef THEPIT_CAMERA_H
#define THEPIT_CAMERA_H

#include "Common.h"

namespace thepit
{
    // Perspective camera
    struct CameraP
    {
        HMM_Mat4 mvp{};

        void LookAt(const HMM_Vec3& in_cam_pos, const HMM_Vec3& in_lookat_obj);
    };

    extern const HMM_Vec3 cam_global_up;
    extern const float cam_fov_degrees;
}

#endif // THEPIT_CAMERA_H