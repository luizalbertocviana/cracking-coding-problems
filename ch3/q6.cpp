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

// a virtual class to represent an animal
class Animal{
public:
  // virtual methos require some implementation; notice that derived
  // classes can call this
  virtual std::string talk() const {return "";}
};

// one final subclass of Animal and Identity<Dog>

// notice that Dog is passed as template argument to Identity; this
// creates an id counter exclusive to Dog objects
class Dog final : public Animal, public Identity<Dog>{
public:
  // default constructor
  Dog() : Animal{}, Identity{}
  {}

  // copy constructor defined in terms of subclasses copy constructors
  Dog(const Dog& dog) : Animal{dog}, Identity{dog}
  {}

  // copy assignment defined in terms of subclasses copy assignments
  Dog& operator=(const Dog& dog){
    // Animal does not have a relevant copy assignment
    Identity::operator=(dog);

    return *this;
  }

  // move constructor defined in terms of subclasses move constructors
  Dog(Dog&& dog) : Animal{std::move(dog)}, Identity{std::move(dog)}
  {}

  // move assignment defined in terms of subclasses move assignments
  Dog& operator=(Dog&& dog){
    // Animal does not have a relevant move assignment
    Identity::operator=(std::move(dog));

    return *this;
  }

  // overrides virtual method talk of Animal
  std::string talk() const override{
    std::stringstream sstr {};

    sstr << "dog " << id() << " talking";

    return {sstr.str()};
  }
};

// this is analogous to Dog class
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

  Cat(Cat&& cat) : Animal{std::move(cat)}, Identity{std::move(cat)}
  {}

  Cat& operator=(Cat&& cat){
    Identity::operator=(std::move(cat));

    return *this;
  }

  std::string talk() const override{
    std::stringstream sstr {};

    sstr << "cat " << id() << " talking";

    return {sstr.str()};
  }
};

// represents the shelter described in the exercise
class Shelter{
  // queue set of two queues, one for dogs and other for cats
  QueueSet<std::unique_ptr<Animal>, 2> queue_set_;

  // we use this to identify each queue by its index
  inline static unsigned dog_queue {0};
  inline static unsigned cat_queue {1};

  // template private method to put an animal into queue determined by
  // queue_id
  template<typename Type>
  void enqueue_(Type&& animal, unsigned queue_id){
    // pure_type represents Type with no reference mark (&)
    using pure_type = std::remove_reference_t<Type>;

    // moves animal (held by unique_ptr) into queue indicated by queue_id
    queue_set_.enqueue_at(queue_id, std::make_unique<pure_type>(std::move(animal)));
  }

  // dequeues an animal from queue indicated by queue_id
  std::unique_ptr<Animal> dequeue_from_(unsigned queue_id){
    // we get an optional from queue set that holds the returned
    // animal, if any
    if (auto opt {queue_set_.dequeue_from(queue_id)}){
      // in case opt does hold a unique_ptr to an Animal, we move it
      // to the caller
      return std::move(*opt);
    }
    else{
      // otherwise, we return nullptr to indicate no animal was
      // returned by queue set
      return nullptr;
    }
  }
public:
  // default constructor
  Shelter() : queue_set_{}
  {}

  // moves dog into dog queue
  void enqueue(Dog&& dog){
    enqueue_(std::move(dog), dog_queue);
  }

  // moves cat into cat queue
  void enqueue(Cat&& cat){
    enqueue_(std::move(cat), cat_queue);
  }

  // takes olddest animal in shelter, if any
  std::unique_ptr<Animal> dequeue_any(){
    if (auto opt {queue_set_.dequeue()}){
      return std::move(*opt);
    }
    else{
      return nullptr;
    }
  }

  // takes oldest dog, if any
  std::unique_ptr<Animal> dequeue_dog(){
    return dequeue_from_(dog_queue);
  }

  // takes oldest cat, if any
  std::unique_ptr<Animal> dequeue_cat(){
    return dequeue_from_(cat_queue);
  }
};

void test_shelter(){
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
}

int main(){
  test_shelter();

  return 0;
}
