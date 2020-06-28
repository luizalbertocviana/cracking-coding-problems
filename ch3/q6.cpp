#include <Identity.hpp>
#include <QueueSet.hpp>

#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <type_traits>

// an animal shelter, which holds only dogs and cats, operates on a
// strictly "first in, first out" basis; people must adpot either the
// "oldest" (based on arrival time) of all animals at the shelter, or
// they can select whether they would prefer a dog or a cat (and will
// receive the oldest animal of that type); they cannot select which
// specific animal they would like; create the data structures to
// maintain this system and implement operations such as enqueue,
// dequeueAny, dequeueDog and dequeueCat

class Animal{
public:
  virtual std::string talk() const {return "";}
};

class Dog final : public Animal, public Identity<Dog>{
public:
  Dog() : Animal{}, Identity{}
  {}

  Dog(const Dog& dog) : Animal{dog}, Identity{dog}
  {}

  Dog& operator=(const Dog& dog){
    Identity::operator=(dog);

    return *this;
  }

  Dog(Dog&& dog) : Animal{std::move(dog)}, Identity{std::move(dog)}
  {}

  Dog& operator=(Dog&& dog){
    Identity::operator=(std::move(dog));

    return *this;
  }

  std::string talk() const override{
    std::stringstream sstr {};

    sstr << "dog " << id() << " talking";

    return {sstr.str()};
  }
};

class Cat final : public Animal, public Identity<Cat>{
public:
  Cat() : Animal{}, Identity{}
  {}

  Cat(const Cat& cat) : Animal{cat}, Identity{cat}
  {}

  Cat& operator=(const Cat& cat){
    Identity::operator=(cat);

    return *this;
  }

  Cat(Cat&& cat) : Animal{cat}, Identity{cat}
  {}

  Cat& operator=(Cat&& cat){
    Identity::operator=(cat);

    return *this;
  }

  std::string talk() const override{
    std::stringstream sstr {};

    sstr << "cat " << id() << " talking";

    return {sstr.str()};
  }
};

class Shelter{
  QueueSet<std::unique_ptr<Animal>, 2> queue_set_;

  inline static unsigned dog_queue {0};
  inline static unsigned cat_queue {1};

  template<typename Type>
  void enqueue_(Type&& animal, unsigned queue_id){
    using pure_type = std::remove_reference_t<Type>;

    auto unique_animal {std::make_unique<pure_type>()};

    *unique_animal = std::move(animal);

    queue_set_.enqueue_at(queue_id, std::move(unique_animal));
  }

  std::unique_ptr<Animal> dequeue_type_(unsigned queue_id){
    if (auto opt {queue_set_.dequeue_from(queue_id)}){
      return std::move(*opt);
    }
    else{
      return nullptr;
    }
  }
public:
  Shelter() : queue_set_{}
  {}

  void enqueue(Dog&& dog){
    enqueue_(dog, dog_queue);
  }

  void enqueue(Cat&& cat){
    enqueue_(cat, cat_queue);
  }

  std::unique_ptr<Animal> dequeue_any(){
    if (auto opt {queue_set_.dequeue()}){
      return std::move(*opt);
    }
    else{
      return nullptr;
    }
  }

  std::unique_ptr<Animal> dequeue_dog(){
    return dequeue_type_(dog_queue);
  }

  std::unique_ptr<Animal> dequeue_cat(){
    return dequeue_type_(cat_queue);
  }
};

int main(){
  Shelter shelter {};

  auto p {10};

  std::cout << "lets put " << p << " animals into the shelter\n";

  for (auto i {0}; i < p; ++i){
    if (i % 2 == 0){
      shelter.enqueue(Cat{});
    }
    else{
      shelter.enqueue(Dog{});
    }
  }

  auto q {2};

  std::cout << "lets take " << q << " cats from the shelter:\n";

  for (auto i {0}; i < q; ++i){
    auto cat_ptr {shelter.dequeue_cat()};

    std::cout << cat_ptr->talk() << '\n';
  }

  std::cout << "lets take the other aninals from the shelter:\n";

  while (auto animal_ptr {shelter.dequeue_any()}){
    std::cout << animal_ptr->talk() << '\n';
  }

  return 0;
}
