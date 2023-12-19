//
// Created by sergi on 12/19/2023.
//

#ifndef BITXDR_PATHGRAPH_H
#define BITXDR_PATHGRAPH_H


#include "JsonEntities/Transition.h"

class PathGraph {
    unordered_map<long, vector<Transition>> adjacencyList;
public:
    explicit PathGraph(const vector<Transition> &edges);

    vector<Transition> computeLongestPath(long source, long target);
};


#endif //BITXDR_PATHGRAPH_H
