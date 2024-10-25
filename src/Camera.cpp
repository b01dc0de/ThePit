#include "Camera.h"

namespace thepit
{
    extern const HMM_Vec3 cam_global_up = { 0.0f, 1.0f, 0.0f };
    extern const float cam_fov_degrees = 61.5f;

    void CameraP::LookAt(const HMM_Vec3& in_cam_pos, const HMM_Vec3& in_lookat_obj)
    {
        const float aspect_ratio = sapp_widthf() / sapp_heightf();
        const float z_near = 0.1f;
        const float z_far = 10.0f;

        HMM_Mat4 proj = HMM_Perspective_RH_ZO(cam_fov_degrees, aspect_ratio, z_near, z_far);
        HMM_Mat4 view = HMM_LookAt_RH(in_cam_pos, in_lookat_obj, cam_global_up);
        mvp = proj * view;
    }
}