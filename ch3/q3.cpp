#include <StackSet.hpp>

#include <iostream>

// develoop a data structure consisting of a sequence of stacks with
// limited capacity; push and pop should behave identically to a
// single stack; implement pop_at, which pops an element from a
// specific sub-stack

int main(){
  StackSet<int, 5> stk_set {};

  int n {30};

  std::cout << "inserting ints from 1 to " << n << ":\n";

  for (int i {1}; i <= n; ++i){
    stk_set.push(i);
  }

  int k {2};

  std::cout << "removing elements from stack " << k << ":\n";

  auto opt {stk_set.pop_at(k)};
  while (opt){
    std::cout << *opt << ' ';

    opt = stk_set.pop_at(k);
  }
  std::cout << '\n';

  std::cout << "removing remaining elements from stack:\n";

  while (!stk_set.empty()){
    auto opt {stk_set.pop()};

    std::cout << *opt << ' ';
  }
  std::cout << '\n';

  return 0;
}
