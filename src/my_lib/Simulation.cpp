#include <algorithm>
#include <queue>
#include <thread>
#include <mutex>
#include "Simulation.h"

Simulation::Simulation()
{
    //ctor
}

Simulation::~Simulation()
{
    //dtor
}

int getOverlapLength(const std::vector<std::shared_ptr<Node>>& path1, const std::vector<std::shared_ptr<Node>>& path2) {
    
    std::vector<std::shared_ptr<Node>> overlap;

    // Loop over the nodes in the first path
    for (const auto& nodePtr : path1) {
        // Check if this node is in the second path
        if (std::find_if(path2.begin(), path2.end(), [&nodePtr](const auto& p) { return p->id == nodePtr->id; }) != path2.end()) {
            // Add the node to the overlap vector
            overlap.push_back(nodePtr);
        }
    }

    return overlap.size();
}

bool isOpposite(const std::vector<std::shared_ptr<Node>>& path1, const std::vector<std::shared_ptr<Node>>& path2) {
    int path1StartIndex = -1, path1EndIndex = -1;
    int path2StartIndex = -1, path2EndIndex = -1;

    // Find the first and last nodes of the overlapping region in path1
    for (int i = 0; i < path1.size(); i++) {
        if (std::find(path2.begin(), path2.end(), path1[i]) != path2.end()) {
            if (path1StartIndex == -1) {
                path1StartIndex = i;
            }
            path1EndIndex = i;
        }
    }

    // Find the first and last nodes of the overlapping region in path2
    for (int i = 0; i < path2.size(); i++) {
        if (std::find(path1.begin(), path1.end(), path2[i]) != path1.end()) {
            if (path2StartIndex == -1) {
                path2StartIndex = i;
            }
            path2EndIndex = i;
        }
    }

    // Check if the two overlapping regions are going in opposite directions
    if (path1EndIndex < path1StartIndex && path2EndIndex > path2StartIndex) {
        return true;
    }
    if (path1EndIndex > path1StartIndex && path2EndIndex < path2StartIndex) {
        return true;
    }

    return false;
}


void Simulation::run(std::shared_ptr<Track> track, std::vector<std::shared_ptr<Train>>& trains)
{
    std::unordered_map<int, std::vector<std::shared_ptr<Node>>> paths;
    for (const auto& train : trains) {
        std::cout << "Train " << train->getId() <<" is travelling from " << train->getStartingTrack() << " to " << train->getDestination() << " in direction pointing to " << train->getDirection() << std::endl;
        std::vector<std::shared_ptr<Node>> path = findTrainShortestPath(train, track);
        std::cout << "Shortest path: ";
        track->printPath(path);
        paths[train->getId()] = path;
    }

    // sort the trains based on shortest path to longest
    std::sort(trains.begin(), trains.end(), [&paths](const auto& a, const auto& b) {
        return paths[a->getId()].size() < paths[b->getId()].size();
    });

    // launch each train in a separate thread where they must lock each node before they start traversing their path,
    // if it is unable to lock the mutex in every node in their path then it will release all their locks and wait for a random amount of time
    std::vector<std::thread> threads;
    for (const auto& train : trains) {
        threads.push_back(std::thread([train, &paths, &track]() {
            std::vector<std::shared_ptr<Node>> path = paths[train->getId()];
            std::vector<std::shared_ptr<Node>> lockedNodes;
            bool locked = false;
            while (!locked) {
                locked = true;
                for (const auto& node : path) {
                    if (!node->mutex_.try_lock()) {
                        locked = false;
                        break;
                    }
                    lockedNodes.push_back(node);
                }
                if (!locked) {
                    for (const auto& node : lockedNodes) {
                        node->mutex_.unlock();
                    }
                    lockedNodes.clear();
                    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
                }
            }

            // traverse the path
            for (const auto& node : path) {
                std::cout << "Train " << train->getId() << " is travelling through node " << node->id << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            // release the locks
            for (const auto& node : lockedNodes) {
                node->mutex_.unlock();
            }
        }));
    }

    // wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }
}

std::vector<std::shared_ptr<Node>> Simulation::findTrainShortestPath(std::shared_ptr<Train> train, std::shared_ptr<Track> track)
{
    auto startingNode = train->getStartingTrack();
    auto destinationNode = train->getDestination();
    auto directionNode = train->getDirection();

    return track->findShortestPath(train->getStartingTrack(), train->getDestination(), train->getDirection());
}