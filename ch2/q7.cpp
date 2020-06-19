#include <algorithm>
#include <iostream>
#include <list>
#include <set>

// given two singly linked lists, determine whether they have a common
// node, that is, a memory region present in both data structures

// notice that we are going to compare references instead of contents

// this discovers first intersection between general regions; if they
// do not intersect, end of shorter region is returned
template<typename Iterator>
Iterator intersection(Iterator shorter_it, Iterator shorter_end,
                      Iterator longer_it, Iterator longer_end){
  // calculates each region distance
  auto shorter_distance {std::distance(shorter_it, shorter_end)};
  auto longer_distance  {std::distance(longer_it, longer_end)};

  // differece between region distances
  auto difference {longer_distance - shorter_distance};

  // this puts longer_it at the beginning of a subregion of same
  // length as shorter region
  while (difference > 0){
    ++longer_it;

    --difference;
  }

  // if shorter_it == longer_it and shorter_it != shorter_end,
  // intersection was found, so we return it; also, if shorter_it ==
  // shorter_end, shorter region ended with no intersection found, so
  // we return shorter_end
  while (shorter_it != shorter_end && shorter_it != longer_it){
    ++shorter_it;
    ++longer_it;
  }

  return shorter_it;
}

// well, in order to test intersection, I would need to implement an
// intendedly faulty linked list
int main(){
  std::list<int> list1 {};
  std::list<int> list2 {};

  intersection(std::cbegin(list1), std::cend(list1), std::cbegin(list2), std::cend(list2));
  
  std::cout << "I dont know how to test this\n";
}
