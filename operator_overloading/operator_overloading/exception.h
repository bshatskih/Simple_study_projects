#include <exception>
#include <string>

class IncompatibleDimException : public std::exception {
  std::string buffer;
 public:
  IncompatibleDimException(int dim1, int dim2) {
    buffer =
        "Objects with different dimensions: the dimension of the first " + std::to_string(dim1)
            + " dimension of the second " + std::to_string(dim2);
  }
  const char *what() const noexcept override {
    std::cout << std::endl;
    return buffer.c_str();
  }
};

class OutOfRangeException : public std::exception {
  std::string buffer;
 public:
  OutOfRangeException(int index, int dim) {
    buffer =
        "The size of the vector " + std::to_string(dim) + " is smaller than the input index " + std::to_string(index);
  }
  const char *what() const noexcept override {
    std::cout << std::endl;
    return buffer.c_str();
  }
};