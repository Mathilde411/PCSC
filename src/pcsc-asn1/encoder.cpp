module;

#include <memory>

export module PCSC.ASN1:encoder;

import PCSC.Base;

namespace PCSC::ASN1 {
export template <typename T, typename U>
class Encoder {
public:
    virtual ~Encoder() = default;

private:
    virtual std::unique_ptr<Node<T>> importTree(const U& data) = 0;
};
}