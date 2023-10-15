#include <iostream>

#include "Karger.h"

int main() {
    SuperGraph *s = new SuperGraph();
    s->make_set(1);
    s->make_set(2);
    s->make_pair(1,2);

    s->make_set(3);
    s->make_set(4);
    s->make_pair(3,4);

    s->make_pair(1,3);
    s->make_pair(2,4);

    s->merge(1,2);
    s->merge(3,4);

    auto it = s->edges->begin();
    auto set1 = s->vertex->find(it->first);
    auto set2 = s->vertex->find(it->second);
    std::cout << set1->first << " , " << set2->first << std::endl;
}
