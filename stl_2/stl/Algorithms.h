#pragma once
#include <iostream>
#include <iterator>

using std::cout;
using std::endl;
template<typename _Iter>
concept _iterator = requires(_Iter a, _Iter b) {
  { ++a } -> std::same_as<_Iter &>;
  { a++ } -> std::same_as<_Iter>;

  { --a } -> std::same_as<_Iter &>;
  { a-- } -> std::same_as<_Iter>;

  { *a } -> std::same_as<std::iter_reference_t<_Iter>>;
  { a == b } -> std::convertible_to<bool>;
  { a != b } -> std::convertible_to<bool>;
};

template<typename _Pred, typename _Data>
concept _predicate = requires(_Pred predicate, _Data data) {
  { predicate(data) } -> std::convertible_to<bool>;
};

template<typename _Pred, typename _Data>
concept _binaryPredicate = requires(_Pred predicate, _Data data1, _Data data2) {
  { predicate(data1, data2) } -> std::convertible_to<bool>;
};

template<typename _Oper, typename _Data>
concept _operation = requires(_Oper operation, _Data data) {
  { operation(data) };
};

template<_iterator iterator,
    _predicate<std::iter_reference_t<iterator>> predicate>
iterator findIf(iterator beg, iterator end, predicate pred) {
  for (auto iter = beg; iter != end; ++iter) {
    if (pred(*iter)) {
      return iter;
    }
  }
  return end;
}


template<_iterator iterator>
iterator minElement(iterator beg, iterator end) {
  iterator min = beg;
  for (auto iter = beg++; iter != end; ++iter) {
    if (*iter < *min) {
      min = iter;
    }
  }
  return min;
}
template< _iterator iterator, _binaryPredicate<std::iter_reference_t<iterator>> predicate>
iterator minElement(iterator beg, iterator end, predicate pred) {
  iterator min = beg;
  for (auto iter = beg++; iter != end; ++iter) {
    if (pred(*iter, *min)) {
      min = iter;
    }
  }
  return min;
}

template<_iterator iterator>
iterator maxElement(iterator beg, iterator end) {
  iterator max = beg;
  for (auto iter = beg++; iter != end; ++iter) {
    if (*iter > *max) {
      max = iter;
    }
  }
  return max;
}

template<_iterator iterator>
void Sort(const iterator beg, const iterator end) {
  for (auto iter = beg; iter != end; ++iter) {
    std::iter_swap(iter, minElement(iter, end));
  }
}


template<_iterator iterator, _operation<std::iter_reference_t<iterator>> operation>
operation forEach(iterator beg, iterator end, operation op) {
  for (auto iter = beg; iter != end; ++iter) {
    op(*iter);
  }
  return op;
}


template<_iterator iteratorA, _iterator iteratorB, _predicate<std::iter_reference_t<iteratorA>> predicate>
iteratorB copyIf(iteratorA sourceBeg, iteratorA sourceEnd, iteratorB destBeg, predicate pred) {
  for (auto iter = sourceBeg; iter != sourceEnd; ++iter) {
    if (pred(*iter)) {
      *destBeg = *iter;
      ++destBeg;
    }
  }
  return destBeg;
}

