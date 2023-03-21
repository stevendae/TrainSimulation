#include <ios>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "InputHandler.h"

InputHandler::InputHandler()
{
}

bool InputHandler::getValidInput()
{
    // Get user input for a new component
    std::cout
        << "\nEnter the type of component to add (TrackSegment, Junction, "
           "or Terminator): ";
    std::cin >> m_type;

    // Clear input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (m_type == "TrackSegment")
    {
        type = m_type;
        std::cout << "Which components do this track segment connect to? If it "
                     "is the first component, just press enter. If multiple "
                     "separate each with a space."
                  << std::endl;
        std::getline(std::cin, connectedTo);
        if (!validTrackSegment())
        {
            return false;
        }
    }
    else if (m_type == "Junction")
    {
        type = m_type;
        std::cout << "Which component does this junction connect to? ";
        std::getline(std::cin, connectedTo);
    }
    else if (m_type == "Terminator")
    {
        type = m_type;
        std::cout << "Which component does this terminator connect to? ";
        std::getline(std::cin, connectedTo);
    }
    else
    {
        std::cout << "\nInvalid type of component. Please enter TrackSegment, "
                     "Junction, or Terminator."
                  << std::endl;
        return false;
    }
    return true;
}

bool InputHandler::addMoreComponents()
{
    std::cout << "\nDo you want to add more components to the track? (y/n): ";
    std::cin >> m_continue;
    if (m_continue != "y" && m_continue != "Y")
    {
        return false;
    }

    return true;
}

std::string InputHandler::getTrackType()
{
    return type;
}

std::vector<int> InputHandler::getConnectedTo()
{
    std::istringstream iss(connectedTo);
    std::vector<int> tokens;
    std::string token;
    while (iss >> token)
    {
        tokens.push_back(stoi(token));
    }

    return tokens;
}


bool InputHandler::validTrackSegment()
{
    // TODO: Check if the track segment is valid
    // Check if the connection id is valid

    return true;
}

void InputHandler::setTrainParameters()
{
    std::cout << "Enter the id of the Track Segment from where the train "
                 "starts from: ";
    std::cin >> trainStart;
    std::cout
        << "Enter the id of the Track Segment from you want the train to go: ";
    std::cin >> trainDestination;
    std::cout << "Which adjacent Track Component does the train face? ";
    std::cin >> trainDirection;
}

bool InputHandler::loadTrackState()
{
    std::cout << "Do you have a previous track state that you would like to "
                 "load? (y/n)"
              << std::endl;
    std::cin >> m_continue;
    if (m_continue == "y" || m_continue == "Y")
    {
        std::cout
            << "Enter the filename of the track state you would like to load: ";
        std::cin >> loadFilename;
        return true;
    }
    return false;
}

bool InputHandler::saveTrackState()
{
    std::cout << "Do you want to save the current track state? (y/n)"
              << std::endl;
    std::cin >> m_continue;
    if (m_continue == "y" || m_continue == "Y")
    {
        return true;
    }
    return false;
}

bool InputHandler::addMoreTrains()
{
    std::cout << "Do you want to add more trains? (y/n)" << std::endl;
    std::cin >> m_continue;
    if (m_continue == "y" || m_continue == "Y")
    {
        return true;
    }
    return false;
}
