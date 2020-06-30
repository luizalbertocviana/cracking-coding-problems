#include <args.hpp>
#include <range.hpp>

#include <algorithm>
#include <iostream>

// given two strings, decide whether one is rotation of the other, eg
// banana is rotation of nabana

// this functions does just that
bool rotation(const std::string& str1, const std::string& str2){
  // rotations must have the same size
  if (str1.size() == str2.size()){
    // we use size_type of string
    using size_type = std::string::size_type;

    // position of str1 from which we start to check
    size_type check_start {0};

    // we increment check_start at each iteration so we compare str2
    // with every possible rotation of str1
    while (check_start < str1.size()){
      // we use this to flag if str2 matches with current rotation of
      // str1
      bool is_rotation {std::all_of(index<size_type>(0), index<size_type>(str2.size()),
                                    [&str1, &str2, check_start](const auto i) {
                                      return str1[(check_start + i) % str1.size()] == str2[i];
                                    })};

      // if str2 indeed matches current rotation of str1, then we
      // return true
      if (is_rotation){
        return true;
      }

      // next iteration we check another rotation of str1
      check_start++;
    }

    // if str2 matches no rotation of str1, then str2 is not a
    // rotation of str1
    return false;
  }
  // otherwise we simply return false
  else{
    return false;
  }
}

int main(int argc, char** argv){
  auto args {get_args(argc, argv)};

  if (args.size() == 3){
    std::string str1 {args[1]};
    std::string str2 {args[2]};

    if (rotation(str1, str2)){
      std::cout << str1 << " is a rotation of " << str2 << '\n';
    }
    else{
      std::cout << str1 << " is not a rotation of " << str2 << '\n';
    }
  }

  return 0;
}
