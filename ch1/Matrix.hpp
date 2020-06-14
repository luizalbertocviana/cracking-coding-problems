#include <algorithm>
#include <vector>
#include <iostream>

template<typename Type>
class Matrix{
private:
  using Data = std::vector<Type>;
public:
  using size_type = typename Data::size_type;
private:
  Data data_;
  size_type rows_;
  size_type cols_;

  size_type index(size_type i, size_type j){
    return cols_ * i + j;
  }
public:
  const size_type& num_rows;
  const size_type& num_cols;
  
  Matrix(size_type rows, size_type cols)
    : data_{}, rows_{rows}, cols_{cols}, num_rows{rows_}, num_cols{cols_}
  {
    data_.reserve(rows_ * cols_);
  }

  Type& at(size_type i, size_type j){
    return data_[index(i, j)];
  }

  void print(std::ostream& out = std::cout){
    for (size_type i {0}; i < num_rows; i++){
      for (size_type j {0}; j < num_cols; j++){
        out << at(i, j) << ' ';
      }
      out << '\n';
    }
  }

  void transpose(){
    if (num_rows == num_cols){
      for (size_type i {0}; i < num_rows; i++){
        for (size_type j {i + 1}; j < num_cols; j++){
          std::swap(at(i, j), at(j, i));
        }
      }
    }
    else{
      Matrix<Type> t {num_cols, num_rows};

      for (size_type i {0}; i < num_rows; i++){
        for (size_type j {0}; j < num_cols; j++){
          t.at(j, i) = at(i, j);
        }
      }

      std::swap(data_, t.data_);
    }
    
    std::swap(rows_, cols_);
  }
};
