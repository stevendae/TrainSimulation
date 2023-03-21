#include "Files.h"
#include <fstream>
#include <nlohmann/json.hpp>


void Files::saveToJson(const std::string &filename,
                       const std::shared_ptr<Track> &track,
                       const std::vector<std::shared_ptr<Train>> &trains)
{
    std::cout << "Saving Track State.\n";
    nlohmann::json trackState;

    // Add track nodes
    for (const auto &node : track->getNodes())
    {
        nlohmann::json nodeData;
        nodeData["id"] = node->getId();
        nodeData["type"] = node->getType();
        trackState["nodes"].push_back(nodeData);
    }
    // Add connections
    for (const auto &edge : track->getEdges())
    {
        nlohmann::json edgeData;
        edgeData["node1"] = edge.first;
        edgeData["node2"] = edge.second;
        trackState["edges"].push_back(edgeData);
    }
    std::ofstream trackStateFile("trackState.json");
    trackStateFile << trackState.dump(4) << std::endl;
    trackStateFile.close();
}

void Files::loadFromJson(const std::string &filename,
                         std::shared_ptr<Track> &track,
                         std::vector<std::shared_ptr<Train>> &trains)
{
    // Read the contents of the JSON file
    std::ifstream input(filename);
    nlohmann::json json;
    input >> json;

    // Create the track from the JSON data
    track = std::make_shared<Track>();
    for (auto &node : json["nodes"])
    {
        std::string type = node["type"];
        int id = node["id"];
        auto trackNode = track->createNodeByTypeAndID(type, id);
    }
    for (auto &node : json["edges"])
    {
        int node1 = node["node1"];
        int node2 = node["node2"];
        auto node1Ptr = track->getNode(node1);
        auto node2Ptr = track->getNode(node2);
        track->connectNodes(node1Ptr, node2Ptr);
    }

    // // Create the trains from the JSON data
    // for (auto& train : json["trains"]) {
    //     int startingTrackId = train["startingTrackId"];
    //     int destinationTrackId = train["destinationTrackId"];
    //     int directionNodeId = train["directionNodeId"];

    //     auto startingTrack = track->getNodeById(startingTrackId);
    //     auto destinationTrack = track->getNodeById(destinationTrackId);
    //     auto directionNode = track->getNodeById(directionNodeId);

    //     auto newTrain = std::make_shared<Train>(startingTrack, destinationTrack, directionNode);
    //     trains.push_back(newTrain);
    // }
}
