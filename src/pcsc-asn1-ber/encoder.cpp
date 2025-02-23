module;

#include <cstdint>
#include <vector>
#include <memory>

#define func auto

export module PCSC.ASN1.BER:encoder;

import PCSC.ASN1;
import PCSC.Base;

namespace PCSC::ASN1::BER {

enum Class : uint8_t {
    UNIVERSAL = 0b00,
    APPLICATION = 0b01,
    CONTEXT_SPECIFIC = 0b10,
    PRIVATE = 0b11,
};

enum Type : uint8_t {
    PRIMITIVE = 0b0,
    CONSTRUCTED = 0b1
};

struct BERValue {
    Class clazz;
    Type type;
    uint64_t tag;
    std::vector<uint8_t> data;
};

export class BEREncoder : public Encoder<BERValue, std::vector<uint8_t>> {
private:
    static uint8_t readIter(std::vector<uint8_t>::const_iterator& iter, const std::vector<uint8_t>::const_iterator end) {
        const uint8_t result = *iter;
        if (++iter >= end)
            throw std::out_of_range("Iterator out of range");
        return result;
    }

    std::unique_ptr<Node<BERValue>> recImport(
        std::vector<uint8_t>::const_iterator& cbegin,
        const std::vector<uint8_t>::const_iterator& cend
    ) {
        auto value = importHeader(cbegin, cend);
        const uint64_t length = importLength(cbegin, cend);

        if (cbegin + length > cend)
            throw std::out_of_range("Iterator out of range");

        if (value->type == PRIMITIVE) {
            value->data = std::vector(cbegin, cbegin + length);
            cbegin += length;
        }

        std::vector<std::unique_ptr<Node<BERValue>>> children;
        while (cbegin < cend)
            children.push_back(recImport(cbegin, cend));
        return std::make_unique<Node<BERValue>>(std::move(children), std::move(value));

    };

    uint64_t importLength(
        std::vector<uint8_t>::const_iterator& cbegin,
        const std::vector<uint8_t>::const_iterator& cend
    ) {
        uint8_t len = readIter(cbegin, cend);
        if ((len & 0b10000000) == 0)
            return len;

        len &= 0b01111111;
        if (len == 0)
            throw std::runtime_error("This implementation doesn't support indefinite lengths.");

        if (len > 8)
            throw std::runtime_error("This implementation doesn't support lengths encoded over more than 8 bytes.");

        uint64_t result = 0;
        for (uint8_t i = 0; i < len; i++) {
            result = result << 8 | readIter(cbegin, cend);
        }
        return result;
    }


    std::unique_ptr<BERValue> importHeader(
        std::vector<uint8_t>::const_iterator& cbegin,
        const std::vector<uint8_t>::const_iterator& cend
    )  {
        uint8_t byte = readIter(cbegin, cend);
        uint64_t tag = byte & 0b00011111;
        byte >>= 5;
        auto type = static_cast<Type>(byte & 0b001);
        byte >>= 1;
        auto clazz = static_cast<Class>(byte);

        if (tag == 0b11111) {
            tag = 0;
            do {
                byte = readIter(cbegin, cend);
                tag = tag << 7 | (byte & 0b01111111);

            } while ((byte & 0b10000000) != 0);
        }
        return std::make_unique<BERValue>(clazz, type, tag);
    }

    std::unique_ptr<Node<BERValue>> importTree(const std::vector<uint8_t>& data) {
        auto cbegin = data.cbegin();
        return recImport(cbegin, data.cend());
    }
};
}