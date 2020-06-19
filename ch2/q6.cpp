#include <args.hpp>

#include <iostream>
#include <list>

// implement a function to check whether a linked list is a palindrome

// this function does just that (it is a little more general,
// actually)
template<typename Iterator>
bool is_palindrome(Iterator it, Iterator end){
  // as end points to the first position after the region of interest,
  // we decrement end before initialization of it2
  --end;
  auto it2 {end};

  // we assume it2 is not before it; we stop when it is not after it2
  bool it_after_it2 {it != it2};

  // this sets stop condition to false when it == it2
  auto check {[&it, &it2, &it_after_it2](){
                if (it == it2){
                  it_after_it2 = false;
                }
              }};

  while (it_after_it2){
    // if contents are different, return false
    if (*it != *it2){
      return false;
    }

    // region has even size: we check stop condition just after
    // incrementing it
    ++it;
    check();

    // region has odd size: we check stop condition just after
    // decrementing it2
    --it2;
    check();
  }

  return true;
}

int main(int argc, char** argv){
  auto args {get_args(argc, argv)};

  if (args.size() == 2){
    std::string str {args[1]};
    
    std::list<char> list {std::cbegin(str), std::cend(str)};

    if (is_palindrome(std::cbegin(list), std::cend(list))){
      std::cout << str << " is a paliindrome\n";
    }
    else{
      std::cout << str << " is not a palindrome\n";
    }
  }
  
  return 0;
}
