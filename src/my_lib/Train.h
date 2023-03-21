#pragma once

#include <memory>

class Train
{
public:
    Train(int id, int startingTrack, int destination, int direction);
    ~Train();
    int getStartingTrack()
    {
        return m_startingTrack;
    }
    int getDestination()
    {
        return m_destination;
    }
    int getDirection()
    {
        return m_direction;
    }
    int getId()
    {
        return m_id;
    }

private:
    int m_id;
    int m_startingTrack;
    int m_destination;
    int m_direction;
};