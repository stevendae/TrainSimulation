#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Track.h"
#include "Train.h"

namespace Files
{
    void saveToJson(const std::string& filename, const std::shared_ptr<Track>& track, const std::vector<std::shared_ptr<Train>>& trains);
    void loadFromJson(const std::string& filename, std::shared_ptr<Track>& track, std::vector<std::shared_ptr<Train>>& trains);
}



