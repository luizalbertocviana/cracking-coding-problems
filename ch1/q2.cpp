#include <iostream>
#include <map>
#include <set>

// given two strings, decide if one is a permutation of the other

bool permutation(const std::string& str1, const std::string& str2){
  std::set<char> all_chars{};
  std::map<char, unsigned> count1{};
  std::map<char, unsigned> count2{};

  for (char c : str1){
    all_chars.insert(c);
    count1[c]++;
  }
  for (char c : str2){
    all_chars.insert(c);
    count2[c]++;
  }
  for (char c : all_chars){
    if (count1[c] != count2[c]){
      return false;
    }
  }
  return true;
}

int main(int argc, char** argv){
  if (argc == 3){
    std::string str1{argv[1]};
    std::string str2{argv[2]};

    if (permutation(str1, str2)){
      std::cout << str1 << " is a permutation of " << str2 << '\n';
    }
    else{
      std::cout << str1 << " is not a permutation of " << str2 << '\n';
    }
  }
  return 0;
}
