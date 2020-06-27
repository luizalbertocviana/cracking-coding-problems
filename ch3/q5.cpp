#include <args.hpp>

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

// sort a stack using an auxiliary stack; smaller elements should be
// at the top, bigger elements should be at the bottom

// moves the element on top of first stack to the top of second
template<typename Type>
void move_top(std::stack<Type>& from, std::stack<Type>& to){
  to.push(from.top());
  from.pop();
}

// sorts a stack using an auxiliary stack
template<typename Type>
void sort_stack(std::stack<Type>& stk){
  // creates auxiliary stack
  std::stack<Type> aux_stk {};

  // moves all stk content to aux_stk
  while (!stk.empty()){
    move_top(stk, aux_stk);
  }

  // performs an insertion sort
  while (!aux_stk.empty()){
    // moves aux_stk top to copy
    Type copy {aux_stk.top()};
    aux_stk.pop();

    // moves content from stk to aux_stk until stk top is suitable for
    // receive copy
    while (!stk.empty() && copy > stk.top()){
      move_top(stk, aux_stk);
    }

    // then put copy on top of stk
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
