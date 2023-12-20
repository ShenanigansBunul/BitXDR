//
// Created by sergi on 12/19/2023.
//

#include "PathGraph.h"
#include<queue>
#include<unordered_set>

/**
 * Calculate the path between two given entities that has the highest total alert score value.
 * @param source The source node (entity)
 * @param target The destination node (entity)
 * @return A vector containing Transition objects in the order they are visited in order to create the path.
 */
vector<Transition> PathGraph::computeLongestPath(long source, long target) {
    auto comparePaths = [](const auto &a, const auto &b) {
        int sumA = accumulate(begin(get<2>(a)), end(get<2>(a)), 0,
                              [](int acc, const Transition &t) { return acc + t.getAlertScore(); });
        int sumB = accumulate(begin(get<2>(b)), end(get<2>(b)), 0,
                              [](int acc, const Transition &t) { return acc + t.getAlertScore(); });
        return sumA < sumB;
    };

    priority_queue<tuple<int, long, vector<Transition>>,
            vector<tuple<int, long, vector<Transition>>>,
            decltype(comparePaths)> priorityQueue(comparePaths);

    unordered_set<long long> visited;

    priorityQueue.push({INT_MAX, source, {}});

    while (!priorityQueue.empty()) {
        long currentNode = get<1>(priorityQueue.top());
        int currentWeight = get<0>(priorityQueue.top());
        vector<Transition> currentPath = get<2>(priorityQueue.top());
        priorityQueue.pop();

        if (currentNode == target) {
            return currentPath;
        }

        // Create unique key based on current node ID and current weight (so as to be able to visit a node multiple
        // times in separate paths. if the weight is equal there already is a path with the same score or the node
        // was already visited in this path.
        long long combinedKey = (static_cast<long long>(currentNode) << 32) | currentWeight;
        if (visited.count(combinedKey)) {
            continue;
        }

        visited.insert(combinedKey);

        for (Transition edge: adjacencyList[currentNode]) {
            if (!currentPath.empty() && edge.getSecondEntity() == currentPath.back().getFirstEntity()) {
                continue;
            }

            // Check if the reverse of the current edge is already present in the path
            Transition reverseEdge = edge.reverseEntities();
            if (find(currentPath.begin(), currentPath.end(), reverseEdge) != currentPath.end()) {
                continue; // Skip traversing the same edge in the opposite direction
            }

            int newWeight = min(currentWeight, edge.getAlertScore());
            vector<Transition> newPath = currentPath;
            newPath.push_back(edge);
            priorityQueue.emplace(newWeight, edge.getSecondEntity(), newPath);
        }
    }

    return {};
}

/**
 * Create a PathGraph object that can then be used to calculate the maximum score path between two given entities.
 * @param edges Transition objects that the graph is made of.
 */
PathGraph::PathGraph(const vector<Transition> &edges) {
    for (Transition edge: edges) {
        adjacencyList[edge.getFirstEntity()].emplace_back(edge);
        adjacencyList[edge.getSecondEntity()].emplace_back(edge.reverseEntities());
    }
}
