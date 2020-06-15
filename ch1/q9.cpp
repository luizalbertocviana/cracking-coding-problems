#include <iostream>

// given two strings, decide whether one is rotation of the other, eg
// banana is rotatio of nabana

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
      bool is_rotation {true};

      // we iterate through str2 ...
      for (size_type i {0}; i < str2.size(); i++){
        // and compare it with the rotation of str1 starting at
        // check_start; if one char mismatches, we flag that
        if (str1[(check_start + i) % str1.size()] != str2[i]){
          is_rotation = false;
        }
      }

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
  if (argc == 3){
    std::string str1 {argv[1]};
    std::string str2 {argv[2]};

    if (rotation(str1, str2)){
      std::cout << str1 << " is a rotation of " << str2 << '\n';
    }
    else{
      std::cout << str1 << " is not a rotation of " << str2 << '\n';
    }
  }

  return 0;
}
