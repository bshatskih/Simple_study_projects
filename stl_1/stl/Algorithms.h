#pragma once

#include <iostream>
#include <iterator>

using std::cout;
using std::endl;
template<typename Iter>
concept iterator = requires(Iter a, Iter b) {
  { ++a } -> std::same_as<Iter &>;
  { a++ } -> std::same_as<Iter>;

  { --a } -> std::same_as<Iter &>;
  { a-- } -> std::same_as<Iter>;

  { *a } -> std::same_as<std::iter_reference_t<Iter>>;
  { a == b } -> std::convertible_to<bool>;
  { a != b } -> std::convertible_to<bool>;
};

template<typename Pred, typename Data>
concept predicate = requires(Pred predicate, Data data) {
  { predicate(data) } -> std::convertible_to<bool>;
};

template<typename Pred, typename Data>
concept binaryPredicate = requires(Pred predicate, Data data1, Data data2) {
  { predicate(data1, data2) } -> std::convertible_to<bool>;
};

template<typename Oper, typename Data>
concept operation = requires(Oper operation, Data data) {
  { operation(data) };
};

template<iterator iterator,
    predicate<std::iter_reference_t<iterator>> predicate>
iterator findIf(iterator beg, iterator end, predicate pred) {
  for (auto iter = beg; iter != end; ++iter) {
    if (pred(*iter)) {
      return iter;
    }
  }
  return end;
}


template<iterator iterator>
iterator minElement(iterator beg, iterator end) {
  iterator min = beg;
  for (auto iter = beg++; iter != end; ++iter) {
    if (*iter < *min) {
      min = iter;
    }
  }
  return min;
}
template< iterator iterator, binaryPredicate<std::iter_reference_t<iterator>> predicate>
iterator minElement(iterator beg, iterator end, predicate pred) {
  iterator min = beg;
  for (auto iter = beg++; iter != end; ++iter) {
    if (pred(*iter, *min)) {
      min = iter;
    }
  }
  return min;
}

template<iterator iterator>
iterator maxElement(iterator beg, iterator end) {
  iterator max = beg;
  for (auto iter = beg++; iter != end; ++iter) {
    if (*iter > *max) {
      max = iter;
    }
  }
  return max;
}

template<iterator iterator>
void Sort(const iterator beg, const iterator end) {
  for (auto iter = beg; iter != end; ++iter) {
    std::iter_swap(iter, minElement(iter, end));
  }
}


template<iterator iterator,
    operation<std::iter_reference_t<iterator>> operation>
operation forEach(iterator beg, iterator end, operation op) {
  for (auto iter = beg; iter != end; ++iter) {
    op(*iter);
  }
  return op;
}


template<iterator iteratorA, iterator iteratorB,
    predicate<std::iter_reference_t<iteratorA>> predicate>
iteratorB copyIf(iteratorA sourceBeg, iteratorA sourceEnd, iteratorB destBeg,
                 predicate pred) {
  for (auto iter = sourceBeg; iter != sourceEnd; ++iter) {
    if (pred(*iter)) {
      *destBeg = *iter;
      ++destBeg;
    }
  }
  return destBeg;
}
