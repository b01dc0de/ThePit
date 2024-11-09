#ifndef THEPIT_DATATYPES_INL
#define THEPIT_DATATYPES_INL

namespace ThePit
{
    using SizeT = long long;

    template <typename ItemT>
    struct FixedArray
    {
        static const SizeT default_capacity = 32;

        SizeT capacity;
        ItemT* items;

        FixedArray(SizeT in_capacity = default_capacity)
            : capacity(in_capacity)
            , items(new ItemT[in_capacity])
        {
        }
        FixedArray(const FixedArray& other) = delete;
        FixedArray& operator=(const FixedArray& other) = delete;
        ~FixedArray()
        {
            if (items)
            {
                delete[] items;
            }
        }
        FixedArray(FixedArray&& other)
        {
            *this = other;
        }
        FixedArray& operator=(FixedArray&& other)
        {
            this->capacity = other.capacity;
            this->items = other.items;
            other.capacity = 0;
            other.items = nullptr;
        }

        ItemT& operator[](SizeT idx)
        {
            THEPIT_ASSERT(idx >= 0);
            THEPIT_ASSERT(idx < capacity);
            return items[idx];
        }
    };
} // namespace ThePit 

#endif // THEPIT_DATATYPES_INL