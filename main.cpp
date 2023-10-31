#include <iostream>

#include "Karger.h"

int main() {
    SuperGraph *s = new SuperGraph("test.txt");
    Karger karger(s);

    auto base_edges = karger.min_cut();
    std::cout << "min_cut: " << std::endl;
    for (auto e : base_edges) {
        std::cout << "( " << e.first << " , " << e.second << " )" << std::endl;
    }
}
