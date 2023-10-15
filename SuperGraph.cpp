//
// Created by Jhn on 04/10/2023.
//

#include "SuperGraph.h"

SuperGraph::SuperGraph() : max_set(0){
    this->vertex = new std::unordered_map<int, GSet>;
    this->edges = new std::unordered_set<std::pair<int,int>, hash_pair>;
}

void SuperGraph::make_set(int v) {
    if (v > max_set) { max_set = v; }

    GSet *set = new GSet(v);
    vertex->insert({v, *set});
}

void SuperGraph::make_pair(int v, int u) const {
    auto pair = new std::pair<int,int>(v, u);
    edges->insert(*pair);
}

void SuperGraph::merge(int v, int u) {
    auto it1 = vertex->find(v);
    auto it2 = vertex->find(u);

    max_set++;
    GSet *set1 = &it1->second;
    GSet *set2 = &it2->second;
    GSet *comb = new GSet(max_set, set1, set2);
    vertex->insert({max_set,*comb});

    vertex->erase(v);
    vertex->erase(u);
    contract(v, u);
}

void SuperGraph::contract(int v, int u) {
    std::unordered_set<std::pair<int, int>, hash_pair> to_erase;
    std::unordered_set<std::pair<int, int>, hash_pair> to_insert;

    auto it = edges->begin();
    while (it != edges->end()) {
        if (it->first == v && it->second == u) {
            to_erase.insert(*it);
        }
        else {
            if (it->first == v || it->first == u) {
                to_erase.insert(*it);
                to_insert.insert({it->second, max_set});
            }
            else if (it->second == v || it->second == u) {
                to_erase.insert(*it);
                to_insert.insert({it->first, max_set});
            }
        }
        ++it;
    }

    for (const auto &edge : to_erase) {
        edges->erase(edge);
    }
    for (const auto &edge : to_insert) {
        edges->insert(edge);
    }
}

int SuperGraph::vtx_total() {
    return vertex->size();
}

std::pair<int,int> SuperGraph::get_random_pair() {
    std::vector<std::pair<int, int>> vector(edges->begin(),edges->end());
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<int> random(0, vector.size()-1);
    return vector[random(gen)];
}
