#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Node.h"

class Track {
private:
    std::unordered_map<int, std::shared_ptr<Node>> nodes;
    std::vector<std::pair<int, int>> edges;
    std::unordered_map<int, std::shared_ptr<Signal>> signals;

public:
    Track() = default;
    void addNode(int id);
    void addTrackSegmentNode(int id);
    void addJunctionNode(int id);
    void addTerminatorNode(int id);
    void addEdge(int id1, int id2);
    int getNumNodes() const { return nodes.size(); }
    std::shared_ptr<Node> createNodeByTypeAndID(std::string type, int id);
    std::shared_ptr<Node> getNode(int id) const;
    std::vector<std::shared_ptr<Node>> getNodes() const;
    std::vector<std::pair<int, int>> getEdges() const { return edges; }
    std::vector<std::shared_ptr<Node>> findShortestPath(int start, int goal, int direction);
    void connectNodes(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2);
    void printTrack() const;
    void printPath(std::vector<std::shared_ptr<Node>> path) const;

};
