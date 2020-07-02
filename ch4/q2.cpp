#include <bstree.hpp>

#include <vector>
#include <functional>

// given a sorted array of unique elements, write an algorithm to
// create a binary search tree with minimal height

// this function does that and a little more
template<typename Iterator, typename Val>
auto bstree_from_sorted(const Iterator& begin, const Iterator& end, const Val& default_value){
  // we are going to use Key as the type of elements within range
  // [begin, end)
  using Key      = decltype(*begin);
  // we are going to use a recursive function to perform the insertions
  using Function = std::function<void(const Iterator&, const Iterator&)>;

  // an empty BSTree
  BSTree<Key, Val> bst {};

  Function inserter {[&bst, &default_value, &inserter](const auto& begin, const auto& end) {
                       // if range is not empty
                       if (begin < end){
                         // we calculate half of the range length
                         auto length      {std::distance(begin, end)};
                         auto half_length {length / 2};

                         // we insert the middle element (odd length)
                         // or the first element of second half (even
                         // length)
                         bst.insert(*(begin + half_length), default_value);

                         // we recurse into each half, excluding the
                         // element that was just inserted
                         inserter(begin, begin + half_length);
                         inserter(begin + half_length + 1, end);
                       }
                     }};

  // we begin the insertion process to the whole range
  inserter(begin, end);

  // at the end, we return the BSTree
  return bst;
}

int main(){
  std::vector<int> vec {1,2,3,4,5,6,7};

  auto bst {bstree_from_sorted(std::cbegin(vec), std::cend(vec), 0)};

  return 0;
}
