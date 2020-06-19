#include <Matrix.hpp>

#include <algorithm>
#include <iostream>

// given a square matrix, write a function to rotate it 90 degrees
// clockwise in-place

// this function does just that
template<typename Type>
bool rotate(Matrix<Type>& m){
  // takes size_type from inside matrix
  using size_type = typename Matrix<Type>::size_type;

  // if m is a square matrix, do the rotation
  if (m.num_rows == m.num_cols){
    // first we transpose m: notice that this is equivalent to a
    // counterclockwise rotation of 90 degrees

    // as m is square, this can be done in-place
    m.transpose();

    // in order to complete a clockwise rotation of 90 degrees, we
    // take the column-wise mirror of m

    // for this, we swap pairs of columns: first and left, second and
    // second-last, and so on

    size_type left_col  {0};
    size_type right_col {m.num_cols - 1};

    while (left_col < right_col){
      m.col(left_col).swap(m.col(right_col));
      
      left_col++;
      right_col--;
    }

    return true;
  }
  // otherwise just indicate that nothing was done
  else{
    return false;
  }
}

int main(){
  Matrix<int> m {4, 4};
  using size_type = Matrix<int>::size_type;

  for (size_type i {0}; i < m.num_rows; i++){
    m.row(i) = i;
  }

  m.print();
  std::cout << '\n';

  rotate(m);
  
  m.print();

  return 0;
}
