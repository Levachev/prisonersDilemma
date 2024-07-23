#include "func.h"


namespace
{
std::optional<Mode> get_mod(std::string tmp)
{
  if ( tmp == "detailed" )
  {
    return Mode::DETAILED;
  }
  if ( tmp == "fast" )
  {
    return Mode::FAST;
  }
  if ( tmp == "tournament" )
  {
    return Mode::TOURNAMENT;
  }
  return std::nullopt;
}

bool is_digit(std::string tmp)
{
  if(tmp[0]=='0' && tmp.size()>1)
  {
    return false;
  }
  if(tmp.size()==0)
  {
    return false;
  }
  for ( auto i : tmp )
  {
    if ( !(i >= '0' && i <= '9'))
    {
      return false;
    }
  }
  return true;
}

bool is_strategy(const Factory &factory, std::string str)
{
  return factory.can_create(str);
}

void message( )
{
  std::cout << "Error!!!!! Invalid input" << std::endl;
  std::cout << "Input rules :" << std::endl;
  std::cout << "At the start of the program, the following command line arguments are given :" << std::endl;
  std::cout << "\ta) Three (or more - for tournament mode) names of competing strategies." << std::endl;
  std::cout << "\tb) Mode name --mode=[detailed|fast|tournament] (optional, \n\tdefault - detailed for three strategies, tournament for >3 strategies)" << std::endl;
  std::cout << "\tc) Number of simulation steps --steps=<n> (optional)." << std::endl;
  std::cout << "If you do not follow the rules, the program will not work" << std::endl;
}

void my_cast_to_mode(Mode &mod, std::optional<Mode> tmp_mod)
{
  mod = tmp_mod.value();
}
}

bool parsing_input(int argc, char *argv[], std::vector<std::string> &vec_of_strategy, Mode &mod, int32_t &steps, const Factory &factory)
{
  if(argc==1)
  {
    message();
    return false;
  }

  std::string tmp;
  int32_t iter = 1;

  while ( argv[iter][0] != '-' && iter<argc-1)
  {
    
    tmp = argv[iter];
    if ( !(is_strategy(factory, tmp)))
    {
      message();
      return false;
    }
    vec_of_strategy.push_back(tmp);
    ++iter;
  }

  if ( iter < 4 )
  {
    message();
    return false;
  }

  tmp = argv[iter];
  tmp = tmp.substr(0, 7);

  if ( tmp != "--mode=" )
  {
    message();
    return false;
  }

  tmp = argv[iter];
  tmp = tmp.substr(7);
  iter++;

  std::optional<Mode> tmp_mod = get_mod(tmp);

  if ( tmp_mod == std::nullopt )
  {
    message();
    return false;
  }
  my_cast_to_mode(mod, tmp_mod);

  if ( (mod == Mode::FAST || mod == Mode::DETAILED) && vec_of_strategy.size()>3)
  {
    message();
    return false;
  }

  if ( mod == Mode::FAST || mod == Mode::TOURNAMENT )
  {
    if(iter>=argc)
    {
      message();
      return false;
    }
    tmp = argv[iter];
    tmp = tmp.substr(0, 8);

    if ( tmp != "--steps=" )
    {
      message();
      return false;
    }

    tmp = argv[iter];
    tmp = tmp.substr(8);
    iter++;
    if ( !(is_digit(tmp)))
    {
      message();
      return false;
    }

    steps = atoi(tmp.c_str());
  }
  if(iter!=argc)
  {
    message();
    return false;
  }

  return true;
}

void rule_map_init(std::map<std::string, std::string> &rule_map)
{
  rule_map.insert({"111", "777"});
  rule_map.insert({"110", "339"});
  rule_map.insert({"101", "393"});
  rule_map.insert({"011", "933"});
  rule_map.insert({"100", "055"});
  rule_map.insert({"010", "505"});
  rule_map.insert({"001", "550"});
  rule_map.insert({"000", "111"});
}

void factory_store(Factory &factory)
{
  factory.register_creator("default", std::make_shared<Creator<DefaultStrategy>>());
  factory.register_creator("snitch", std::make_shared<Creator<SnitchStrategy>>());
  factory.register_creator("simple", std::make_shared<Creator<SimpleStrategy>>());
  factory.register_creator("smart", std::make_shared<Creator<SmartStrategy>>());
  factory.register_creator("clever", std::make_shared<Creator<CleverStrategy>>());
  factory.register_creator("meta", std::make_shared<Creator<MetaStrategy>>());
}