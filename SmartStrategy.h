#pragma once
#include "IStrategy.h"

class SmartStrategy : public IStrategy
{
  MoveResult choice;

  int32_t n=0;
  
  int32_t idx;

  std::vector<std::array<MoveResult, 3>> history_choice;

  std::vector<std::array<int32_t, 3>> history_result;

 public:
  void set_history(std::array<int32_t, 3> current_result, std::array<MoveResult, 3> current_choice) override;
  
  MoveResult move() override;

  SmartStrategy(const std::map<std::string, std::string> &rule_map, int32_t input_idx);

};