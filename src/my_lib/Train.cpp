#include "Train.h"

Train::Train(int id, int startingTrack, int destination, int direction)
{
    m_id = id;
    m_startingTrack = startingTrack;
    m_destination = destination;
    m_direction = direction;
}

Train::~Train()
{
    //dtor
}
