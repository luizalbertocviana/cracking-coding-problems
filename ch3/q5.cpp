#include <args.hpp>

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

template<typename Type>
void move_top(std::stack<Type>& from, std::stack<Type>& to){
  to.push(from.top());
  from.pop();
}

template<typename Type>
void sort_stack(std::stack<Type>& stk){
  std::stack<Type> auxiliar_stk {};

  while (!stk.empty()){
    move_top(stk, auxiliar_stk);
  }

  while (!auxiliar_stk.empty()){
    Type copy {auxiliar_stk.top()};
    auxiliar_stk.pop();

    while (!stk.empty() && copy > stk.top()){
      move_top(stk, auxiliar_stk);
    }

    stk.push(copy);
  }
}

int main(int argc, char** argv){
  auto args {get_args(argc, argv)};

  if (args.size() > 1){
    std::vector<int> int_args {};
    int_args.reserve(args.size() - 1);

    std::transform(std::cbegin(args) + 1, std::cend(args), std::back_inserter(int_args),
                   [](auto& str) {return std::stoi(str);});

    std::stack<int> stk {};

    std::cout << "inserting elements into stack (first will be the last inserted)\n";

    for (auto it {std::crbegin(int_args)}; it != std::crend(int_args); ++it){
      stk.push(*it);
    }

    sort_stack(stk);

    std::cout << "removing elements from stack:\n";

    while (!stk.empty()){
      std::cout << stk.top() << ' ';

      stk.pop();
    }

    std::cout << '\n';
  }

  return 0;
}
