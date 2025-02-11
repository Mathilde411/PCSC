//
// Created by mathilde on 27/01/25.
//

#pragma once

#include <memory>
#include <vector>

namespace ASN1::Encoding
{
    template<typename T>
    struct TreeNode
    {
        std::vector<std::unique_ptr<TreeNode<T>>> children;
        std::unique_ptr<T> value;
    };

}
