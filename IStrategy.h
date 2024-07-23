#pragma once
#include <map>
#include <vector>
#include "MoveResult.h"

class IStrategy
{
 public:
  virtual ~IStrategy( ) = default;

  virtual void set_history(std::array<int32_t, 3> current_result, std::array<MoveResult, 3> current_choice) = 0;

  virtual MoveResult move() = 0;
};