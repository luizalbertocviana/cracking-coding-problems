#include <iostream>
#include <set>
#include <string>

#include <args.hpp>

// determine whether a string has all unique characters

bool unique(const std::string& col){
  // we are going to use a set to determine whether we see a character
  // more than once
  std::set<char> set {};
  for (char c : col){
    // if c is already present, we have seen it more than once, and
    // return false
    if (set.count(c)){
      return false;
    }
    // otherwise we are seeing c for the first time, so we register it
    else{
      set.insert(c);
    }
  }
  // if no character of col was seen more than once, we return true
  return true;
}

int main(int argc, char** argv){
  auto args {get_args(argc, argv)};

  if (args.size() == 2){
    std::string str {args[1]};

    if (unique(str)){
      std::cout << str << " has no repeated characters\n";
    }
    else{
      std::cout << str << " has repeated characters\n";
    }
  }

  return 0;
}
