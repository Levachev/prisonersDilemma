#pragma once
#include "DefaultStrategy.h"
#include "SimpleStrategy.h"
#include "SmartStrategy.h"
#include "SnitchStrategy.h"
#include "MetaStrategy.h"
#include "CleverStrategy.h"
#include "Factory.h"
#include <iostream>
#include "Mode.h"


void rule_map_init(std::map<std::string, std::string> &rule_map);

void factory_store(Factory &factory);

bool parsing_input(int argc, char *argv[], std::vector<std::string> &vec_of_strategy, Mode &mod, int32_t &steps, const Factory &factory);