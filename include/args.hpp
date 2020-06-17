#pragma once

#include <string>
#include <vector>

std::vector<std::string> get_args(int argc, char** argv){
  return {argv, argv + argc};
}
