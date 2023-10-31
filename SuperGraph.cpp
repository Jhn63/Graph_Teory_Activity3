//
// Created by Jhn on 04/10/2023.
//

#include <sstream>
#include <fstream>
#include <algorithm>
#include "SuperGraph.h"

SuperGraph::SuperGraph(std::string file) : max_set(0) {
    this->vertex = new std::unordered_map<int, GSet>;
    this->matrix = new std::vector<std::vector<uint8_t>>;
    this->edges = new std::unordered_set<std::pair<int,int>, hash_pair>;

    load_data(file);
    initialize();
}

SuperGraph::~SuperGraph() {
    delete vertex;
    delete matrix;
    delete edges;
}

void SuperGraph::initialize() {
    auto i = matrix->begin()+1;
    for (int row = 1 ; i != matrix->end(); row++, i++) {

        auto j = i->begin();
        for (int column = 0; j != i->begin()+row+1; column++, j++) {

            if(*j == 1) {
                make_set(row);
                make_set(column);
                make_pair(row, column);
            }

        }
    }

    std::cout << "vertex: " << std::endl;
    for (auto v : *vertex) {
        std::cout << v.second.id << std::endl;
    }
    std::cout << std::endl;

    std::cout << "edge: " << std::endl;
    for (auto v : *edges) {
        std::cout << "( " << v.first << " , " << v.second << " )" << std::endl;
    }
    std::cout << std::endl;
}

void SuperGraph::load_data(std::string path) {
    std::ifstream input;
    input.open(path);
    if (!input.is_open()) {
        std::cerr << "file not open";
        delete this;  exit(-1);
    }

    int trash; input >> trash;

    std::string line;
    while (!input.eof()) {
        std::getline(input, line);

        int data;
        if (!line.empty()) {
            std::vector<uint8_t> row;
            std::istringstream stream(line);
            while (stream >> data) {
                row.push_back(data);
            }
            matrix->push_back(row);
        }
    }
    input.close();
}

void SuperGraph::make_set(int v) {
    if (v > max_set) { max_set = v; }

    GSet *set = new GSet(v);
    vertex->insert({v, *set});
}

void SuperGraph::make_pair(int v, int u) const {
    if (v > u) { std::swap(v,u); }

    auto pair = new std::pair<int,int>(v, u);
    edges->insert(*pair);
}

void SuperGraph::merge(int v, int u) {
    auto it1 = vertex->find(v);
    auto it2 = vertex->find(u);

    max_set++;
    GSet *set1 = new GSet(0); set1->copy(it1->second);
    GSet *set2 = new GSet(0); set2->copy(it2->second);

    GSet *comb = new GSet(max_set, set1, set2);
    vertex->insert({max_set,*comb});

    vertex->erase(v);//erro
    vertex->erase(u);//erro
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
    for (const auto &edge : to_insert) {
        std::cout << edge.first << " , " << edge.second << std::endl;
    }
    std::cout << std::endl;
}

std::vector<std::pair<int, int>> SuperGraph::back_tracking() {
    std::vector<std::pair<GSet, GSet>> pairs, concat;
    if (vertex->size() == 2) {

        std::vector<GSet> vector;
        for (auto it : *vertex) {
            vector.push_back(it.second);
        }
        pairs.push_back({vector[0], vector[1]});

        bool flag;
        do {
            flag = false;
            for (auto it : pairs) {
                if (!it.first.simple && !it.second.simple) {
                    concat.push_back({*it.first.set1, *it.second.set1});
                    concat.push_back({*it.first.set1, *it.second.set2});
                    concat.push_back({*it.first.set2, *it.second.set1});
                    concat.push_back({*it.first.set2, *it.second.set2});
                    flag = true;
                } else if (it.first.simple && !it.second.simple) {
                    concat.push_back({it.first, *it.second.set1});
                    concat.push_back({it.first, *it.second.set2});
                    flag = true;
                } else if (!it.first.simple && it.second.simple) {
                    concat.push_back({*it.first.set1, it.second});
                    concat.push_back({*it.first.set2, it.second});
                    flag = true;
                }
            }

            if (!concat.empty()) {
                pairs.assign(concat.begin(), concat.end());
            }
            concat.clear();
        } while (flag);
    }
    return refine(pairs);
}

std::vector<std::pair<int,int>> SuperGraph::refine(std::vector<std::pair<GSet,GSet>> bt_list) {
    std::vector<std::pair<int,int>> refined;
    for (auto p : bt_list) {
        int i = p.first.id, j = p.second.id;

        auto row = matrix->at(i);
        auto column = row.at(j);
        if (column == 1) {
            if (i > j) {
                refined.push_back({j,i});
            }
            else {
                refined.push_back({i,j});
            }
        }
    }
    return refined;
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
