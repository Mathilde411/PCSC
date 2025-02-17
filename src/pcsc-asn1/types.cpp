module;

#include <cstdint>

export module PCSC.ASN1:types;

namespace PCSC::ASN1 {
template <typename T, uint64_t typeTag>
    struct Type
{
    T val;

    [[nodiscard]] uint64_t tag() const
    {
        return typeTag;
    }
};

using Boolean = Type<bool, 1>;
}