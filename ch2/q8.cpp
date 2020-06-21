#include <iostream>
#include <list>

template<typename FunctionAB, typename FunctionBC>
auto compose(const FunctionAB& f, const FunctionBC& g){
  return [&f, &g](auto x){
           return g(f(x));
         };
}

/*

cycle detection Floyd's turtle and hare algorithm:
given an initial value val and a function f, declare variables turtle and hare:
- both turtle and hare are set to val;
- phase 1:
  - turtle is updated with f(turtle);
  - hare is updated with f(f(hare));
  - they are updated this way until either hare satisfies a finishing
    condition or turtle = hare;
  - if hare satisfies a finishing condition, no cycle was found;
  - otherwise, we begin phase 2 in order to find the cycle start
- phase 2:
  - we set turtle to val, and let hare untouched;
  - turtle is updated with f(turtle);
  - hare is updated with f(hare);
  - when they meet, both turtle and hare are at the start of the
    cycle, so return turtle (or hare, whatever).

very simple, but why the hell this works?

Let's consider a scenario where a cycle can be reached from val; x is
the distance from val to the cycle start; y is the distance from the
cycle start to the (phase 1) meeting point; z is the distance from the
meeting point to the cycle start; L is the cycle length; observe the
diagram below

              y
           -----------
          /           \
  x      /             \ * meeting point
--------|     L         |
         \             /
          \           /
           -----------
              z

L = y + z

In phase 1, turtle moves one step at a time; hare moves two steps at a
time

d1: distance traveled by turtle until it meets hare
d2: distance traveled by hare until it meets turtle

turtle is slower than hare:
d1 = x + y
d2 = x + k*L - z (hare may loop before it meets turtle)

notice we assume that hare is in its k-th travel through the cycle
when it meets turtle; we used "- z" in order to have k >= 1

hare is twice as fast as turtle:
d2 = 2*d1
d2 = 2*(x + y)

equation on d2 and 2*d1:
2*x + 2*y       = x + k*L - z
2*x + y + y + z = x + k*L
2*x + y + L     = x + k*L
2*x + y         = x + (k - 1)*L
x + y           = (k - 1)*L

let's put x in terms of L and z:
x = x + y - y
  = x + y - (L - z)
  = (k - 1)*L - L + z
  = (k - 2)*L + z

in phase 2, turtle is put at the beginning and both hare and turtle
move a step at a time

After x steps, turtle is at the cycle start; after x = p*L + z steps,
hare loops p times through the cycle, staying at the (phase 1) meeting
point, and then moves z steps, being at the cycle start

*/

// implements Floyd's hare and turtle algorithm
template<typename Function, typename Type>
Type find_cycle(const Type& start, const Type& end, const Function& f){
  // if a finishing condition is not met at beginning, we perform the
  // search
  if (start != end){
    // put turtle and hare at the start
    Type turtle {start};
    Type hare   {start};

    // steps that will be performed during the search
    auto slow_step {f};
    auto fast_step {compose(f, f)};

    // phase 1: unless hare meets a finishing condition, setps both
    // turtle and hare
    while (slow_step(hare) != end && fast_step(hare) != end){
      // turtle is slower than hare
      turtle = slow_step(turtle);
      hare   = fast_step(hare);

      // phase 2: turtle meets hare
      if (turtle == hare){
        // puts turtle at the start
        turtle = start;

        // both do one step at a time; we know they will meet each
        // other
        while (turtle != hare){
          slow_step(turtle);
          slow_step(hare);
        }

        // when they meet, return one of them, in this case turtle
        return turtle;
      }
    }

    // if hare satisfies a finishing condition, returns end to
    // indicate that no cycle was found
    return end;
  }
  // other wise we return end
  else{
    return end;
  }
}

int main(){
  std::list<int> list {};

  auto cycle_it {find_cycle(std::cbegin(list), std::cend(list),
                            [](auto it) {return ++it;})};

  std::cout << "I dont know how to test this\n";
}
