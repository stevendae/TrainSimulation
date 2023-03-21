#pragma once
#include <string>

// UserInput.h
struct UserInput
{
    std::string type{""};
    std::string connectedTo{""};
    int trainStart;
    int trainDirection;
    int trainDestination;
};