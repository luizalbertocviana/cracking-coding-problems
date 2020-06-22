#include <StackSet.hpp>

#include <iostream>

// implement three stacks using a single array

int main(){
  StackSet<int, 3> stk_set {};

  for (int i {0}; i < 20; ++i){
    stk_set.push(i % 3, i);
  }

  for (unsigned i {0}; i < 3; ++i){
    std::cout << "removing content of stack " << i << ":\n";

    while(!stk_set.empty(i)){
      auto opt {stk_set.pop(i)};
      
      std::cout << *opt << ' ';
    }

    std::cout << '\n';
  }

  return 0;
}
