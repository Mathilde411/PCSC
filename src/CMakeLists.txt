add_library(ASN1
        ../include/asn1/encoding/Tree.h
        asn1/encoding/ber/Encoder.cpp
        ../include/asn1/encoding/ber/Encoder.h
        ../include/asn1/encoding/Encoder.h
        ../include/asn1/Types.h
)
target_include_directories(ASN1 PUBLIC ../include)
#target_link_libraries(BoringLang PRIVATE Boost::boost)
target_compile_features(ASN1 PUBLIC cxx_std_23)