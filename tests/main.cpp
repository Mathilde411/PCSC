#include <iomanip>
#include <iostream>

#include "asn1/encoding/Tree.h"
#include <sstream>

void buildArrayRepr(const std::vector<uint8_t>& vec, std::stringstream& builder)
{
    for (const uint8_t i : vec)
    {
        builder << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << static_cast<int>(i);
    }
}

void buildObjectRepr(ASN1::BER::Object* ob, uint64_t depth, std::stringstream& builder)
{
    for (uint64_t i = 0; i < depth; ++i)
        builder << "    ";
    builder << "TAG: " << ob->tag();

    if (!ob->primary())
    {
        builder << std::endl;
        for (auto& child : ob->children())
        {
            buildObjectRepr(child.get(), depth + 1, builder);
        }
    }
    else
    {
        builder << " VALUE: ";
        buildArrayRepr(ob->data(), builder);
        builder << std::endl;
    }
}

void printObject(ASN1::BER::Object* ob)
{
    std::stringstream builder;
    buildObjectRepr(ob, 0, builder);
    std::cout << builder.str() << std::endl;
}

int main()
{
    std::vector<uint8_t> bytes = {
        0x30, 0x82, 0x00, 0x44, 0x02, 0x01, 0x00, 0x04, 0x06, 0x70, 0x75, 0x62, 0x6C, 0x69, 0x63, 0xA4, 0x82, 0x00,
        0x35, 0x06, 0x09, 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x99, 0x5D, 0x00, 0x40, 0x04, 0xC0, 0xA8, 0x01, 0x80,
        0x02, 0x01, 0x06, 0x02, 0x01, 0x01, 0x43, 0x03, 0x01, 0xE2, 0x40, 0x30, 0x82, 0x00, 0x15, 0x30, 0x82, 0x00,
        0x11, 0x06, 0x0C, 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x99, 0x5D, 0x03, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01
    };
    std::unique_ptr<ASN1::BER::Object> ob = ASN1::BER::Object::import(bytes);
    printObject(ob.get());
    return 0;
}
