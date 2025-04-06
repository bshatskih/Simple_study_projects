#include "Container.h"

template <typename DataType>
class List;

template <typename DataType>
class ListElement;





template <typename DataType>
class ListIterator {
  using listElement = ListElement<DataType>;

  listElement *pointer;

 public:
  ListIterator() = default;

  ListIterator(listElement *list_element) : pointer(list_element) {}

  ListIterator(const ListIterator &other) : pointer(other.pointer) {}

  ListIterator &operator++() {
    if (pointer == nullptr)
      throw EmptyIteratorError();
    pointer = pointer->next_element;
    return *this;
  }

  ListIterator operator++(int n) {
    if (pointer == nullptr)
      throw EmptyIteratorError();
    listElement *toReturn = pointer;
    pointer = pointer->next_element;
    return {toReturn};
  }

  ListIterator &operator=(const ListIterator &other) {
    if (this == &other) {                    //!!! Неверно (НЕ ИСПРАВЛЕНО) Это не проверка на самоприсваивание.
      return *this;
    }
    //!!! Где проверка на самоприсваивание (Не исправлено)

    pointer = other.pointer;
    return *this;
  }

  ListIterator operator--(int n) {
    if (pointer == nullptr)
      throw EmptyIteratorError();
    listElement *toReturn = pointer;
    pointer=pointer->prev_element;
    return {toReturn};
  }

  ListIterator &operator--() {
    if (pointer == nullptr)
      throw EmptyIteratorError();
    pointer = pointer->prev_element;
    return *this;
  }

  bool operator==(ListIterator other) const {
    return pointer == other.pointer;
  }

  bool operator!=(ListIterator other) const { return *this != other; }

  DataType &operator*() const {
    if (pointer == nullptr)
      throw EmptyIteratorError();
    return pointer->get_data();
  }

  DataType *operator->() const {
    if (pointer == nullptr)
      throw EmptyIteratorError();
    return &pointer->get_data();
  }

  listElement *get_element() const { return pointer; }
};
