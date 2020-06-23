#ifndef stacksequence_hpp
#define stacksequence_hpp

#include <array>
#include <optional>
#include <vector>

template<typename Type, unsigned n>
class StackSequence{
  std::vector<Type>  data_;
  std::array<int, n> head_;

  int& head_index(const unsigned i){
    return head_[i];
  }

  Type& head_content(const unsigned i){
    return data_[head_index(i)];
  }
public:
  StackSequence()
    : data_{}, head_{}
  {
    data_.resize(n);
    
    for (unsigned i {0}; i < n; ++i){
      head_[i] = i - n;
    }
  }

  bool empty(unsigned i){
    return head_index(i) < 0;
  }

  std::optional<Type> peek(const unsigned i){
    return empty(i) ? std::nullopt : head_content(i);
  }

  void push(const unsigned i, const Type e){
    if (head_index(i) + n >= data_.size()){
      data_.resize(2 * data_.size());
    }

    head_index(i)   += n;
    head_content(i)  = e;
  }

  std::optional<Type> pop(const unsigned i){
    if (empty(i)){
      return {};
    }
    else{
      Type copy {head_content(i)};

      head_index(i) -= n;

      return copy;
    }
  }
};

#endif
