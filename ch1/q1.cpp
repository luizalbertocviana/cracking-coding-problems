#include <iostream>
#include <set>
#include <string>

// determine whether a string has all unique characters

bool unique(const std::string& col){
  std::set<char> set{};
  for(char c : col){
    if (set.count(c)){
      return false;
    }
    else{
      set.insert(c);
    }
  }
  return true;
}

int main(int argc, char** argv){
  if (argc == 2){
    std::string str{argv[1]};

    if (unique(str)){
      std::cout << str << " has no repeated characters\n";
    }
    else{
      std::cout << str << " has repeated characters\n";
    }
  }

  return 0;
}
