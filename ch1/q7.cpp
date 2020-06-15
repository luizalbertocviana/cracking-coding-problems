#include <algorithm>
#include <iostream>

#include "Matrix.hpp"

template<typename Type>
bool rotate(Matrix<Type>& m){
  using size_type = typename Matrix<Type>::size_type;

  if (m.num_rows == m.num_cols){
    m.transpose();

    size_type left_col  {0};
    size_type right_col {m.num_cols - 1};

    while (left_col < right_col){
      m.col(left_col).swap(m.col(right_col));
      
      left_col++;
      right_col--;
    }

    return true;
  }
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
