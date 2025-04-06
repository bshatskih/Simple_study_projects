#pragma once
#include <iostream>
#include "Exception.h"
#include "Iterator.h"


              template<typename T>
              struct ListElement {
                ListElement *next_element; //!!! Что у класса делаеют открытые поля? Используйте тогда структуру
                ListElement *prev_element;


                // default constructor
                ListElement() : data(T()), next_element(nullptr), prev_element(nullptr) {}

                explicit ListElement(const T &data_, ListElement *next = nullptr, ListElement *prev = nullptr) : data(data_), next_element(next), prev_element(prev) {}

                explicit ListElement(T &&data_, ListElement *next = nullptr, ListElement *prev = nullptr) : data(std::move(data_)), next_element(next), prev_element(prev) {}

                T &get_data() { return data; }

               private:
                T data;
              };

              //есть класс лист, есть класс лист элемент

              template<typename T>
              class List {
               public:
                using iterator = ListIterator<T>;
                using listElement = ListElement<T>;

               private:
                listElement *begin_element;
                listElement *last_element;
                int m_size = 0;

                template<typename _iter = iterator>
                void copy_list(_iter begin, _iter end) {
                  begin_element = new listElement(*begin);
                  last_element = new listElement();
                  begin_element->next_element = last_element;
                  last_element->prev_element = begin_element;
                  m_size++;
                  for (auto iter = ++begin; iter != end; ++iter) {
                    pushBack(*iter);
                  }
                }

  void reset() {
    if (begin_element == nullptr) {
      return;
    }
    iterator current = begin();
    iterator next = current;
    ++next;
    while (next.get_element() != nullptr) {
      delete current.get_element();
      current = next;
      ++next;
    }
    m_size = 0;
    delete last_element;
  }

 public:
  List() : begin_element(nullptr), last_element(nullptr) {}

  explicit List(int n) {
    begin_element = new listElement();
    last_element = new listElement();
    last_element->prev_element = begin_element;
    begin_element->next_element = last_element;
    for (int i = 0; i < n - 1; i++) {
      pushBack(T());
    }
  }

  List(int n, const T &default_data) { //!!! Почему default_data передается по значению?

    begin_element = new listElement(default_data); //!!! Тогда где move ?
    last_element = new listElement();
    last_element->prev_element = begin_element;
    begin_element->next_element = last_element;
    for (int i = 0; i < n - 1; i++) {
      pushBack(default_data);
    }
  }

  List(const List &other) : List(other.begin(), other.end()) {}

  template<_iterator Iter>
  List(Iter beg, Iter end) { copy_list(beg, end); }

  List(std::initializer_list<T> list) {
    copy_list(list.begin(), list.end());
  }

  List(List &&other) {
    begin_element = other.begin_element;
    last_element = other.last_element;
    other.begin_element = nullptr;
    other.last_element = nullptr;
  }

  ~List() { reset(); }

  List &operator=(const List &other) {
    if(this == &other)
      return *this;
    reset();
    copy_list(other.begin(), other.end());
    return *this;
  }

  List &operator=(List &&other) {
    if (&other == this) return *this;
    reset();
    begin_element = other.begin_element;
    last_element = other.last_element;
    m_size = other.m_size;
    other.begin_element = nullptr;
    other.last_element = nullptr;
    return *this;
  }

  iterator begin() const {
    if (begin_element == nullptr) {
      throw EmptyIteratorError();
    }
    return {begin_element};
  }

  iterator end() const {
    if (last_element == nullptr) {
      throw EmptyIteratorError();
    }
    return iterator(last_element);
  }

  void pushBack(const T &elem) {
    if (begin_element == nullptr) {
      begin_element = new listElement(elem);
      last_element = new listElement();
      begin_element->next_element = last_element;
      last_element->prev_element = begin_element;
      m_size++;
      return;
    }
    last_element->get_data() = elem;
    auto *el = new listElement();
    el->prev_element = last_element;
    last_element->next_element = el;
    last_element = el;
    m_size++;
  }

  void popBack() {
    if (begin_element == nullptr) {
      throw EmptyListError();
    }
    listElement *td = last_element->prev_element;
    last_element->prev_element = td->prev_element;
    td->prev_element->next_element = last_element;
    T data = td->get_data();
    m_size--;
    delete td;
  }

  void pushFront(const T &elem) {
    if (begin_element == nullptr) {
      begin_element = new listElement(elem);
      last_element = new listElement();
      begin_element->next_element = last_element;
      last_element->prev_element = begin_element;
      m_size++;
      return;
    }
    auto *el = new listElement(elem);
    begin_element->prev_element = el;
    el->next_element = begin_element;
    begin_element = el;
    m_size--;
  }

  void pushFront(T &&elem) {
    if (begin_element == nullptr) {
      begin_element = new listElement(std::move(elem));
      last_element = new listElement();
      begin_element->next_element = last_element;
      last_element->prev_element = begin_element;
      m_size++;
      return;
    }
    auto *el = new listElement(std::move(elem));
    begin_element->prev_element = el;
    el->next_element = begin_element;
    begin_element = el;
    m_size++;
  }

  void popFront() {
    if (begin_element == nullptr) {
      throw EmptyListError();
    }
    listElement *n_first = begin_element->next_element;
    n_first->prev_element = nullptr;
    T data = begin_element->get_data();
    delete begin_element;
    begin_element = n_first;
    m_size--;
  }

  iterator insert(iterator pos, const T &elem) { //!!! elem должен передавать по ссылке на константу ?
    iterator prev = pos;
    prev--;
    auto *n_element = new listElement(elem);
    pos.get_element()->prev_element = n_element;
    n_element->next_element = pos.get_element();
    if (prev.get_element() != nullptr) {
      prev.get_element()->next_element = n_element;
      n_element->prev_element = prev.get_element();
    } else {
      begin_element = n_element;
    }
    m_size++;
    return iterator(n_element);
  }

  iterator erase(iterator pos) {
    iterator to_delete = pos;
    iterator next = pos;
    ++next;
    --pos;
    if (pos.get_element() == nullptr) {
      popFront();
      return begin();
    }
    m_size--;
    pos.get_element()->next_element = next.get_element();
    next.get_element()->prev_element = pos.get_element();
    delete to_delete.get_element();
    return next;
  }

  int size() const { //!!! Метод должен быть константным
    return m_size;
  }

  void clear() {
    auto iter = begin();
    while (iter != end()) {
      erase(iter);
      iter = begin();
    }
    m_size= 0;
  }

  void resize(int num) {
    int _size = size();
    if (_size > num) {
      for (int i = 0; _size != num + i; ++i) {
        popBack();
      }
    } else {
      for (int i = 0; _size + i != num; ++i) {
        pushBack(T());
      }
    }
    m_size = num;
  }

  template<_iterator Iter>
  iterator insert(iterator pos, Iter beg, Iter end) {
    iterator itr;
    iterator first;
    iterator last = pos;
    ++last;
    bool isFirst = true;
    for (itr = beg; itr != end; ++itr) {
      auto *new_element = new listElement(*itr);
      new_element->prev_element = pos.get_element();
      pos.get_element()->next_element = new_element;
      ++pos;
      if (isFirst) {
        first = iterator(new_element);
        isFirst = false;
      }
      m_size++;
    }
    last.get_element()->prev_element = pos.get_element();
    pos.get_element()->next_element = last.get_element();
    return first;
  }

  bool empty() const{
    return m_size == 0;
  }

  friend std::ostream &operator<<(std::ostream &os, const List &list) {
    if (list.size() != 0) {
      for (const auto &i : list) {            //!!! Вы не изменяете i. Где const ?
        os << i << " ";
      }
      os << std::endl;
    } else {
      os << "List is empty!" << std::endl;
    }
    return os;
  }
};
//