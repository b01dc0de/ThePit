#include "Camera.h"
#include "Input.h"
#include "Engine.h"

namespace ThePit
{
    extern const glm::vec3 cam_global_up = { 0.0f, 1.0f, 0.0f };
    extern const float cam_fov_degrees = 61.5f;

    void CameraP::LookAt(const glm::vec3& in_cam_pos, const glm::vec3& in_lookat_obj)
    {
        const float z_near = 0.1f;
        const float z_far = 1000.0f;
        
        glm::mat4 proj = glm::perspectiveFovRH_NO(cam_fov_degrees, sapp_widthf(), sapp_heightf(), z_near, z_far);
        glm::mat4 view = glm::lookAtRH(in_cam_pos, in_lookat_obj, cam_global_up);
        vp = proj * view;
    }

    glm::mat4 FPSView::GetMVP()
    {
        return cam.vp;
    }

    void FPSView::UpdateCamera()
    {
        if(ThePit::Engine::GlobalState.lock_mouse) {
            glm::vec3 lookat_obj = cam_pos + dir;
            cam.LookAt(cam_pos, lookat_obj);
        }
    }

    void FPSView::Init(const glm::vec3& in_cam_pos, const glm::vec3& in_lookdir)
    {
        fov_degrees = 45.0f;
        near_z = 0.1f;
        far_z = 1000.0f;

        cam_pos = in_cam_pos;

        dir = in_lookdir;
        dir = glm::normalize(dir);
        right = glm::cross(cam_global_up, dir);
        right = glm::normalize(right);
        up = glm::cross(dir, right);
        up = glm::normalize(up);

        UpdateCamera();
    }

    void FPSView::UpdateState()
    {
        bool w_button_down = Input::GetButtonState(SAPP_KEYCODE_W);
        bool a_button_down = Input::GetButtonState(SAPP_KEYCODE_A);
        bool s_button_down = Input::GetButtonState(SAPP_KEYCODE_S);
        bool d_button_down = Input::GetButtonState(SAPP_KEYCODE_D);

        static bool god_mode_enabled = true;
        if (god_mode_enabled)
        {
            bool q_button_down = Input::GetButtonState(SAPP_KEYCODE_Q);
            bool e_button_down = Input::GetButtonState(SAPP_KEYCODE_E);

            glm::vec3 up{ 0.0f, 1.0f, 0.0f };

            if (q_button_down != e_button_down)
            {
                if (q_button_down) { cam_pos += up * default_cam_move_speed; }
                else if (e_button_down) { cam_pos -= up * default_cam_move_speed; }
            }
        }

        glm::vec3 forward = glm::normalize(glm::vec3 { dir.x, 0.0f, dir.z });
        glm::vec3 left = { -right.x, 0.0f, -right.z };

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

            glm::mat4 rotate = glm::mat4(1.0f);
            if ((dx < 0.0f ? -dx : dx) > 0.0f)
            {
                rotate = glm::rotate(rotate, dx * default_cam_turn_speed, cam_global_up);
            }
            if ((dy < 0.0f ? -dy : dy) > 0.0f)
            {
                rotate = glm::rotate(rotate, dy * default_cam_turn_speed, -right);
            }
            glm::vec4 new_dir = rotate * glm::vec4{ dir.x, dir.y, dir.z, 0.0f };
            Init(cam_pos, glm::vec3(new_dir));
        }

        UpdateCamera();
    }
} // namespace ThePit