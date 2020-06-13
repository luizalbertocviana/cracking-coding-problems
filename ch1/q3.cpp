#include <iostream>

// replace all occurrences of " " with "%20"

// replaces all occurrences of from in target with to
void replace(std::string& target, const std::string& from, const std::string& to){
  // position where suffix we are going to do a search in begins
  auto suffix_start {0};
  // first search for from in target: at first we consider target from
  // the beginning
  auto position     {target.find(from, suffix_start)};

  // when position is target.size(), there are no more occurrences of
  // from to replace with to
  while (position < target.size()){
    // we replace from with to
    target.replace(position, from.size(), to);

    // we update suffix_start to consider the suffix starting just
    // after last insertion of to ...
    suffix_start = position + to.size();
    // ... and search for from in such a suffix
    position     = target.find(from, suffix_start);
  }
}

int main(){
  std::string str {"this is a string"};

  replace(str, " ", "%20");

  std::cout << str << '\n';
  
  return 0;
}
