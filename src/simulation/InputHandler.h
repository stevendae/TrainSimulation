#include "UserInput.h"

// InputHandler.h
class InputHandler
{
public:
    InputHandler();
    bool getValidInput();
    bool addTrackComponents();
    std::string getTrackType();
    std::vector<int> getConnectedTo();
    bool validTrackSegment();
    //bool validJunction(UserInput &userInput);
    //bool validTerminator(UserInput &userInput);
    void setTrainParameters();
    void setSignalParameters();
    bool loadTrackState();
    bool saveTrackState();
    bool addTrains();
    bool addSignals();


    std::string m_type{""};
    std::string m_continue{""};
    std::string type{""};
    std::string connectedTo{""};
    std::string loadFilename{""};
    int trainStart;
    int trainDirection;
    int trainDestination;
    int signalID_1;
    int signalID_2;
};