#pragma once

#include "Node.h"

// TrackSegment.h
class TrackSegment : public Node
{

public:
    TrackSegment() : id(++count)
    {
        type = "TrackSegment";
    }

private:
};

// Junction.h
class Junction : public Node
{
public:
    Junction(int id) : id(++count)
    {
        type = "Junction";
    }

private:
};

// Terminator.h
class Terminator : public Node
{
public:
    Terminator(int id) : id(++count)
    {
        type = "Terminator";
    }

private:
};