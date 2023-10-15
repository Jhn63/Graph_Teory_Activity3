//
// Created by Melissa on 11/10/2023.
//

#ifndef ATIVIDADE_3_GRAPH_H
#define ATIVIDADE_3_GRAPH_H

#include <list>
#include <string>
#include <fstream>
#include <iostream>

class Graph {

private:
    int N; //number of vertices
    bool **matrix;
    std::list<int> **list;

    void load_data(const std::string& path);

public:
    Graph(const std::string& path);
    ~Graph();

    int get_N();
    std::list<int>& get_op_ngbhood(int vertex);

    void print_v2();
    void print_v1();
};


#endif //ATIVIDADE_3_GRAPH_H
