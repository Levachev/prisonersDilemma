#include "SimpleStrategy.h"

MoveResult SimpleStrategy::move()
{
  int32_t tmp = rand();
  return (tmp % 2 == 0) ? MoveResult::BETRAY : MoveResult::COOPERATE;
}

void SimpleStrategy::set_history(std::array<int32_t, 3> current_result, std::array<MoveResult, 3> current_choice)
{
}

SimpleStrategy::SimpleStrategy(const std::map<std::string, std::string> &rule_map, int32_t ind)
{
}
