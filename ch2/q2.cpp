#include <iostream>
#include <list>

// given k and a list, find its kth to last element

// returns an iterator to kth to last element of list
template<typename Type>
auto list_kth_last_iterator(std::list<Type>& list, typename std::list<Type>::size_type k){
  // it will walk until end of list is reached
  auto it         {std::begin(list)};
  // lagging_it will be k steps behind it
  auto lagging_it {std::begin(list)};

  // it is moved k steps ahead
  for (decltype(k) i {0}; i < k; i++){
    ++it;
  }

  // now both iterators step ahead until it reaches end of list
  while (it != std::end(list)){
    ++it;
    ++lagging_it;
  }

  // then we return lagging_it, which is k steps behind end of list
  return lagging_it;
}

int main(int argc, char** argv){
  if (argc > 2){
    unsigned long k {std::stoul(argv[1])};
    
    std::list<std::string> list {argv + 2, argv + argc};

    auto kth {list_kth_last_iterator(list, k)};

    std::cout << *kth << '\n';
  }
  
  return 0;
}
