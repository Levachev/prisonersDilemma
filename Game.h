#pragma once
#include <vector>
#include <map>
#include "Factory.h"
#include "MoveResult.h"
#include "Mode.h"
#include <cassert>

class Game
{
  std::array<MoveResult, 3> current_choice;
  
  std::array<int32_t, 3> current_result;

  std::map<std::string, std::string> rule_map;

  std::array<int32_t, 3> sum_strategy={0};

  Mode type;

  int32_t steps = 0;

  std::vector<std::string> strategy_names;

  void tournament(const Factory &factory);

  void detailed(const Factory &factory);
  
  void fast(const Factory &factory);

  void make_step(std::shared_ptr<IStrategy> &first_strategy, std::shared_ptr<IStrategy> &second_strategy, std::shared_ptr<IStrategy> &third_strategy);

  std::vector<int32_t> fast_process(int32_t steps, std::shared_ptr<IStrategy> &strategy1, std::shared_ptr<IStrategy> &strategy2, std::shared_ptr<IStrategy> &strategy3);

  std::vector<int32_t> detailed_process(std::shared_ptr<IStrategy> &strategy1, std::shared_ptr<IStrategy> &strategy2, std::shared_ptr<IStrategy> &strategy3);

 public:
  Game(std::vector<std::string> input_strategy_names, int32_t input_steps, Mode input_type, const std::map<std::string, std::string> &input_rule_map);

  void do_game(const Factory &factory);

  
};