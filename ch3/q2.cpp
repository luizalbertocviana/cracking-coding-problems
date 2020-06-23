#include <args.hpp>
#include <StackMin.hpp>

#include <algorithm>
#include <iostream>

// implement a stack that keeps track of its current minimum element;
// insertion, removal, access to top and to minimum element should
// cost O(1)

int main(int argc, char** argv){
  auto args {get_args(argc, argv)};

  if (args.size() > 1){
    std::vector<long> long_args {};
    long_args.reserve(args.size() - 1);

    std::transform(std::cbegin(args) + 1, std::cend(args), std::back_inserter(long_args),
                   [](const auto& str) {return std::stol(str);});
    
    StackMin<long> min_stk {};

    std::cout << "minimum elements after each insert:\n";
    for (auto e : long_args){
      min_stk.push(e);

      auto opt {min_stk.min()};

      std::cout << *opt << ' ';
    }

    std::cout << '\n';

    std::cout << "minimum elements after each removal:\n";
    while (!min_stk.empty()){
      min_stk.pop();

      auto opt {min_stk.min()};

      if (opt){
          std::cout << *opt << ' ';
      }
    }
  }
  
  std::cout << '\n';
  
  return 0;
}
