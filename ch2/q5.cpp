#include <algorithm>
#include <iostream>
#include <list>
#include <optional>
#include <string>

#include <args.hpp>

// you have two numbers represented by a linked list, where each node
// contains a single digit; the digits are stored from least
// significant to most significant; produce a linked list containing
// the digits of the sum of these two numbers, from least significant
// to most significant

// repeat the question considering that both numbers and result are
// represented from most significant to least significant digits

// offset char for performing arithmetc operations
constexpr const char base_digit {'0'};

// returns distance from offset char
int distance(const char c){
  return c - base_digit;
}

// determines whether char is a digit
bool is_digit(const char c){
  auto dc {distance(c)};

  return dc >= 0 && dc <= 9;
}

// determines whether string represents a number
bool is_number(const std::string& str){
  return std::all_of(std::cbegin(str), std::cend(str), is_digit);
}

// converts a string into a list of chars
std::list<char> string_to_list(const std::string& str){
  return {std::cbegin(str), std::cend(str)};
}

// performs sum of digit chars c1 and c2, considering a carry (either
// '0' or '1')
std::pair<char, char> sum(const char c1, const char c2, const char carry){
  // distances from offset char
  auto dc1             {distance(c1)};
  auto dc2             {distance(c2)};
  // sum of distances
  auto int_sum         {dc1 + dc2};
  // sum of distances considering carry
  auto carried_int_sum {carry == '1' ? int_sum + 1 : int_sum};
    
  // if sum with carry is at most nine, carry '0'
  if (carried_int_sum <= 9){
    return {'0', base_digit + carried_int_sum};
  }
  // otherwise, carry '1' and subtract ten to obtain result digit
  else{
    return {'1', base_digit + carried_int_sum - 10};
  }
}

// performs sum of ranges, considering they arrange their digits from
// least significant to most significant
template<typename Iterator>
std::list<char> sum(Iterator it1, Iterator end1,
                    Iterator it2, Iterator end2){
  // result list to be built
  std::list<char> result         {};
  // carry of last operation; '0' for least significant digits
  char            previous_carry {'0'};

  // performs sum of digits, updating result and previous_carry
  auto summing {[&result, &previous_carry](const char c1, const char c2){
                  // sums c1 and c2, getting digit of same
                  // significance and carry
                  auto[carry, result_digit] {sum(c1, c2, previous_carry)};

                  // stores digit in result
                  result.push_back(result_digit);
                  // updates carry;
                  previous_carry = carry;
                }};
  
  // while the two ranges have digits of same significance, sum them
  // and go to next pair of digits
  while (it1 != end1 && it2 != end2){
    summing(*it1, *it2);

    ++it1;
    ++it2;
  }

  // notice that when we exit the while loop, it could be the case
  // that one of the ranges has some remaining digits to be
  // considered; in that case; we match its remaining digits with '0'
  
  // decides which range mght have remaining digits
  auto& unfinished_it  {it1 != end1 ? it1  : it2};
  auto& unfinished_end {it1 != end1 ? end1 : end2};

  // while the unfinished range has digits to be considered
  while (unfinished_it != unfinished_end){
    summing(*unfinished_it, '0');

    ++unfinished_it;
  }

  // at the end, we verify whether carry will be put as the most
  // significant digit of result ...
  if (previous_carry == '1'){
    result.push_back('1');
  }

  // and we return result
  return result;
}

// prints a range
template<typename Iterator>
void print(Iterator begin, Iterator end){
  std::for_each(begin, end, [](auto e) {std::cout << e << ' ';});
  std::cout << '\n';
}

int main(int argc, char** argv){
  auto args {get_args(argc, argv)};

  if (args.size() == 3){
    std::string str1 {args[1]};
    std::string str2 {args[2]};

    if (is_number(str1) && is_number(str2)){
      auto normal_result  {sum(std::crbegin(str1), std::crend(str1),
                               std::crbegin(str2), std::crend(str2))};
      auto reverse_result {sum(std::cbegin(str1), std::cend(str1),
                               std::cbegin(str2), std::cend(str2))};
      
      std::cout << "sum considering numbers in normal order of digits:\n";
      print(std::crbegin(normal_result), std::crend(normal_result));
      std::cout << "sum considering numbers in reverse order of digits:\n";
      print(std::crbegin(reverse_result), std::crend(reverse_result));
    }
    else{
      std::cout << "arguments must be numbers\n";
    }
  }
  
  return 0;
}
