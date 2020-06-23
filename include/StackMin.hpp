#ifndef stackmin_hpp
#define stackmin_hpp

#include <functional>
#include <optional>
#include <stack>

template<typename Type, typename Comparator = std::less_equal<Type>>
class StackMin{
  std::stack<Type> stk_;
  std::stack<Type> min_;

  const Comparator cmp_;

  std::optional<Type> peek_(const std::stack<Type>& stk){
    if (empty()){
      return {};
    }
    else{
      return stk.top();
    }
  }
public:
  StackMin() : stk_{}, min_{}, cmp_{}
  {}
  
  bool empty(){
    return stk_.empty();
  }

  std::optional<Type> peek(){
    return peek_(stk_);
  }

  void push(const Type& e){
    if (min_.empty()){
      stk_.push(e);
      min_.push(e);
    }
    else{
      stk_.push(e);

      if (cmp_(e, min_.top())){
        min_.push(e);
      }
    }
  }

  std::optional<Type> pop(){
    if (empty()){
      return {};
    }
    else{
      Type removed {stk_.top()};
      stk_.pop();

      if (removed == min_.top()){
        min_.pop();
      }

      return removed;
    }
  }

  std::optional<Type> min(){
    return peek_(min_);
  }
};

template<typename Type>
using StackMax = StackMin<Type, std::greater_equal<Type>>;

#endif
