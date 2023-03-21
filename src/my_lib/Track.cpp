#include <queue>
#include <unordered_set>
#include <algorithm>
#include "Track.h"


std::shared_ptr<Node> Track::createNodeByTypeAndID(std::string type, int id) {
    std::cout << "Creating node with id: " << id << std::endl;
    if (type == "TrackSegment")
        addTrackSegmentNode(id);
    else if (type == "Junction")
        addJunctionNode(id);
    else if (type == "Terminator")
        addTerminatorNode(id);
    return nodes[id];
}

void Track::connectNodes(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2) {
    addEdge(node1->id, node2->id);
}

void Track::addNode(int id) {
        nodes[id] = std::make_shared<Node>(id);
    }

void Track::addTrackSegmentNode(int id) {
        nodes[id] = std::make_shared<TrackSegment>(id);
    }

void Track::addJunctionNode(int id) {
        nodes[id] = std::make_shared<Junction>(id);
    }

void Track::addTerminatorNode(int id) {
        nodes[id] = std::make_shared<Terminator>(id);
    }

void Track::addEdge(int id1, int id2) {
        if (nodes.count(id1) && nodes.count(id2)) {
            std::shared_ptr<Node> node1 = nodes[id1];
            std::shared_ptr<Node> node2 = nodes[id2];
            node1->neighbors.push_back(node2);
            node2->neighbors.push_back(node1);
            edges.push_back(std::make_pair(id1, id2));
        }
    }

std::shared_ptr<Node> Track::getNode(int id) const {
    auto iter = nodes.find(id);
    if (iter != nodes.end()) {
        return iter->second;
    }
    return nullptr;
}

std::vector<std::shared_ptr<Node>> Track::getNodes() const {
    std::vector<std::shared_ptr<Node>> nodesVector;
    for (const auto& entry : nodes) {
        nodesVector.push_back(entry.second);
    }
    return nodesVector;
}

void Track::printTrack() const {
    for (const auto& entry : nodes) {
        std::shared_ptr<Node> node = entry.second;
        std::cout << "Node " << entry.first << " (" << node->type << ") is connected to: | ";
        for (const auto& neighbor : node->neighbors) {
            std::shared_ptr<Node> neighborPtr = neighbor.lock();
            if (neighborPtr) {
                std::cout << "Node " << neighborPtr->id << " (" << neighborPtr->type << ") | ";
            }
        }
        std::cout << std::endl;
    }
}

std::vector<std::shared_ptr<Node>> Track::findShortestPath(int start, int goal, int direction) {
    // find the shortest path between two nodes using BFS
    std::vector<std::shared_ptr<Node>> path;
    //std::unordered_set<int> visited;
    // map to store the parent of each node
    std::unordered_map<int, int> parent;
    std::queue<int> q;
    q.push(direction);
    parent[direction] = start;
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        if (current == goal) {
            break;
        }
        std::shared_ptr<Node> node = nodes[current];
        for (auto neighbor : node->neighbors) {
            // if neighbor is not visited, add it to the queue
            if (neighbor.lock()->id != parent[current]) {
                // add neighbor to the queue
                q.push(neighbor.lock()->id);
                // set parent of neighbor to current
                parent[neighbor.lock()->id] = current;
            }
        }
    }
    if (parent.find(goal) == parent.end()) {
        std::cout << "No path found" << std::endl;
        return path;
    }
    int current = goal;
    while (current != start) {
        path.push_back(nodes[current]);
        current = parent[current];
    }
    path.push_back(nodes[start]);
    std::reverse(path.begin(), path.end());
    return path;
}

void Track::printPath(std::vector<std::shared_ptr<Node>> path) const {
    for (const auto& node : path) {
        std::cout << "Node " << node->id << " (" << node->type << ") -> ";
    }
    std::cout << "Arrived";
    std::cout << std::endl;
}


