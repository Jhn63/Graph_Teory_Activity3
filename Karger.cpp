//
// Created by Jhn on 12/10/2023.
//

#include "Karger.h"

Karger::Karger(SuperGraph *s) : s_graph(s) {};

std::vector<std::pair<int, int>> Karger::min_cut() {
    while (s_graph->vtx_total() > 2) {

        auto edge = s_graph->get_random_pair();
        s_graph->merge(edge.first, edge.second);

    }
    return s_graph->back_tracking();
}