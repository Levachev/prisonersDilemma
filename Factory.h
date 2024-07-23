#pragma once

#include "IStrategy.h"

#include <memory>

class ICreator
{
 public:
  virtual ~ICreator( ) = default;

  virtual std::shared_ptr<IStrategy> create(const std::map<std::string, std::string> &rule_map, int idx) = 0;
};

template < typename T >
class Creator : public ICreator
{
 public:
  std::shared_ptr<IStrategy> create(const std::map<std::string, std::string> &rule_map, int idx)
  {
    return std::make_shared<T>(rule_map, idx);
  }
};

class Factory
{
 public:
  void register_creator(std::string strategy_name, std::shared_ptr<ICreator> creator);
  std::shared_ptr<IStrategy> create(const std::string &strategy_name, const std::map<std::string, std::string> &rule_map, int idx) const;
  bool can_create(std::string strategy_name) const;

 private:
  std::map<std::string, std::shared_ptr<ICreator>> factory_map_;
};