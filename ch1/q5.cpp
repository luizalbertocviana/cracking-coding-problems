#include <algorithm>
#include <iostream>

#include <args.hpp>

// given two strings, decide whether their edit distance is at most one

bool nearly_equal(const std::string& str1, const std::string& str2){
  // first we are going to decide which string is the shorter one
  auto size1          {str1.size()};
  auto size2          {str2.size()};
  const auto& shorter {size1 <= size2 ? str1 : str2};
  const auto& longer  {size1 > size2  ? str1 : str2};
  
  // if sizes differ by at least two, edit distance is at least two
  if (longer.size() - shorter.size() > 1){
    return false;
  }
  // otherwise sizes differ by at most one
  else{
    // we find the first positions in which shorter and longer differ
    auto[shorter_it, longer_it] {std::mismatch(std::cbegin(shorter), std::cend(shorter), std::cbegin(longer))};

    // if shorter is a prefix of longer, we return true since we know
    // they differ by at most a deletion at the end of longer
    if (shorter_it == std::cend(shorter)){
      return true;
    }
    // otherwise, shorter is not a prefix of longer, that is, shorter
    // differs from the corresponding prefix of longer at shorter_it
    else{
      // if longer has one mmore char than shorter, we expect that
      // shorter is obtained from longer by exactly one deletion; this
      // way, we verify whether shorter (from shorter_it on) is the
      // suffix of longer that begins at longer_it + 1
      if (longer.size() > shorter.size()){
        return std::equal(shorter_it, std::cend(shorter), longer_it + 1);
      }
      // if shorter and longer have the same size, we expect that
      // shorter is obtained from longer by exactly the char change we
      // already have seen; this way, we verify whether shorter is
      // equal to longer past that char change
      else{
        return std::equal(shorter_it + 1, std::cend(shorter), longer_it + 1);
      }
    }
  }
}

int main(int argc, char** argv){
  auto args {get_args(argc, argv)};

  if (args.size() == 3){
    std::string str1 {args[1]};
    std::string str2 {args[2]};

    if (nearly_equal(str1, str2)){
      std::cout << str1 << " is nearly equal to " << str2 << '\n';
    }
    else{
      std::cout << str1 << " is quite different from " << str2 << '\n';
    }
  }

  return 0;
}
