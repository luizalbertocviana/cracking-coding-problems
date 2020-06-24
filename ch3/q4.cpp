#include <queue.hpp>

#include <iostream>

// implement a queue using two stacks

int main(){
  int n {10};

  std::cout << "inserting numbers from 0 to " << n << ":\n";

  Queue<int> queue {};

  for (int i {0}; i <= n; ++i){
    queue.insert(i);
  }

  std::cout << "removing elements from queue:\n";

  while (!queue.isEmpty()){
    auto opt {queue.remove()};

    std::cout << *opt << ' ';
  }

  std::cout << '\n';

  return 0;
}
