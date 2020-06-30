#include <queue.hpp>

#include <range.hpp>

#include <iostream>

// implement a queue using two stacks

int main(){
  int n {10};

  std::cout << "inserting numbers from 0 to " << n << ":\n";

  Queue<int> queue {};

  for (auto i : range(0, n + 1)){
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
