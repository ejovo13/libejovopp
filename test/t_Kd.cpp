#include "ejovotest.hpp"

using namespace ejovo;

int main() {


    KdNode2 node (0.0, 1.0, new KdNode2(1.0, 2.0), nullptr);

    assert(node.n_children() == 1);

    std::cout << "n_children: " << node.n_children() << "\n";
    std::cout << "height: " << node.height() << "\n";

    return 0;
}