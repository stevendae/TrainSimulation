#include <iostream>
#include <memory>


#include "Files.h"
#include "InputHandler.h"
#include "Simulation.h"
#include "Track.h"
#include "Train.h"
#include "UserInput.h"


int main()
{

    InputHandler inputHandler;

    // Create a graph with 4 vertices
    auto track = std::make_shared<Track>();

    std::vector<std::shared_ptr<Train>> trains;

    // Load track state from file
    if (inputHandler.loadTrackState())
    {
        std::string filename = "trackState.json";
        Files::loadFromJson(filename, track, trains);
    }
    // Add components to the track
    int id = track->getNumNodes();
    while (inputHandler.addMoreComponents())
    {
        if (!inputHandler.getValidInput())
        {
            continue;
        }
        std::string trackType = inputHandler.getTrackType();
        std::vector<int> trackConnectedTo = inputHandler.getConnectedTo();

        auto newNode = track->createNodeByTypeAndID(trackType, ++id);
        for (auto &node : trackConnectedTo)
        {
            auto nodePtr = track->getNode(node);
            track->connectNodes(newNode, nodePtr);
        }
    }

    // Print the track as an adjacency list
    std::cout << "The nodes on the track and their connected nodes are: "
              << std::endl;
    track->printTrack();
    std::cout << std::endl;

    if (inputHandler.saveTrackState())
    {
        Files::saveToJson("trackState.json", track, trains);
    }

    int trainID = 0;
    while (inputHandler.addMoreTrains())
    {
        // Add a train
        inputHandler.setTrainParameters();
        std::shared_ptr<Train> train =
            std::make_shared<Train>(++trainID,
                                    inputHandler.trainStart,
                                    inputHandler.trainDestination,
                                    inputHandler.trainDirection);

        trains.push_back(train);
    }

    // Run simulation
    std::cout << "Running simulation...\n";
    Simulation simulation;
    simulation.run(track, trains);

    std::cout << std::endl;
    return 0;
}
