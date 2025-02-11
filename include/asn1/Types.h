//
// Created by mathilde on 28/01/25.
//

#pragma once
#include <cstdint>
#include <vector>

namespace ASN1::Types
{

    template <typename T, uint64_t typeTag>
    struct Type
    {
        T val;

        uint64_t tag() const
        {
            return typeTag;
        }
    };

    using Boolean = Type<bool, 1>;
} // ASN1
