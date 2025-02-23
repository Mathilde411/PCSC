module;

#include <cstdint>
#include <vector>

export module PCSC.ASN1:types;

namespace PCSC::ASN1 {
export struct Type {
    virtual ~Type() = default;
    [[nodiscard]] virtual constexpr uint64_t tag() const = 0;
};

template <typename T, uint8_t N>
struct SimpleType final : Type {
    T val;

    [[nodiscard]] constexpr uint64_t tag() const override {
        return N;
    }
};

export using Boolean = SimpleType<bool, 1>;
export using Integer = SimpleType<int64_t, 2>;

struct BitString final : Type {
    std::vector<uint8_t> val;
    size_t bitLen;

    [[nodiscard]] uint64_t tag() const override {
        return 3;
    }
};

export using OctetString = SimpleType<std::vector<uint8_t>, 4>;

struct Null final : Type {
    [[nodiscard]] constexpr uint64_t tag() const override {
        return 5;
    }
};
}