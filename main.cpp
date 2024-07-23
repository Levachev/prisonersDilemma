#include "Game.h"
#include "func.h"

int main(int argc, char *argv[])
{
  std::cout<<std::endl;

  std::map<std::string, std::string> rule_map;
  rule_map_init(rule_map);

  Factory factory;
  factory_store(factory);

  std::vector<std::string> vec_of_strategy;

  Mode mod = Mode::FAST;

  int32_t steps = 0;

  if ( !parsing_input(argc, argv, vec_of_strategy, mod, steps, factory))
  {
    return 0;
  }

  Game game(vec_of_strategy, steps, mod, rule_map);
  
  game.do_game(factory);

  return 0;
}
