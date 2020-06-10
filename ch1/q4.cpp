#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <optional>

// given a string, decide whether it is a palindrome permutation

constexpr const bool debug {false};

// builds a map counting the characters of a string
std::map<char, unsigned> count_chars(const std::string& str){
  std::map<char, unsigned> count {};

  for (char c : str){
    count[c]++;
  }

  return count;
}

// decides whether a string is a palindrome permutation
bool palindrome_permutation(const std::string& str, const std::map<char, unsigned>* char_count_ = nullptr){
  auto char_count {char_count_ ? *char_count_ : count_chars(str)};
  
  if (str.size() % 2 == 0){
    return std::all_of(std::cbegin(char_count), std::cend(char_count),
                       [](const auto& pair) {return pair.second % 2 == 0;});
  }
  else{
    bool seen_one_odd_count {false};

    for (auto[c, count] : char_count){
      if (count % 2 != 0){
        if (seen_one_odd_count){
          return false;
        }
        else{
          seen_one_odd_count = true;
        }
      }
    }

    return true;
  }
}

// returns a palindrome in case string is a palindrome permutation;
// otherwise, returns nothing
std::optional<std::string> build_palindrome(const std::string& str){
  auto char_count {count_chars(str)};

  if constexpr (debug)
                 std::cout << "counted chars\n";

  if (palindrome_permutation(str, &char_count)){
    std::deque<char> palindrome {};
    auto it {std::find_if(std::begin(char_count), std::end(char_count),
                          [](const auto& pair) {return pair.second % 2 != 0;})};
    if constexpr (debug)
                   std::cout << "looked for char with odd counting\n";

    if (it != std::end(char_count)){
      palindrome.push_back(it->first);
      it->second--;
      if (it->second == 0){
        char_count.erase(it);
      }
      if constexpr (debug)
                     std::cout << "inserted odd char at middle\n";
    }

    while (!char_count.empty()){
      for (auto&[c, count] : char_count){
        palindrome.push_back(c);
        palindrome.push_front(c);
        count -= 2;
        if (count == 0){
          char_count.erase(c);
          break;
        }
      }
    }
    if constexpr (debug)
                   std::cout << "inserted remaining chars\n";
    
    std::string palindrome_str {std::cbegin(palindrome), std::cend(palindrome)};
    return palindrome_str;
  }
  else{
    return {};
  }
}

int main(int argc, char** argv){
  if (argc == 2){
    std::string str {argv[1]};

    if constexpr (debug)
                   std::cout << "built string\n";

    auto palindrome {build_palindrome(str)};

    if constexpr (debug)
                   std::cout << "built palindrome\n";

    if (palindrome){
      std::cout << str << " is a palindrome permutation: " << *palindrome << '\n';
    }
    else{
      std::cout << str << " is not a palindrome permutation\n";
    }
  }

  return 0;
}
