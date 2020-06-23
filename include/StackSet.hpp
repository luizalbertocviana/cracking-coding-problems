#ifndef stackset_hpp
#define stackset_hpp

#include <optional>
#include <stack>
#include <vector>

template<typename Type, unsigned stack_capacity>
class StackSet{
  std::vector<std::stack<Type>> stk_set_;
  unsigned                      current_stk_index_;

  std::stack<Type>& current_stack(){
    return stk_set_[current_stk_index_];
  }
public:
  StackSet() : stk_set_{1}, current_stk_index_{0}
  {}

  bool empty(){
    return current_stack().empty();
  }

  void push(const Type& e){
    if (current_stack().size() >= stack_capacity){
      if (current_stk_index_ == stk_set_.size() - 1){
        stk_set_.push_back({});
      }

      ++current_stk_index_;
    }

    current_stack().push(e);
  }

  std::optional<Type> pop(){
    if (empty()){
      return {};
    }
    else{
      Type copy {current_stack().top()};

      current_stack().pop();

      while (current_stack().empty() && current_stk_index_ > 0){
        --current_stk_index_;
      }

      return copy;
    }
  }

  std::optional<Type> pop_at(unsigned i){
    auto& stk {stk_set_[i]};
    
    if (stk.empty()){
      return {};
    }
    else{
      Type copy {stk.top()};

      stk.pop();

      return copy;
    }
  }

  std::optional<Type> peek(){
    if (empty()){
      return {};
    }
    else{
      return current_stack().top();
    }
  }
};

#endif
