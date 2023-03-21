#include "Track.h"
#include "Train.h"
#include <memory>
#include <vector>

class Simulation
{
public:
    Simulation();
    ~Simulation();
    void run(std::shared_ptr<Track> track,
             std::vector<std::shared_ptr<Train>> &trains);

    std::vector<std::shared_ptr<Node>> findTrainShortestPath(
        std::shared_ptr<Train> train,
        std::shared_ptr<Track> track);
    //bool detectCollision(std::shared_ptr<Train> train1, std::shared_ptr<Train> train2);
    //void scheduleTrains(std::shared_ptr<Track> track, const std::vector<std::shared_ptr<Train>> &trains);
};