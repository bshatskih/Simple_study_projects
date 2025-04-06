#pragma once
#include <exception>

class EmptyIteratorError : public std::exception {
 public:
  const char *what() const noexcept override {
    return "Error: the iterator is empty!";
  }
};

class EmptyListError : public std::exception {
 public:
  const char *what() const noexcept override {
    return "Error: trying to get access to empty list!";
  }
};
