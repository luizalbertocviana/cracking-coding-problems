#ifndef range_hpp
#define range_hpp

template<typename Type>
class Index{
  Type element_;
public:
  Index(const Type& e) : element_{e}
  {}
  Type& operator*(){
    return element_;
  }
  Type& operator++(){
    return ++element_;
  }
  Type& operator--(){
    return --element_;
  }
  Type& operator++(int){
    return element_++;
  }
  Type& operator--(int){
    return element_--;
  }
  bool operator!=(const Index& idx){
    return element_ != idx.element_;
  }
  bool operator==(const Index& idx){
    return element_ == idx.element_;
  }
  bool operator<=(const Index& idx){
    return element_ <= idx.element_;
  }
  bool operator>=(const Index& idx){
    return element_ >= idx.element_;
  }
  bool operator<(const Index& idx){
    return element_ < idx.element_;
  }
  bool operator>(const Index& idx){
    return element_ > idx.element_;
  }
};

template<typename Type>
Index<Type> index(const Type& e){
  return {e};
}

template<typename Type>
class ReverseIndex : public Index<Type>{
  using Idx = Index<Type>;
public:
  ReverseIndex(const Type& e) : Idx{e}
  {}
  Type& operator++(){
    return Idx::operator--();
  }
  Type& operator--(){
    return Idx::operator++();
  }
  Type& operator++(int){
    return Idx::operator--(0);
  }
  Type& operator--(int){
    return Idx::operator++(0);
  }
};

template<typename Type>
ReverseIndex<Type> reverse_index(const Type& e){
  return {e};
}

template<typename Type>
class Range{
  Type begin_;
  Type end_;
public:
  Range(const Type& begin, const Type& end) : begin_{begin}, end_{end}
  {}

  Index<Type> begin(){
    return index(begin_);
  }
  Index<Type> end(){
    return index(end_);
  }

  ReverseIndex<Type> rbegin(){
    return reverse_index(end_ - 1);
  }
  ReverseIndex<Type> rend(){
    return reverse_index(begin_ - 1);
  }
};

template<typename Type>
class ReverseRange{
  Type begin_;
  Type end_;
public:
  ReverseRange(const Type& begin, const Type& end) : begin_{begin}, end_{end}
  {}

  ReverseIndex<Type> begin(){
    return reverse_index(end_ - 1);
  }
  ReverseIndex<Type> end(){
    return reverse_index(begin_ - 1);
  }

  Index<Type> rbegin(){
    return index(begin_);
  }
  Index<Type> rend(){
    return index(end_);
  }
};

template<typename Type>
Range<Type> range(const Type& begin, const Type& end){
  return {begin, end};
}

template<typename Type>
ReverseRange<Type> reverse_range(const Type& begin, const Type& end){
  return {begin, end};
}

#endif
