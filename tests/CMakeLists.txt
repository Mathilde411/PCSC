add_executable(Test
        main.cpp
)
target_link_libraries(Test PRIVATE ASN1)
target_compile_features(Test PUBLIC cxx_std_23)