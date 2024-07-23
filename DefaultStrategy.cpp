#include "DefaultStrategy.h"

MoveResult DefaultStrategy::move()
{
  return MoveResult::COOPERATE;
}

void DefaultStrategy::set_history(std::array<int32_t, 3> current_result, std::array<MoveResult, 3> current_choice)
{
}

DefaultStrategy::DefaultStrategy(const std::map<std::string, std::string> &rule_map, int32_t ind)
{
}
