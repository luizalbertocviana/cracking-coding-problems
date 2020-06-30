#include <Graph.hpp>

#include <iostream>
#include <stack>

// given a directed graph, desigm an algorithm to find out whether
// there is a route between two nodes

using size_type = Digraph::size_type;

std::stack<size_type> route(const Digraph& D, size_type u, size_type v){
  std::stack<size_type> possible_route {};

  auto backwards_path_builder {[&possible_route, &D, v](const auto i) {
                                 if (possible_route.empty()){
                                   if (i == v){
                                     possible_route.push(i);
                                   }
                                 }
                                 else{
                                   if (D.has_edge(i, possible_route.top())){
                                     possible_route.push(i);
                                   }
                                 }
                               }};

  depth_first_search(D, u, backwards_path_builder);

  return possible_route;
}

void print_path(std::stack<size_type>& stk){
  while (!stk.empty()){
    std::cout << stk.top() << ' ';
    stk.pop();
  }

  std::cout << '\n';
}

void test_route(){
  size_type p {10};
  
  Digraph D {p};

  for (size_type i {0}; i < D.num_verts - 1; ++i){
    D.add_edge(i, i + 1);
  }

  std::cout << "D is a path from 0 to 9\n";
  std::cout << "we are going to look for a path from 0 to 9\n";

  auto path {route(D, 0, 9)};
  print_path(path);

  std::cout << "let's add an edge from 0 to 8\n";

  D.add_edge(0, 8);

  path = route(D, 0, 9);
  print_path(path);

  std::cout << "let's remove an edge from 3 to 4\n";

  D.remove_edge(3, 4);

  path = route(D, 0, 9);
  print_path(path);
}

int main(){
  test_route();

  return 0;
}
