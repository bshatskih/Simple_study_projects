#include "../Algorithms.h"
#include "../Container.h"
#include "vector"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"

using std::vector;

template <typename T>
vector<T> listToVector(List<T> &a) {
  vector<T> r;
  for (auto elem : a) {
    r.push_back(elem);
  }
  return r;
}

TEST_SUITE("List") {
TEST_CASE("Default Constructor") {
List<int> a;
CHECK(a.empty());
}
TEST_CASE("Constructor(int n)") {
List<int> a(4);
CHECK(listToVector<int>(a) == vector<int>{0, 0, 0, 0});
}
TEST_CASE("Constructor(int n, T default)") {
List<int> a(4, 5);
CHECK(listToVector<int>(a) == vector<int>{5, 5, 5, 5});
}
TEST_CASE("Constructor(std::initializer_list)") {
List<int> a{1, 2, 3, 4};
CHECK(listToVector<int>(a) == vector<int>{1, 2, 3, 4});
}

TEST_CASE("Constructor(iterator beg, iterator beg)") {
List<int> a{1, 2, 3, 4};
List<int>::iterator beg = ++a.begin();
List<int>::iterator end = --a.end();
List<int> b(beg, end);
CHECK(listToVector<int>(b) == vector<int>{2, 3});
}
TEST_CASE("Copy constructor") {
List<int> a(4, 5);
List<int> b(a);
CHECK(listToVector<int>(b) == vector<int>{5, 5, 5, 5});
}
TEST_CASE("Move constructor") {
List<int> a(4, 5);
List<int> b(std::move(a));
CHECK(listToVector<int>(b) == vector<int>{5, 5, 5, 5});
}
TEST_CASE("Copy operator=") {
List<int> a(4, 5);
List<int> b(3);
b = a;
CHECK(listToVector<int>(b) == vector<int>{5, 5, 5, 5});
}
TEST_CASE("Move operator=") {
List<int> a(4, 5);
List<int> b(3);
b = std::move(a);
CHECK(listToVector<int>(b) == vector<int>{5, 5, 5, 5});
}
TEST_CASE("begin()") {
List<int> a{1, 2, 3, 4};
List<int>::iterator beg = a.begin();
CHECK(*beg == 1);
}
TEST_CASE("end()") {
List<int> a{1, 2, 3, 4};
List<int>::iterator end = --a.end();
CHECK(*end == 4);
}
TEST_CASE("pushBack(T elem)") {
List<int> a{1, 2, 3, 4};
a.pushBack(5);
CHECK(listToVector<int>(a) == vector<int>{1, 2, 3, 4, 5});
}
TEST_CASE("popBack()") {
List<int> a{1, 2, 3, 4};
a.popBack();
CHECK(listToVector<int>(a) == vector<int>{1, 2, 3});
}
TEST_CASE("pushFront(T elem)") {
List<int> a{1, 2, 3, 4};
a.pushFront(5);
CHECK(listToVector<int>(a) == vector<int>{5, 1, 2, 3, 4});
}
TEST_CASE("popFront()") {
List<int> a{1, 2, 3, 4};
a.popFront();
CHECK(listToVector<int>(a) == vector<int>{2, 3, 4});
}
TEST_CASE("insert(pos, elem)") {
List<int> a{1, 2, 3, 4};
List<int>::iterator iter = ++a.begin();
a.insert(iter, 5);
CHECK(listToVector<int>(a) == vector<int>{1, 5, 2, 3, 4});
}
TEST_CASE("insert(pos, beg, end)") {
List<int> a{1, 2, 3, 4};
List<int> b{5, 6};
List<int>::iterator iter = ++a.begin();
a.insert(iter, b.begin(), b.end());
CHECK(listToVector<int>(a) == vector<int>{1, 2, 5, 6, 3, 4});
}
TEST_CASE("erase(pos)") {
List<int> a{1, 2, 3, 4};
List<int>::iterator iter = ++a.begin();
a.erase(iter);
CHECK(listToVector<int>(a) == vector<int>{1, 3, 4});
}
TEST_CASE("resize(size)") {
List<int> a{1, 2, 3, 4};
a.resize(6);
CHECK(listToVector<int>(a) == vector<int>{1, 2, 3, 4, 0, 0});
a.resize(2);
CHECK(listToVector<int>(a) == vector<int>{1, 2});
}
TEST_CASE("empty()") {
List<int> a{1, 2, 3, 4};
List<int> b;
CHECK(a.empty() == false);
CHECK(b.empty() == true);
}
TEST_CASE("size()") {
List<int> a{1, 2, 3, 4};
CHECK(a.size() == 4);
}
TEST_CASE("clear()") {
List<int> a{1, 2, 3, 4};
a.clear();
CHECK(a.empty() == true);
}
}
