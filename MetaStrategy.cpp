#include "MetaStrategy.h"

MoveResult MetaStrategy::move()
{
  if ( n == 0 )
  {
    auto strategy = DefaultStrategy(my_rule_map, 0);
    choice = strategy.move();
  }
  else if ( n == 1 )
  {
    auto strategy = SimpleStrategy(my_rule_map, 0);
    choice = strategy.move();
  }
  else if ( n == 2 )
  {
    auto strategy = SnitchStrategy(my_rule_map, 0);
    choice = strategy.move();
  }
  else
  {
    int32_t max = -1;
    MoveResult choice_max;
    for ( int32_t i = 0; i < n; i++ )
    {
      int32_t tmp = history_result[i][idx];
      if ( tmp >= max )
      {
        max = tmp;
        choice_max = history_choice[i][idx];
      }
    }
    choice = choice_max;
  }
  n++;
  return choice;
}

void MetaStrategy::set_history(std::array<int32_t, 3> current_result, std::array<MoveResult, 3> current_choice)
{
  history_result.push_back(current_result);
  history_choice.push_back(current_choice);
  
}

MetaStrategy::MetaStrategy(const std::map<std::string, std::string> &rule_map, int32_t input_idx)
{
  my_rule_map=rule_map;
  idx=input_idx;
}