#include <memory>

#include "Component.h"

// ObjectFactory.h
class ComponentFactory
{
public:
    virtual ~ComponentFactory()
    {
    }
    virtual std::unique_ptr<Node> createComponent() = 0;
};

// TrackSegmentFactory.h
class TrackSegmentFactory : public ComponentFactory
{
public:
    std::unique_ptr<Node> createComponent() override
    {
        return std::make_unique<TrackSegment>();
    }
};

// JunctionFactory.h
class JunctionFactory : public ComponentFactory
{
public:
    std::unique_ptr<Node> createComponent() override
    {
        return std::make_unique<Junction>();
    }
};

// TerminatorFactory.h
class TerminatorFactory : public ComponentFactory
{
public:
    std::unique_ptr<Node> createComponent() override
    {
        return std::make_unique<Terminator>();
    }
};

