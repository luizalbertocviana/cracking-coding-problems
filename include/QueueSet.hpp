#ifndef queueset_hpp
#define queueset_hpp

#include <algorithm>
#include <array>
#include <queue>
#include <memory>
#include <optional>

template<typename Type, unsigned n>
class QueueSet{
  struct Element;
  using  queue_ref = std::queue<std::shared_ptr<Element>>&;

  struct Element{
    Type      content;
    queue_ref queue;

    Element(Type&& c, queue_ref r) : content{std::move(c)}, queue{r}
    {}
  };

  std::array<std::queue<std::shared_ptr<Element>>, n> queue_;
  std::queue<std::weak_ptr<Element>>                  main_queue_;

  queue_ref queue(unsigned i){
    return queue_[i];
  }
public:
  QueueSet() : queue_{}, main_queue_{}
  {}

  bool empty(){
    return std::all_of(std::cbegin(queue_), std::cend(queue_),
                       [](auto& q) {return q.empty();});
  }

  bool empty_at(unsigned i){
    return queue(i).empty();
  }
  
  void enqueue_at(unsigned i, Type&& e){
    std::shared_ptr<Element> ptr {std::make_unique<Element>(e, queue(i))};
    
    queue(i).push(ptr);

    main_queue_.push({ptr});
  }

  std::optional<Type> dequeue_from(unsigned i){
    if (queue(i).empty()){
      return {};
    }
    else{
      auto& ptr_ref {queue(i).front()};
      
      Type content {std::move(ptr_ref->content)};

      queue(i).pop();

      return content;
    }
  }

  std::optional<Type> dequeue(){
    if (empty()){
      return {};
    }
    else{
      auto lock_ptr {main_queue_.front().lock()};

      main_queue_.pop();

      while (!lock_ptr){
        lock_ptr = main_queue_.front().lock();

        main_queue_.pop();
      }
      
      lock_ptr->queue.pop();

      return std::move(lock_ptr->content);
    }
  }
};

#endif
