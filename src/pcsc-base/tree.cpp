module;

#include <vector>
#include <memory>

export module PCSC.Base:tree;

namespace PCSC {
export template<typename T>
struct Node {
    std::vector<std::unique_ptr<Node>> children;
    std::unique_ptr<T> data;
};

}