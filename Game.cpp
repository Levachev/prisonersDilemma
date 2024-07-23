#include <iostream>
#include "Game.h"

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

std::string convert_to_string(MoveResult val)
{
  switch(val)
  {
  case MoveResult::BETRAY:
    return "betray";
    break;
  case MoveResult::COOPERATE:
    return "cooperate";
    break;
  }
  assert(false);
}
}

void Game::make_step(std::shared_ptr<IStrategy> &first_strategy, std::shared_ptr<IStrategy> &second_strategy, std::shared_ptr<IStrategy> &third_strategy)
{
  std::string buffer(3, '0');
  current_choice[0]=first_strategy->move();
  current_choice[1]=second_strategy->move();
  current_choice[2]=third_strategy->move();

  for(int32_t i=0;i<3;i++)
  {
    buffer[i] = convert_to_char(current_choice[i]);
  }

  auto it = rule_map.find(buffer);
  for ( int32_t j = 0; j < 3; j++ )
  {
    sum_strategy[j] += ((it->second)[j]) - '0';
  }

  current_result[0]=((it->second)[0]) - '0';
  current_result[1]=((it->second)[1]) - '0';
  current_result[2]=((it->second)[2]) - '0';

  first_strategy->set_history(current_result, current_choice);
  second_strategy->set_history(current_result, current_choice);
  third_strategy->set_history(current_result, current_choice);
}

std::vector<int32_t> Game::fast_process(int32_t steps, std::shared_ptr<IStrategy> &strategy1, std::shared_ptr<IStrategy> &strategy2, std::shared_ptr<IStrategy> &strategy3)
{
  std::vector<int32_t> result;
  srand(time(NULL));
  //std::vector<MoveResult> current_choice(3, MoveResult::BETRAY);
  //std::vector<int32_t> current_result(3, 0);

  for ( int32_t i= 0; i < steps; i++ )
  {
    make_step(strategy1, strategy2, strategy3);
  }

  result.push_back(sum_strategy[0]);
  result.push_back(sum_strategy[1]);
  result.push_back(sum_strategy[2]);
  return result;
}

std::vector<int32_t> Game::detailed_process(std::shared_ptr<IStrategy> &strategy1, std::shared_ptr<IStrategy> &strategy2, std::shared_ptr<IStrategy> &strategy3)
{
  std::vector<int32_t> result;
  srand(time(NULL));
  //std::vector<MoveResult> current_choice(3, MoveResult::BETRAY);
  //std::vector<int32_t> current_result(3, 0);

  while(true)
  {
    make_step(strategy1, strategy2, strategy3);

    std::cout<<"current choice of first strategy - "<<convert_to_string(current_choice[0])<<std::endl;
    std::cout<<"current choice of second strategy - "<<convert_to_string(current_choice[1])<<std::endl;
    std::cout<<"current choice of third strategy - "<<convert_to_string(current_choice[2])<<std::endl;

    std::cout<<std::endl;

    std::cout<<"current result of first strategy - "<<current_result[0]<<std::endl;
    std::cout<<"current result of second strategy - "<<current_result[1]<<std::endl;
    std::cout<<"current result of third strategy - "<<current_result[2]<<std::endl;

    std::cout<<std::endl;

    std::cout<<"sum of first strategy - "<<sum_strategy[0]<<std::endl;
    std::cout<<"sum of second strategy - "<<sum_strategy[1]<<std::endl;
    std::cout<<"sum of third strategy - "<<sum_strategy[2]<<std::endl;

    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    int32_t flag_to_break=0;
    std::string input_string;
    do {
      std::cout<<"Press Enter to continue,  enter \"quit\""<<'\n';
      getline(std::cin, input_string, '\n');
      if(input_string == "quit")
      {
        flag_to_break=1;
        break;
      }
    }
    while (!(input_string.empty()));
    if(flag_to_break==1)
    {
      break;
    }
  }

  result.push_back(sum_strategy[0]);
  result.push_back(sum_strategy[1]);
  result.push_back(sum_strategy[2]);
  return result;
}



void Game::do_game(const Factory &factory)
{
  switch(type)
  {
  case Mode::DETAILED:
    detailed(factory);
    break;
  case Mode::FAST:
    fast(factory);
    break;
  case Mode::TOURNAMENT:
    tournament(factory);
    break;
  default:
    assert(false);
  }
}

void Game::tournament(const Factory &factory)
{
  int32_t size=strategy_names.size();
  std::vector<int32_t> data(size, 0);
  for(int32_t i=0;i<size;i++){
    for(int32_t j=i+1;j<size;j++){
      for(int32_t k=j+1;k<size;k++){
        auto strategy1 = factory.create(strategy_names[i], rule_map, 0);
        auto strategy2 = factory.create(strategy_names[j], rule_map, 1);
        auto strategy3 = factory.create(strategy_names[k], rule_map, 2);
        std::vector<int32_t> result=fast_process(steps, strategy1, strategy2, strategy3);
        data[i]+=result[0];
        data[j]+=result[1];
        data[k]+=result[2];
      }
    }
  }

  std::cout<<std::endl<<"result of game:"<<std::endl;

  for(int32_t i=0;i<size;i++)
  {
    std::cout<<"sum of "<<strategy_names[i]<<" strategy - "<<data[i]<<" pts"<<std::endl;
  }

  int32_t max=-1;
  int32_t maxind=0;

  for(int32_t i=0;i<size;i++)
  {
    if ( max < data[i] )
    {
      max = data[i];
      maxind = i;
    }
  }
  std::cout<<std::endl<<"winner - "<<strategy_names[maxind]<<std::endl;
}

void Game::detailed(const Factory &factory)
{
  int32_t size=strategy_names.size();
  auto strategy1 = factory.create(strategy_names[0], rule_map, 0);
  auto strategy2 = factory.create(strategy_names[1], rule_map, 1);
  auto strategy3 = factory.create(strategy_names[2], rule_map, 2);
  std::vector<int32_t> result=detailed_process(strategy1, strategy2, strategy3);
  int32_t max=-1;
  int32_t maxind=0;

  for(int32_t i=0;i<size;i++)
  {
    if ( max < result[i] )
    {
      max = result[i];
      maxind = i;
    }
  }

  std::cout<<std::endl<<"result of game:"<<std::endl;

  for(int32_t i=0;i<3;i++)
  {
    std::cout<<"sum of "<<strategy_names[i]<<" strategy - "<<result[i]<<" pts"<<std::endl;
  }
  std::cout<<std::endl<<"winner - "<<strategy_names[maxind]<<std::endl;
}

void Game::fast(const Factory &factory)
{
  int32_t size=strategy_names.size();

  auto strategy1 = factory.create(strategy_names[0], rule_map, 0);
  auto strategy2 = factory.create(strategy_names[1], rule_map, 1);
  auto strategy3 = factory.create(strategy_names[2], rule_map, 2);
  std::vector<int32_t> result=fast_process(steps, strategy1, strategy2, strategy3);
  int32_t max=-1;
  int32_t maxind=0;

  for(int32_t i=0;i<size;i++)
  {
    if ( max < result[i] )
    {
      max = result[i];
      maxind = i;
    }
  }

  std::cout<<std::endl<<"result of game:"<<std::endl;

  for(int32_t i=0;i<3;i++)
  {
    std::cout<<"sum of "<<strategy_names[i]<<" strategy - "<<result[i]<<" pts"<<std::endl;
  }
  std::cout<<std::endl<<"winner - "<<strategy_names[maxind]<<std::endl;
}

Game::Game(std::vector<std::string> input_strategy_names, int32_t input_steps, Mode input_type, const std::map<std::string, std::string> &input_rule_map)
{
  rule_map=input_rule_map;
  strategy_names=input_strategy_names;
  steps=input_steps;
  type=input_type;
}
