#include <algorithm>
#include <iostream>
#include <list>

#include <args.hpp>

// given a (possibly unsorted) linked list of elements, remove
// dupliacte elements from it

// this function should remove duplicate elements from any iterable
// collection
template<typename Collection>
void remove_duplicates(Collection& list){
  // iterators to mark current element and search end positions
  auto it  {std::begin(list)};
  auto end {std::end(list)};

  // while current element is within search range ...
  while (it != end){
    // we save it content ...
    auto e {*it};
    // and we remove e from (it + 1) onwards; notice we also increment
    // it; this was written this way because when Collection is list,
    // it + 1 is not a valid expression
    end = std::remove(++it, end, e);
  }

  // notice that std::remove does not perform the actual removal of
  // elements; instead, it returns an end iterator such that every
  // non-deleted element is before end

  // now we delete elements from end to the original end of list
  list.erase(end, std::end(list));
}

int main(int argc, char** argv){
  auto args {get_args(argc, argv)};

  if (args.size() > 1){
    std::list<std::string> list {std::begin(args) + 1, std::end(args)};

    remove_duplicates(list);

    for (auto s : list){
      std::cout << s << ' ';
    }

    std::cout << '\n';
  }

  return 0;
}
