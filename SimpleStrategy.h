#pragma once

#include "IStrategy.h"

class SimpleStrategy : public IStrategy
{

 public:
  void set_history(std::array<int32_t, 3> current_result, std::array<MoveResult, 3> current_choice) override;
  
  MoveResult move() override;

  SimpleStrategy(const std::map<std::string, std::string> &rule_map, int32_t ind);
};