#ifndef identity_hpp
#define identity_hpp

#include <utility>

template<typename Type>
class Identity{
  unsigned id_;

  inline static unsigned counter_ {1};

  static unsigned use_counter_(){
    return counter_++;
  }
public:
  unsigned id() const{
    return id_;
  }

  Identity() : id_{use_counter_()}
  {}

  Identity(const Identity&) : id_{use_counter_()}
  {}

  Identity& operator=(const Identity&){
    id_ = use_counter_();

    return *this;
  }

  Identity(Identity&& identifiable) : id_{std::move(identifiable.id_)}
  {
    identifiable.id_ = 0;
  }

  Identity& operator=(Identity&& identifiable){
    id_ = std::move(identifiable.id_);

    identifiable.id_ = 0;

    return *this;
  }
};

#endif
