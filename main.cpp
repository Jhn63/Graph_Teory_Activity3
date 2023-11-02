#include <iostream>

#include "Karger.h"
#include "IO.h"
#include "Naive.h"

int main() {
    IO io;
    Naive *n = new Naive(io.load_data("test.txt"));
    auto edges = n->min_cut();

    std::cout << "min cut:" << std::endl;
    for (auto e : edges) {
        std::cout << "( " << e.first << " , " << e.second << " )" << std::endl;
    }
}
