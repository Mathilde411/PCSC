//
// Created by mathilde on 28/01/25.
//

#pragma once
#include "Tree.h"
#include "asn1/Types.h"

namespace ASN1::Encoding
{
    template <typename T, typename U>
    class Encoder
    {
    public:
        virtual ~Encoder() = default;

    private:
        virtual std::unique_ptr<TreeNode<T>> importTree(const U& data) = 0;
    };

    template <typename T, uint64_t typeId, typename U, typename V>
    class ObjectEncoder
    {
    private:
        Encoder<U, V> encoder;
    public:
        virtual Types::Type<T, typeId> importObject(const U&);
    };
}
