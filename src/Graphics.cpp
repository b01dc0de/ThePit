#include "Graphics.h"
#include "Engine.h"
#include "FileUtils.h"
#include "Geometry.h"
#include "DebugGraphics.h"

namespace ThePit
{
    void GetVxColorShaderDesc(sg_shader_desc& out_desc)
    {
        FileContentsT v_file{ "src/glsl/vxcolor_v.glsl", nullptr };
        FileContentsT f_file{ "src/glsl/vxcolor_f.glsl", nullptr };
        ReadFileContents(&v_file);
        ReadFileContents(&f_file);

        out_desc.attrs[0].name = "position";
        out_desc.attrs[1].name = "color0";
        out_desc.vs.source = (const char*)v_file.contents;
        out_desc.vs.entry = "main";
        out_desc.vs.uniform_blocks[0].size = sizeof(glm::mat4);
        out_desc.vs.uniform_blocks[0].layout = SG_UNIFORMLAYOUT_STD140;
        out_desc.vs.uniform_blocks[0].uniforms[0].name = "vs_params";
        out_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4;
        out_desc.vs.uniform_blocks[0].uniforms[0].array_count = 4;
        out_desc.fs.source = (const char*)f_file.contents;
        out_desc.fs.entry = "main";
        out_desc.label = "vxcolor";
    }

    void GetVxTextureShaderDesc(sg_shader_desc& out_desc)
    {
        FileContentsT v_file{ "src/glsl/vxtexture_v.glsl", nullptr };
        FileContentsT f_file{ "src/glsl/vxtexture_f.glsl", nullptr };
        ReadFileContents(&v_file);
        ReadFileContents(&f_file);

        out_desc.attrs[0].name = "pos";
        out_desc.attrs[1].name = "texcoord0";
        out_desc.vs.source = (const char*)v_file.contents;
        out_desc.vs.entry = "main";
        out_desc.vs.uniform_blocks[0].size = sizeof(glm::mat4);
        out_desc.vs.uniform_blocks[0].layout = SG_UNIFORMLAYOUT_STD140;
        out_desc.vs.uniform_blocks[0].uniforms[0].name = "vs_params";
        out_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4;
        out_desc.vs.uniform_blocks[0].uniforms[0].array_count = 4;
        out_desc.fs.source = (const char*)f_file.contents;
        out_desc.fs.entry = "main";
        out_desc.fs.images[0].used = true;
        out_desc.fs.images[0].multisampled = false;
        out_desc.fs.images[0].image_type = SG_IMAGETYPE_2D;
        out_desc.fs.images[0].sample_type = SG_IMAGESAMPLETYPE_FLOAT;
        out_desc.fs.samplers[0].used = true;
        out_desc.fs.samplers[0].sampler_type = SG_SAMPLERTYPE_FILTERING;
        out_desc.fs.image_sampler_pairs[0].used = true;
        out_desc.fs.image_sampler_pairs[0].image_slot = 0;
        out_desc.fs.image_sampler_pairs[0].sampler_slot = 0;
        out_desc.fs.image_sampler_pairs[0].glsl_name = "tex_smp";
        out_desc.label = "texcube_shader";
    }

    void GetVxColorTextureShaderDesc(sg_shader_desc& out_desc)
    {
        FileContentsT v_file{ "src/glsl/vxcolortexture_v.glsl", nullptr };
        FileContentsT f_file{ "src/glsl/vxcolortexture_f.glsl", nullptr };
        ReadFileContents(&v_file);
        ReadFileContents(&f_file);

        out_desc.attrs[0].name = "pos";
        out_desc.attrs[1].name = "color0";
        out_desc.attrs[2].name = "texcoord0";
        out_desc.vs.source = (const char*)v_file.contents;
        out_desc.vs.entry = "main";
        out_desc.vs.uniform_blocks[0].size = 64;
        out_desc.vs.uniform_blocks[0].layout = SG_UNIFORMLAYOUT_STD140;
        out_desc.vs.uniform_blocks[0].uniforms[0].name = "vs_params";
        out_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4;
        out_desc.vs.uniform_blocks[0].uniforms[0].array_count = 4;
        out_desc.fs.source = (const char*)f_file.contents;
        out_desc.fs.entry = "main";
        out_desc.fs.images[0].used = true;
        out_desc.fs.images[0].multisampled = false;
        out_desc.fs.images[0].image_type = SG_IMAGETYPE_2D;
        out_desc.fs.images[0].sample_type = SG_IMAGESAMPLETYPE_FLOAT;
        out_desc.fs.samplers[0].used = true;
        out_desc.fs.samplers[0].sampler_type = SG_SAMPLERTYPE_FILTERING;
        out_desc.fs.image_sampler_pairs[0].used = true;
        out_desc.fs.image_sampler_pairs[0].image_slot = 0;
        out_desc.fs.image_sampler_pairs[0].sampler_slot = 0;
        out_desc.fs.image_sampler_pairs[0].glsl_name = "tex_smp";
        out_desc.label = "texcube_shader";
    }

    void GetVxUniformColorShaderDesc(sg_shader_desc& out_desc)
    {
        FileContentsT v_file{ "src/glsl/vxunicolor_v.glsl", nullptr };
        FileContentsT f_file{ "src/glsl/vxunicolor_f.glsl", nullptr };
        ReadFileContents(&v_file);
        ReadFileContents(&f_file);

        out_desc.attrs[0].name = "pos";
        out_desc.vs.source = (const char*)v_file.contents;
        out_desc.vs.entry = "main";
        out_desc.vs.uniform_blocks[0].size = sizeof(glm::mat4) + sizeof(glm::vec4);
        out_desc.vs.uniform_blocks[0].layout = SG_UNIFORMLAYOUT_STD140;
        out_desc.vs.uniform_blocks[0].uniforms[0].name = "vs_params";
        out_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4;
        out_desc.vs.uniform_blocks[0].uniforms[0].array_count = 5;
        out_desc.fs.source = (const char*)f_file.contents;
        out_desc.fs.entry = "main";
        out_desc.label = "vxunicolor";
    }

    const uint32_t px_width = 4;
    const uint32_t px_height = 4;
    uint32_t default_texture_pixels[px_width * px_height] = {
        0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFF000000,
        0xFF000000, 0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFF000000,
        0xFF000000, 0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF,
    };

    sg_pass default_pass = {};
    const sg_color default_clear_color = { 0.25f, 0.5f, 0.75f, 1.0f };
    const float default_clear_depth = 1.0f;
    sg_pass* GetDefaultSGPass()
    {
        static bool binit_default_pass = false;
        if (!binit_default_pass)
        {
            default_pass.action.colors[0].load_action = SG_LOADACTION_CLEAR;
            default_pass.action.colors[0].store_action = SG_STOREACTION_STORE;
            default_pass.action.colors[0].clear_value = default_clear_color;
            default_pass.action.depth.load_action = SG_LOADACTION_CLEAR;
            default_pass.action.depth.store_action = SG_STOREACTION_STORE;
            default_pass.action.depth.clear_value = default_clear_depth;
            binit_default_pass = true;
        }
        default_pass.swapchain = sglue_swapchain();
        return &default_pass;
    }

    sg_pipeline_desc GetDefaultPipelineDesc()
    {
        sg_pipeline_desc result = {};

        result.index_type = SG_INDEXTYPE_UINT16;
        result.cull_mode = SG_CULLMODE_BACK;
        result.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
        result.depth.write_enabled = true;

        return result;
    }

    static const int SLOT_vs_params = 0;

    DrawStateT* InitNewColorPipeline()
    {
        //sg_shader col_shader = sg_make_shader(cube_shader_desc(sg_query_backend()));
        sg_shader_desc vxcolor_desc = {};
        GetVxColorShaderDesc(vxcolor_desc);
        sg_shader vxcolor_shader = sg_make_shader(vxcolor_desc);

        // Previously from sokol-generated .glsl.h
        static const int ATTR_vs_position = 0;
        static const int ATTR_vs_color0 = 1;

        sg_pipeline_desc pipeline_desc = GetDefaultPipelineDesc();
        pipeline_desc.layout.buffers[0].stride = sizeof(v3) + sizeof(v4);
        pipeline_desc.layout.attrs[ATTR_vs_position].format = SG_VERTEXFORMAT_FLOAT3;
        pipeline_desc.layout.attrs[ATTR_vs_color0].format = SG_VERTEXFORMAT_FLOAT4;
        pipeline_desc.shader = vxcolor_shader;

        DrawStateT* pnew_drawstate = new DrawStateT;
        pnew_drawstate->bind = {};
        pnew_drawstate->pip = sg_make_pipeline(&pipeline_desc);

        delete[] vxcolor_desc.vs.source;
        delete[] vxcolor_desc.fs.source;

        return pnew_drawstate;
    }

    DrawStateT* InitNewTexturePipeline()
    {
        sg_image_desc img_desc = {};
        img_desc.width = px_width;
        img_desc.height = px_height;
        img_desc.data.subimage[0][0] = SG_RANGE(default_texture_pixels);

        // Default sampler state
        sg_sampler_desc sampler_desc = {};

        sg_shader_desc vxtexture_desc = {};
        GetVxTextureShaderDesc(vxtexture_desc);
        sg_shader vxtexture_shader = sg_make_shader(vxtexture_desc);

        // Previously from sokol-generated .glsl.h
        static const int ATTR_vs_pos = 0;
        static const int ATTR_vs_texcoord0 = 1;
        static const int SLOT_tex = 0;
        static const int SLOT_smp = 0;

        sg_pipeline_desc pipeline_desc = {};
        pipeline_desc.layout.buffers[0].stride = sizeof(v3) + sizeof(v2);
        pipeline_desc.layout.attrs[ATTR_vs_pos].format = SG_VERTEXFORMAT_FLOAT3;
        pipeline_desc.layout.attrs[ATTR_vs_texcoord0].format = SG_VERTEXFORMAT_FLOAT2;
        pipeline_desc.shader = vxtexture_shader;
        pipeline_desc.index_type = SG_INDEXTYPE_UINT16;
        pipeline_desc.cull_mode = SG_CULLMODE_BACK;
        pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
        pipeline_desc.depth.write_enabled = true;

        DrawStateT* pnew_drawstate = new DrawStateT;
        pnew_drawstate->bind = {};
        pnew_drawstate->bind.fs.images[SLOT_tex] = sg_make_image(&img_desc);
        pnew_drawstate->bind.fs.samplers[SLOT_smp] = sg_make_sampler(&sampler_desc);

        pnew_drawstate->pip = sg_make_pipeline(&pipeline_desc);

        delete[] vxtexture_desc.vs.source;
        delete[] vxtexture_desc.fs.source;

        return pnew_drawstate;
    }

    DrawStateT* InitNewColorTexturePipeline()
    {
        sg_image_desc img_desc = {};
        img_desc.width = px_width;
        img_desc.height = px_height;
        img_desc.data.subimage[0][0] = SG_RANGE(default_texture_pixels);

        // Default sampler state
        sg_sampler_desc sampler_desc = {};

        sg_shader_desc colortexture_desc = {};
        GetVxColorTextureShaderDesc(colortexture_desc);

        static const int ATTR_vs_pos = (0);
        static const int ATTR_vs_color0 = (1);
        static const int ATTR_vs_texcoord0 = (2);
        static const int SLOT_tex = (0);
        static const int SLOT_smp = (0);

        sg_pipeline_desc pipeline_desc = GetDefaultPipelineDesc();
        pipeline_desc.layout.buffers[0].stride = sizeof(v3) + sizeof(v4) + sizeof(v2);
        pipeline_desc.layout.attrs[ATTR_vs_pos].format = SG_VERTEXFORMAT_FLOAT3;
        pipeline_desc.layout.attrs[ATTR_vs_color0].format = SG_VERTEXFORMAT_FLOAT4;
        pipeline_desc.layout.attrs[ATTR_vs_texcoord0].format = SG_VERTEXFORMAT_FLOAT2;
        pipeline_desc.shader = sg_make_shader(colortexture_desc);
        pipeline_desc.index_type = SG_INDEXTYPE_UINT16;
        pipeline_desc.cull_mode = SG_CULLMODE_BACK;
        pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
        pipeline_desc.depth.write_enabled = true;
        pipeline_desc.label = "vxcolortexture";

        DrawStateT* new_coltex_pipeline = new DrawStateT;
        new_coltex_pipeline->bind = {};
        new_coltex_pipeline->bind.fs.images[SLOT_tex] = sg_make_image(&img_desc);
        new_coltex_pipeline->bind.fs.samplers[SLOT_smp] = sg_make_sampler(&sampler_desc);
        new_coltex_pipeline->pip = sg_make_pipeline(pipeline_desc);

        delete[] colortexture_desc.vs.source;
        delete[] colortexture_desc.fs.source;

        return new_coltex_pipeline;
    }

    DrawStateT* InitNewUnicolorPipeline()
    {
        sg_shader_desc unicolor_desc = {};
        GetVxUniformColorShaderDesc(unicolor_desc);

        static const int ATTR_vs_pos = (0);

        sg_pipeline_desc pipeline_desc = GetDefaultPipelineDesc();
        pipeline_desc.layout.buffers[0].stride = sizeof(v3);
        pipeline_desc.layout.attrs[ATTR_vs_pos].format = SG_VERTEXFORMAT_FLOAT3;
        pipeline_desc.shader = sg_make_shader(unicolor_desc);
        pipeline_desc.label = "vxunicolor";

        DrawStateT* new_unicolor_pipeline = new DrawStateT;
        new_unicolor_pipeline->bind = {};
        new_unicolor_pipeline->pip = sg_make_pipeline(pipeline_desc);

        delete[] unicolor_desc.vs.source;
        delete[] unicolor_desc.fs.source;

        return new_unicolor_pipeline;
    }

    void Draw(DrawStateT* draw_state, MeshDrawStateT* mesh_state, glm::mat4& view_proj)
    {
        THEPIT_ASSERT(nullptr != draw_state);
        THEPIT_ASSERT(nullptr != mesh_state);
        THEPIT_ASSERT(nullptr != mesh_state->geo);

        draw_state->bind.vertex_buffers[0] = mesh_state->geo->vertex_buffer;
        draw_state->bind.index_buffer = mesh_state->geo->index_buffer;

        glm::mat4 mvp = view_proj * mesh_state->model_to_world;
        sg_range mvp_range = SG_RANGE(mvp);

        sg_apply_pipeline(draw_state->pip);
        sg_apply_bindings(&draw_state->bind);
        sg_apply_uniforms(SG_SHADERSTAGE_VS, SLOT_vs_params, &mvp_range);
        sg_draw(0, (int)mesh_state->geo->element_count, 1);
    }

    void DrawUnicolor(DrawStateT* draw_state, MeshDrawStateT* mesh_state, glm::mat4& view_proj, glm::vec4& unicolor)
    {
        THEPIT_ASSERT(nullptr != draw_state);
        THEPIT_ASSERT(nullptr != mesh_state);
        THEPIT_ASSERT(nullptr != mesh_state->geo);

        draw_state->bind.vertex_buffers[0] = mesh_state->geo->vertex_buffer;
        draw_state->bind.index_buffer = mesh_state->geo->index_buffer;

        struct vs_params
        {
            glm::mat4 mvp;
            glm::vec4 color;
        };
        vs_params vps;
        vps.mvp = view_proj * mesh_state->model_to_world;
        vps.color = unicolor;
        sg_range vs_params_range = {};
        vs_params_range.ptr = (const void*)&vps;
        vs_params_range.size = sizeof(glm::mat4) + sizeof(glm::vec4);

        sg_apply_pipeline(draw_state->pip);
        sg_apply_bindings(&draw_state->bind);
        sg_apply_uniforms(SG_SHADERSTAGE_VS, SLOT_vs_params, &vs_params_range);
        sg_draw(0, (int)mesh_state->geo->element_count, 1);
    }

    enum struct DrawPassType
    {
        DRAWPASS_COLOR,
        DRAWPASS_SINGLECOLOR,
        DRAWPASS_TEXTURE,
        DRAWPASS_NUM
    };
    static DrawPassType curr_drawpass = DrawPassType::DRAWPASS_COLOR;

    namespace Graphics
    {
        void StateT::Init()
        {
            { // sokol_gfx setup
                sg_desc setup = {};
                setup.environment = sglue_environment();
                setup.logger.func = slog_func;
                sg_setup(&setup);
            }

            { // Imgui setup
                simgui_desc_t imgui_setup = {};
                imgui_setup.logger.func = slog_func;
                simgui_setup(&imgui_setup);
            }

            texcube_geometry = GetCubeGeometry(DebugShapeGeometryE::Texture);
            tex_drawstate = InitNewTexturePipeline();
            colcube_geometry = GetCubeGeometry(DebugShapeGeometryE::Color);
            col_drawstate = InitNewColorPipeline();

            coltex_drawstate = InitNewColorTexturePipeline();

            floormesh = InitNewFloorMesh();

            skyboxmesh = InitNewSkyboxMesh();

            unicolor_drawstate = InitNewUnicolorPipeline();
            unicolorcube = GetCubeGeometry(DebugShapeGeometryE::Unicolor);
        }

        void StateT::DrawFrame(const glm::mat4& vp)
        {
            simgui_frame_desc_t imgui_frame_desc = {};
            imgui_frame_desc.width = sapp_width();
            imgui_frame_desc.height = sapp_height();
            imgui_frame_desc.delta_time = sapp_frame_duration();
            imgui_frame_desc.dpi_scale = sapp_dpi_scale();
            simgui_new_frame(&imgui_frame_desc);

            if (ImGui::Button("Change Draw Pass Type")) {
                curr_drawpass = (DrawPassType)(((int)curr_drawpass + 1) % (int)DrawPassType::DRAWPASS_NUM);
            }

            glm::mat4 model_to_world = glm::mat4(1.0f);
            glm::mat4 mvp = vp;

            MeshDrawStateT colcube_meshdrawstate{ Engine::GlobalState.gfx.colcube_geometry, model_to_world };
            MeshDrawStateT unicube_meshdrawstate{ Engine::GlobalState.gfx.unicolorcube, model_to_world };
            MeshDrawStateT texcube_meshdrawstate{ Engine::GlobalState.gfx.texcube_geometry, model_to_world };
            MeshDrawStateT floor_meshdrawstate{ Engine::GlobalState.gfx.floormesh, model_to_world };
            MeshDrawStateT skybox_meshdrawstate{ Engine::GlobalState.gfx.skyboxmesh, model_to_world };
            MeshDrawStateT unicolorcube_meshdrawstate{ Engine::GlobalState.gfx.unicolorcube, glm::translate(glm::mat4(1.0f), glm::vec3{5.0f, 5.0f, 5.0f}) };
            glm::vec4 color_peachy{ 0.8f, 0.4f, 0.6f, 1.0f };

            auto BeginFrameHelper = []() -> void
            {
                sg_begin_pass(GetDefaultSGPass());
            };

            auto EndFrameHelper = []() -> void
            {
                simgui_render();
                sg_end_pass();
                sg_commit();
            };

            BeginFrameHelper();

            switch (curr_drawpass)
            {
                case DrawPassType::DRAWPASS_COLOR:
                {
                    Draw(Engine::GlobalState.gfx.col_drawstate, &colcube_meshdrawstate, mvp);
                } break;
                case DrawPassType::DRAWPASS_SINGLECOLOR:
                {
                    DrawUnicolor(Engine::GlobalState.gfx.unicolor_drawstate, &unicube_meshdrawstate, mvp, color_peachy);
                } break;
                case DrawPassType::DRAWPASS_TEXTURE:
                {
                    Draw(Engine::GlobalState.gfx.tex_drawstate, &texcube_meshdrawstate, mvp);
                } break;
                default:
                {
                    THEPIT_ASSERT(false);
                } break;
            }
            static bool bFloor = true;
            if (bFloor)
            {
                Draw(Engine::GlobalState.gfx.tex_drawstate, &floor_meshdrawstate, mvp);
            }
            static bool bSkybox = true;
            if (bSkybox)
            {
                Draw(Engine::GlobalState.gfx.coltex_drawstate, &skybox_meshdrawstate, mvp);
            }
            static bool bUnicolorCube = true;
            if (bUnicolorCube)
            {
                DrawUnicolor(Engine::GlobalState.gfx.unicolor_drawstate, &unicolorcube_meshdrawstate, mvp, color_peachy);
            }

            static bool bDrawAxis = true;
            if (bDrawAxis)
            {
                float axis_length = 1000.0f;
                float axis_width = 0.05f;
                MeshDrawStateT xaxis_meshdrawstate{ Engine::GlobalState.gfx.unicolorcube, glm::scale(glm::mat4{1.0f}, glm::vec3{axis_length, axis_width, axis_width}) };
                MeshDrawStateT yaxis_meshdrawstate{ Engine::GlobalState.gfx.unicolorcube, glm::scale(glm::mat4{1.0f}, glm::vec3{axis_width, axis_length, axis_width}) };
                MeshDrawStateT zaxis_meshdrawstate{ Engine::GlobalState.gfx.unicolorcube, glm::scale(glm::mat4{1.0f}, glm::vec3{axis_width, axis_width, axis_length}) };

                DrawUnicolor(Engine::GlobalState.gfx.unicolor_drawstate, &xaxis_meshdrawstate, mvp, glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
                DrawUnicolor(Engine::GlobalState.gfx.unicolor_drawstate, &yaxis_meshdrawstate, mvp, glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
                DrawUnicolor(Engine::GlobalState.gfx.unicolor_drawstate, &zaxis_meshdrawstate, mvp, glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f });
            }

            EndFrameHelper();
        }

        void StateT::Term()
        {
            simgui_shutdown();
            sg_shutdown();

            delete texcube_geometry;
            delete tex_drawstate;
            delete colcube_geometry;
            delete col_drawstate;
            delete coltex_drawstate;
            delete floormesh;
            delete skyboxmesh;
            delete unicolor_drawstate;
            delete unicolorcube;
        }
    } // namespace Graphics
} // namespace ThePit
