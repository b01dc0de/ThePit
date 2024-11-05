#ifndef THEPIT_DATATYPES_INL
#define THEPIT_DATATYPES_INL

namespace ThePit
{
    using DArraySizeT = int;
    using DArrayIncFactorT = float;

    static const DArraySizeT dynamicarray_default_capacity = 16;
    static const DArrayIncFactorT dynamicarray_default_inc_factor = 2.0f;

    template <typename ItemT>
    struct DynamicArray
    {
        DArraySizeT capacity;
        DArraySizeT num_items;
        DArrayIncFactorT inc_factor;
        ItemT* data;

        DynamicArray();
        DynamicArray(DArraySizeT init_capacity);
        DynamicArray(const DynamicArray& other) = delete;
        DynamicArray& operator=(const DynamicArray& other) = delete;
        ~DynamicArray();
    };
} // namespace ThePit 

#endif // THEPIT_DATATYPES_INL