#include "Geometry.h"

namespace ThePit
{
    sg_buffer MakeVxBuffer(const float* p_vxs, size_t vx_size, size_t vx_count)
    {
        THEPIT_ASSERT(nullptr != p_vxs);
        THEPIT_ASSERT(0 < vx_size);
        THEPIT_ASSERT(0 < vx_count);

        sg_buffer_desc vxbuff_desc = {};
        vxbuff_desc.data = sg_range{ p_vxs, vx_size * vx_count };
        vxbuff_desc.type = SG_BUFFERTYPE_VERTEXBUFFER;
        vxbuff_desc.usage = SG_USAGE_IMMUTABLE;

        return sg_make_buffer(&vxbuff_desc);
    }

    sg_buffer MakeIxBuffer(const TriInds* p_inds, size_t ix_count)
    {
        THEPIT_ASSERT(nullptr != p_inds);
        THEPIT_ASSERT(0 < ix_count);

        sg_buffer_desc ixbuff_desc = {};
        ixbuff_desc.data = sg_range{ p_inds, sizeof(TriInds) * ix_count };
        ixbuff_desc.type = SG_BUFFERTYPE_INDEXBUFFER;
        ixbuff_desc.usage = SG_USAGE_IMMUTABLE;

        return sg_make_buffer(&ixbuff_desc);
    }
} // namespace ThePit
