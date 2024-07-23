#include "SnitchStrategy.h"

MoveResult SnitchStrategy::move()
{
  return MoveResult::BETRAY;
}

void SnitchStrategy::set_history(std::array<int32_t, 3> current_result, std::array<MoveResult, 3> current_choice)
{
}

SnitchStrategy::SnitchStrategy(const std::map<std::string, std::string> &rule_map, int32_t ind)
{
}

