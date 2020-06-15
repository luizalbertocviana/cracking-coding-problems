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
  Data      data_;
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

  class Row{
    Matrix<Type>& parent_;
    size_type     row_index_;
  public:
    Row(Matrix<Type>& parent, size_type row_index)
      : parent_{parent}, row_index_{row_index}
    {}

    Type& operator[](size_type j){
      return parent_.at(row_index_, j);
    }

    Row& operator=(Type e){
      for (size_type j {0}; j < parent_.num_cols; j++){
        (*this)[j] = e;
      }

      return *this;
    }

    Row& operator=(const Row& row){
      for (size_type j {0}; j < parent_.num_cols; j++){
        (*this)[j] = row[j];
      }

      return *this;
    }

    void swap(Row&& row){
      for (size_type j {0}; j < parent_.num_cols; j++){
        std::swap((*this)[j], row[j]);
      }
    }
  };

  class Col{
    Matrix<Type>& parent_;
    size_type     col_index_;
  public:
    Col(Matrix<Type>& parent, size_type col_index)
      : parent_{parent}, col_index_{col_index}
    {}

    Type& operator[](size_type i){
      return parent_.at(i, col_index_);
    }

    Col& operator=(Type e){
      for (size_type i {0}; i < parent_.num_rows; i++){
        (*this)[i] = e;
      }

      return *this;
    }

    Col& operator=(const Col& col){
      for (size_type i {0}; i < parent_.num_rows; i++){
        (*this)[i] = col[i];
      }

      return *this;
    }

    void swap(Col&& col){
      for (size_type i {0}; i < parent_.num_rows; i++){
        std::swap((*this)[i], col[i]);
      }
    }
  };

  Row row(size_type i){
    return {*this, i};
  }

  Col col(size_type j){
    return {*this, j};
  }
};
