#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <optional>

// given a string, decide whether it is a palindrome permutation

// builds a map counting the characters of a string
std::map<char, unsigned> count_chars(const std::string& str){
  // this will hold the char count we are going to do
  std::map<char, unsigned> count {};

  // and this do the counting
  for (char c : str){
    count[c]++;
  }

  return count;
}

// decides whether a string is a palindrome permutation. Optional
// argument should point to a char count of str
bool palindrome_permutation(const std::string& str, const std::map<char, unsigned>* char_count_ = nullptr){
  // verifies whether char_count_ is nullptr. If it is, does a char
  // counting of str
  auto& char_count {char_count_ ? *char_count_ : count_chars(str)};
  
  // if str has even length, it suffices to verify whether every char
  // appears an even number of times
  if (str.size() % 2 == 0){
    return std::all_of(std::cbegin(char_count), std::cend(char_count),
                       [](const auto& pair) {return pair.second % 2 == 0;});
  }
  // if there is any char with odd counting, there should be exactly
  // one of them otherwise str is not a palindrome permutation
  else{
    // we are going to flag a second occurrence of a char with odd
    // counting
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
  // first we do a char counting of str
  auto char_count {count_chars(str)};

  // if str is a palindrome permutation, we are going to build a
  // related palindrome
  if (palindrome_permutation(str, &char_count)){
    // we use a deque of chars to represent a palindrome so we have
    // constant time insertion in both palindrome ends
    std::deque<char> palindrome {};
    // we verify whether there is a char with odd counting in str
    auto it {std::find_if(std::begin(char_count), std::end(char_count),
                          [](const auto& pair) {return pair.second % 2 != 0;})};

    // if there is such a char, it should occur in the middle of palindrome
    if (it != std::end(char_count)){
      palindrome.push_back(it->first);
      // we update the counting
      it->second--;
      // if this char count reaches zero, it is removed from char_count
      if (it->second == 0){
        char_count.erase(it);
      }
    }

    // notice that, from now on, every char in char_count has an even count

    // while there are chars to be inserted into palindrome
    while (!char_count.empty()){
      // for each char in char_count
      for (auto&[c, count] : char_count){
        // adds c in both ends of palindrome
        palindrome.push_back(c);
        palindrome.push_front(c);
        // updates counting
        count -= 2;
        // if c count reaches zero, remove it
        if (count == 0){
          char_count.erase(c);
          // since we have altered char_count, the iterators used in
          // this loop have become invalid, so we break the loop
          break;
        }
      }
    }
    
    // now we build a string from the deque iterators
    std::string palindrome_str {std::cbegin(palindrome), std::cend(palindrome)};
    return palindrome_str;
  }
  // if str is not a palindromme permutation, we return no palindrome
  else{
    return {};
  }
}

int main(int argc, char** argv){
  if (argc == 2){
    std::string str {argv[1]};

    auto palindrome {build_palindrome(str)};

    if (palindrome){
      std::cout << str << " is a palindrome permutation: " << *palindrome << '\n';
    }
    else{
      std::cout << str << " is not a palindrome permutation\n";
    }
  }

  return 0;
}
