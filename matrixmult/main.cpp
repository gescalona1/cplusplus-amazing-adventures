#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>

template <typename T> class Matrix {
public:
  Matrix(const size_t rows, const size_t cols) : rows{rows}, cols{cols} {
    assert(rows > 0);
    assert(cols > 0);
    values = std::make_unique<T[]>(rows * cols);
    std::cout << "Constructed!\n";
  }; // constructor
  Matrix(Matrix &&) = default;     // move
  Matrix(const Matrix &) = delete; // copy
  Matrix &operator=(Matrix &&) = default;
  Matrix &operator=(const Matrix &) = delete;
  ~Matrix() = default; // destructor

  void print() const {
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        std::cout << values[i * rows + j] << " ";
      }
      std::cout << "\n";
    }
  }
  Matrix multiply(const Matrix &b) const {
    assert(cols == b.rows);
    Matrix output = Matrix{rows, b.cols};

    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < b.cols; j++) {
        for (size_t k = 0; k < cols; k++) {
          T valueA = values[i * rows + k];
          T valueB = b.values[k * b.rows + j];
          std::cout << std::format("multiplying A[{},{}]={} * B[{},{}]={}\n", i,
                                   k, valueA, k, j, valueB);
          output.values[i * rows + j] += valueA * valueB;
        }
      }
    }
    return output;
  }

  void set_value(const size_t i, const size_t j, T value) {
    values[i * rows + j] = value;
  }

private:
  size_t rows;
  size_t cols;
  std::unique_ptr<int[]> values;
};

int main(int argc, char *argv[]) {
  size_t rows, cols;
  std::cout << "Enter row num and col num for 1st matrix\n";
  std::cin >> rows >> cols;
  std::cout << "Enter values of the 1st matrix:\n";
  Matrix<int> a{static_cast<size_t>(rows), static_cast<size_t>(cols)};
  int value;
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      std::cin >> value;
      a.set_value(i, j, value);
    }
  }
  std::cout << "Enter row num and col num for 2nd matrix\n";
  std::cin >> rows >> cols;
  std::cout << "Enter values of the 2nd matrix:\n";
  Matrix<int> b{static_cast<size_t>(rows), static_cast<size_t>(cols)};
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      std::cin >> value;
      b.set_value(i, j, value);
    }
  }
  std::cout << "1st Matrix:\n";
  a.print();
  std::cout << "2nd Matrix:\n";
  b.print();
  Matrix<int> c = a.multiply(b);
  c.print();
}
