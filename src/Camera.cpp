#include "Camera.h"
#include "Input.h"

namespace ThePit
{
    extern const HMM_Vec3 cam_global_up = { 0.0f, 1.0f, 0.0f };
    extern const float cam_fov_degrees = 61.5f;

    void CameraP::LookAt(const HMM_Vec3& in_cam_pos, const HMM_Vec3& in_lookat_obj)
    {
        const float aspect_ratio = sapp_widthf() / sapp_heightf();
        const float z_near = 0.1f;
        const float z_far = 1000.0f;

        HMM_Mat4 proj = HMM_Perspective_RH_NO(cam_fov_degrees, aspect_ratio, z_near, z_far);
        HMM_Mat4 view = HMM_LookAt_RH(in_cam_pos, in_lookat_obj, cam_global_up);
        vp = proj * view;
    }

    HMM_Mat4 FPSView::GetMVP()
    {
        return cam.vp;
    }

    void FPSView::UpdateCamera()
    {
        v3 lookat_obj = cam_pos + dir;
        cam.LookAt(cam_pos, lookat_obj);
    }

    void FPSView::Init(const v3& in_cam_pos, const v3& in_lookdir)
    {
        fov_degrees = 45.0f;
        near_z = 0.1f;
        far_z = 1000.0f;

        cam_pos = in_cam_pos;

        dir = in_lookdir;
        dir = HMM_Norm(dir);
        right = HMM_Cross(cam_global_up, dir);
        right = HMM_Norm(right);
        up = HMM_Cross(dir, right);
        up = HMM_Norm(up);

        UpdateCamera();
    }

    void FPSView::UpdateState()
    {
        bool w_button_down = Input::GetButtonState(SAPP_KEYCODE_W);
        bool a_button_down = Input::GetButtonState(SAPP_KEYCODE_A);
        bool s_button_down = Input::GetButtonState(SAPP_KEYCODE_S);
        bool d_button_down = Input::GetButtonState(SAPP_KEYCODE_D);

        v3 forward{ dir.X, 0.0f, dir.Z };
        v3 left{ -right.X, 0.0f, -right.Z };

        // Update state from keyboard input
        if (w_button_down != s_button_down)
        {
            if (w_button_down) { cam_pos += forward * default_cam_move_speed; }
            else if (s_button_down) { cam_pos -= forward * default_cam_move_speed; }
        }
        if (a_button_down != d_button_down)
        {
            if (a_button_down) { cam_pos += left * default_cam_move_speed; }
            else if (d_button_down) { cam_pos -= left * default_cam_move_speed; }
        }

        // Update state from mouse input
        {
            float dx = 0.0f, dy = 0.0f;
            Input::GetMouseDelta(dx, dy);

            m4 rotate = HMM_M4D(1.0f);
            if ((dx < 0.0f ? -dx : dx) > 0.0f)
            {
                rotate = rotate * HMM_Rotate_RH(dx * default_cam_turn_speed, cam_global_up);
            }
            if ((dy < 0.0f ? -dy : dy) > 0.0f)
            {
                rotate = rotate * HMM_Rotate_RH(dy * default_cam_turn_speed, -right);
            }
            v4 new_dir = HMM_Mul(rotate, v4{ dir.X, dir.Y, dir.Z, 0.0f });
            Init(cam_pos, new_dir.XYZ);
        }

        UpdateCamera();
    }
} // namespace ThePit