module;

#include <memory>

export module PCSC.ASN1:encoder;

import PCSC.Base;
import :types;
namespace PCSC::ASN1 {
export template <typename T, typename U>
class Encoder {
public:
    virtual ~Encoder() = default;

private:
    virtual std::unique_ptr<Type> import(const U& data) = 0;
};

}