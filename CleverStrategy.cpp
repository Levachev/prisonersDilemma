#include "CleverStrategy.h"
#include <cassert>

namespace
{
char convert_to_char(MoveResult val)
{
  switch(val)
  {
  case MoveResult::BETRAY:
    return '0';
  case MoveResult::COOPERATE:
    return '1';
  }
  assert(false);
}
}

MoveResult CleverStrategy::move( )
{
  if ( n == 0 )
  {
    choice = MoveResult::COOPERATE;
  }
  else
  {
    std::string buffer(3, '0');

    int32_t res1 = history_result[n - 1][idx];
    int32_t res2 = 0;
    MoveResult choice1 = history_choice[n - 1][idx];
    MoveResult choice2 = (choice1==MoveResult::COOPERATE) ? MoveResult::BETRAY : MoveResult::COOPERATE;

    buffer[0] = convert_to_char(history_choice[n - 1][0]);
    buffer[1] = convert_to_char(history_choice[n - 1][1]);
    buffer[2] = convert_to_char(history_choice[n - 1][2]);

    buffer[idx] = '0' + int32_t(choice2);

    auto it = my_rule_map.find(buffer);

    res2 = ((it->second)[idx]) - '0';

    if ( res2 > res1 )
    {
      choice = choice2;
    }
    else
    {
      choice = choice1;
    }
  }
  n++;
  return choice;
}

void CleverStrategy::set_history(std::array<int32_t, 3> current_result, std::array<MoveResult, 3> current_choice)
{
  history_result.push_back(current_result);
  history_choice.push_back(current_choice);
}

CleverStrategy::CleverStrategy(const std::map<std::string, std::string> &rule_map, int32_t input_idx)
{
  my_rule_map = rule_map;
  idx = input_idx;
}
