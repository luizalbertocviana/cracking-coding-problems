#include <algorithm>
#include <iostream>
#include <sstream>

// implement a basic string compression using the counts of
// consecutive repeated chars

// template variable holding a function that tests whether its
// arguments are different
template<typename Type>
constexpr const auto different {[](Type a, Type b) {return a != b;}};

// compress str, and returns str in case compression procedure did not
// produce an smaller string
std::string compress_string(const std::string& str){
  // we are going to build the compressed string using a string stream
  std::stringstream compressed {};

  // establishing a search for the first pair of consecutive
  // characters different from each other
  auto search_start {std::cbegin(str)};
  auto it           {std::adjacent_find(search_start, std::cend(str), different<char>)};

  // while we did not walk the entire str ...
  while (it != std::cend(str)){
    // we add the first char of the pair ...
    compressed << *it;
    // and the number of occurrences of that char
    compressed << std::distance(search_start, it + 1);

    // then we set the new search, starting at the second char of the pair
    search_start = it + 1;
    it           = std::adjacent_find(search_start, std::cend(str), different<char>);
  }

  // when the loop exits, we still need to consider the suffix of str
  // of equal chars; as it == std::cend(str), it - 1 is the last char
  // of str
  compressed << *(it - 1);
  compressed << std::distance(search_start, it);

  // at last, we extract the contents of compressed ...
  std::string result {compressed.str()};

  // and return it if it is shorter than str
  return result.size() < str.size() ? result : str;
}

int main(int argc, char** argv){
  if (argc == 2){
    std::string str {argv[1]};

    auto compressed {compress_string(str)};

    std::cout << "compressing " << str << " as " << compressed << '\n';
  }

  return 0;
}
