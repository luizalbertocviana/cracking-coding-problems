#include <algorithm>
#include <iostream>
#include <list>

#include <args.hpp>

// write a function to delete a node in a list

// removes first occurrence of element from list; returns true iff
// removal did took place
template<typename Type>
bool remove(std::list<Type>& list, Type e){
  // we verify if list has a occurrence of e
  auto it {std::find(std::begin(list), std::end(list), e)};

  // if it has, we erase it and return true
  if (it != std::end(list)){
    list.erase(it);

    return true;
  }
  // otherwise there is nothing to delete, then we return false
  else{
    return false;
  }
}

int main(int argc, char** argv){
  auto args {get_args(argc, argv)};

  if (args.size() > 2){
    std::string e {args[1]};
    std::list<std::string> list {std::begin(args) + 2, std::end(args)};

    remove(list, e);

    for (auto e : list){
      std::cout << e << ' ';
    }

    std::cout << '\n';
  }

  return 0;
}
