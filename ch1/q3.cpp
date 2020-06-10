#include <iostream>

// replace all occurrences of " " with "%20"

// replaces all occurrences of from in target with to
void replace(std::string& target, const std::string& from, const std::string& to){
  auto suffix_start{0};
  auto position{target.find(from, suffix_start)};

  while (position < target.size()){
    target.replace(position, from.size(), to);

    suffix_start = position + to.size();
    position     = target.find(from, suffix_start);
  }
}

int main(){
  std::string str{"this is a string"};

  replace(str, " ", "%20");

  std::cout << str << '\n';
  
  return 0;
}
