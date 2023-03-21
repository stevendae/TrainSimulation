#include "UserInput.h"

// InputHandler.h
class InputHandler
{
public:
    InputHandler();
    bool getValidInput();
    bool addMoreComponents();
    std::string getTrackType();
    std::vector<int> getConnectedTo();
    bool validTrackSegment();
    //bool validJunction(UserInput &userInput);
    //bool validTerminator(UserInput &userInput);
    void setTrainParameters();
    bool loadTrackState();
    bool saveTrackState();
    bool addMoreTrains();


    std::string m_type{""};
    std::string m_continue{""};
    std::string type{""};
    std::string connectedTo{""};
    std::string loadFilename{""};
    int trainStart;
    int trainDirection;
    int trainDestination;
};