#include "Factory.h"

void Factory::register_creator(std::string strategy_name, std::shared_ptr<ICreator> creator)
{
  factory_map_.insert({std::move(strategy_name), std::move(creator)});
}

bool Factory::can_create(std::string strategy_name) const
{
  return factory_map_.find(strategy_name) != factory_map_.end();
}

std::shared_ptr<IStrategy> Factory::create(const std::string &strategy_name, const std::map<std::string, std::string> &rule_map, int idx) const
{
  auto it = factory_map_.find(strategy_name);
  if ( it == factory_map_.end())
  {
    return nullptr;
  }
  return it->second->create(rule_map, idx);
}