#include <iostream>
#include <map>
#include <set>

#include <args.hpp>

// given two strings, decide whether one is a permutation of the other

bool permutation(const std::string& str1, const std::string& str2){
  // every char we are going to see will be stored at al_chars
  std::set<char> all_chars        {};
  // here we will store the char counts of str1 and str2
  std::map<char, unsigned> count1 {};
  std::map<char, unsigned> count2 {};

  // every char of str1 is registered and counted
  for (char c : str1){
    all_chars.insert(c);
    count1[c]++;
  }
  // every char of str2 is registered and counted
  for (char c : str2){
    all_chars.insert(c);
    count2[c]++;
  }
  // now we verify whether every char we have has the same count in
  // str1 and str2
  for (char c : all_chars){
    if (count1[c] != count2[c]){
      return false;
    }
  }
  return true;
}

int main(int argc, char** argv){
  auto args {get_args(argc, argv)};

  if (args.size() == 3){
    std::string str1 {args[1]};
    std::string str2 {args[2]};

    if (permutation(str1, str2)){
      std::cout << str1 << " is a permutation of " << str2 << '\n';
    }
    else{
      std::cout << str1 << " is not a permutation of " << str2 << '\n';
    }
  }
  return 0;
}
