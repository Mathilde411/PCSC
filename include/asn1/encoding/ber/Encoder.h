//
// Created by mathilde on 28/01/25.
//

#pragma once
#include <memory>

#include "asn1/encoding/Encoder.h"
#include "asn1/encoding/Tree.h"


namespace ASN1::Encoding::BER
{
    enum Class : uint8_t
    {
        UNIVERSAL = 0b00,
        APPLICATION = 0b01,
        CONTEXT_SPECIFIC = 0b10,
        PRIVATE = 0b11,
    };

    enum Type : uint8_t
    {
        PRIMITIVE = 0b0,
        CONSTRUCTED = 0b1
    };

    struct BERValue
    {
        Class clazz;
        Type type;
        uint64_t tag;
        std::vector<uint8_t> data;
    };

    class Encoder : Encoding::Encoder<BERValue, std::vector<uint8_t>>
    {
    private:
        std::unique_ptr<TreeNode<BERValue>> recImport(
            std::vector<uint8_t>::const_iterator& cbegin,
            const std::vector<uint8_t>::const_iterator& cend
        );

        uint64_t importLength(
            std::vector<uint8_t>::const_iterator& cbegin,
            const std::vector<uint8_t>::const_iterator& cend
        );

        std::unique_ptr<BERValue> importHeader(
            std::vector<uint8_t>::const_iterator& cbegin,
            const std::vector<uint8_t>::const_iterator& cend
        );

        std::unique_ptr<TreeNode<BERValue>> importTree(const std::vector<uint8_t>&) override;
    };
}
