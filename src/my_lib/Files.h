#pragma once
#include "Track.h"
#include "Train.h"
#include <memory>
#include <string>
#include <vector>

namespace Files
{
void saveToJson(const std::string &filename,
                const std::shared_ptr<Track> &track,
                const std::vector<std::shared_ptr<Train>> &trains);
void loadFromJson(const std::string &filename,
                  std::shared_ptr<Track> &track,
                  std::vector<std::shared_ptr<Train>> &trains);
} // namespace Files
