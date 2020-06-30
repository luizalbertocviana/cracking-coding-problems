#include <StackSequence.hpp>

#include <range.hpp>

#include <iostream>

// implement three stacks using a single array

int main(){
  StackSequence<int, 3> stk_set {};

  for (auto i : range(0, 20)){
    stk_set.push(i % 3, i);
  }

  for (auto i : range(0, 3)){
    std::cout << "removing content of stack " << i << ":\n";

    while(!stk_set.empty(i)){
      auto opt {stk_set.pop(i)};
      
      std::cout << *opt << ' ';
    }

    std::cout << '\n';
  }

  return 0;
}
