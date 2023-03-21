#pragma once
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>
#include <unordered_set>

class Signal
{

    enum class State
    {
        GREEN,
        RED
    };

public:
    Signal() = default;
    ~Signal() = default;

    State state{State::RED};
    std::unordered_set<int> position;
    int id;
};

class Node
{
public:
    Node(int id) : id(id)
    {
    }
    virtual ~Node() = default;

    int id;
    std::string type;
    int neighborLimit;
    std::vector<std::weak_ptr<Node>> neighbors;
    std::vector<std::weak_ptr<Signal>> signals;

    int getId() const
    {
        return id;
    }
    std::string getType() const
    {
        return type;
    }

    std::mutex mutex_;
    std::condition_variable cv_;

private:
};

class TrackSegment : public Node
{
public:
    TrackSegment(int id) : Node(id)
    {
        type = "TrackSegment";
        neighborLimit = 2;
    }
};

class Junction : public Node
{
public:
    Junction(int id) : Node(id)
    {
        type = "Junction";
        neighborLimit = 3;
    }
};

class Terminator : public Node
{
public:
    Terminator(int id) : Node(id)
    {
        type = "Terminator";
        neighborLimit = 1;
    }
};
