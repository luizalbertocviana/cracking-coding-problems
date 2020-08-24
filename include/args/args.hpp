#ifndef args_hpp
#define args_hpp

#include <string>
#include <vector>

std::vector<std::string> get_args(int argc, char** argv){
  return {argv, argv + argc};
}

#endif
