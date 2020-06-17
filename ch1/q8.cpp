#include <iostream>
#include <vector>

#include <Matrix.hpp>

// write a function that, given a matrix, if position [i, j] is zero,
// then row i and column j are entirely set to zero

// this saves us from some typing
template<typename Type>
using size_type = typename Matrix<Type>::size_type;

// if position [i, j] of m is zero, sets row i and column j to zero;
// returns true iff m was modified
template<typename Type>
bool zerofy_position(Matrix<Type>& m, size_type<Type> i, size_type<Type> j){
  if (m.at(i, j) == 0){
    m.row(i) = 0;
    m.col(j) = 0;

    return true;
  }
  else{
    return false;
  }
}

// applies zerofy_position to all positions of m
template<typename Type>
void zerofy_matrix(Matrix<Type>& m){
  // we use this for skip columns zeroed by ourselves
  std::vector<bool> candidate_cols (true, m.num_cols);

  // for each row ...
  for (size_type<Type> i {0}; i < m.num_rows; i++){
    bool zeroed_row {false};

    // and for each column ...
    for (size_type<Type> j {0}; !zeroed_row && j < m.num_cols; j++){
      // if column was not zeroed yet ...
      if (candidate_cols[j]){
        // we verify whether it should be zeroed
        if (zerofy_position(m, i, j)){
          // if we did zero column j, we do not need to look at it
          // anymore
          candidate_cols[j] = false;

          // also, there is no need to keep looking row i, since it
          // just had been zeroed
          zeroed_row = true;
        }
      }
    }
  }
}

int main(){
  Matrix<int> m {6, 6};
  m = 1;

  m.at(1, 1) = 0;
  m.at(3, 3) = 0;
  m.at(0, 2) = 0;

  m.print();

  std::cout << '\n';

  zerofy_matrix(m);

  m.print();

  return 0;
}
