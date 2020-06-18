#include <algorithm>
#include <iostream>
#include <list>

#include <args.hpp>

// given a list and a value, partition the list such that all values
// less than value occur before the remaining ones

// this function does just that
template<typename Type>
auto partition(std::list<Type>& list, Type e){
  // we partition the entire list such that every element less than e
  // occurs before every other element
  return std::partition(std::begin(list), std::end(list),
                        [&e](const Type& e1) {return e1 < e;});
}

int main(int argc, char** argv){
  auto args {get_args(argc, argv)};

  if (args.size() > 2){
    std::string e {args[1]};

    std::list<std::string> list {std::begin(args) + 2, std::end(args)};

    partition(list, e);

    for (auto& e : list){
      std::cout << e << ' ';
    }

    std::cout << '\n';
  }
  
  return 0;
}
