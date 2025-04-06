#pragma once
#include <exception>
#include <string>
#include <iostream>

class IncompatibleDimException : public std::exception {
  std::string buffer;
 public:
  explicit IncompatibleDimException(float nomber) {
    buffer = "The amounts must not be negative, the number " + std::to_string(nomber) + "  is less than zero";
  }
  const char *what() const noexcept override {
    std::cout << std::endl;
    return buffer.c_str();
  }
};

class OutOfRangeException : public std::exception {
  std::string buffer;
 public:
  OutOfRangeException() {
    buffer = "Impossible operation, you can't divide by zero";
  }
  const char *what() const noexcept override {
    std::cout << std::endl;
    return buffer.c_str();
  }
};

