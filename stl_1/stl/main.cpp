#include <iostream>
#include <string>
#include <cstdint>

#include "Algorithms.h"
#include "Container.h"

struct Goods {
  uint32_t m_id;                    // Код товара
  std::string m_name;               // Название
  std::string m_manufacturer;       // Производитель
  std::string m_warehouse_address;  // Адрес склада
  double m_weight;                  // Вес
  bool operator<(const Goods &other) { return m_name < other.m_name; }
};

struct Functor {
  auto operator()(const Goods &good) -> bool {
    return good.m_manufacturer == "IKEA";
  }
};

struct FunctorForCount {
  int m_count;
  FunctorForCount(int count) : m_count(count){
  }
  void operator()(const Goods &good) {
    if(good.m_manufacturer == "IKEA"){
      m_count++;
    }
  }
};


void printGoodsList(List<Goods> &cont) {
  forEach(cont.begin(), cont.end(), [](Goods &good) {
    std::cout << good.m_id << " " << good.m_name << " " <<
              good.m_manufacturer
              << " " << good.m_warehouse_address << " " << good.m_weight
              << std::endl;
  });
}

int main() {
  //Binary minElement Check
  List<Goods> cont_binary{{1, "Bed",      "IKEA",     "Moscow", 130},
                          {2, "Chair",    "OBI",      "SPB",    20},
                          {3, "Table",    "LERUA",    "Omsk",   140},
                          {4, "Painting", "LEONARDO", "Moscow", 5}};

  auto th = minElement(cont_binary.begin(), cont_binary.end(), [](Goods first, Goods second) {
    return first.m_weight < second.m_weight;
  });
  std::cout << th->m_name << std::endl;

  // CHECK 1
  std::cout << "CHECK 1 [create with initializer_list and print with forEach]"
            << std::endl;
  List<Goods> cont_1{{1, "Bed",      "IKEA",     "Moscow", 130},
                     {2, "Chair",    "OBI",      "SPB",    20},
                     {3, "Table",    "LERUA",    "Omsk",   140},
                     {4, "Painting", "LEONARDO", "Moscow", 5}};
  printGoodsList(cont_1);
  // CHECK 2
  std::cout
      << std::endl
      << "CHECK 2 [create empty and insert elements with insert and pushBack]"
      << std::endl;
  List<Goods> cont_2;
  Goods a{8, "Bed_2", "IKEA", "Moscow", 130};
  Goods b{9, "Chair_2", "OBI", "SPB", 20};
  Goods c{10, "Table_2", "LERUA", "Omsk", 140};
  cont_2.pushBack(a);
  cont_2.pushBack(b);
  auto iter_mid = cont_2.end();
  cont_2.insert(iter_mid, c);
  printGoodsList(cont_2);

  // CHECK 3
  std::cout << std::endl << "CHECK 3 [use insert for diapason]" << std::endl;
  auto iter_1_mid = cont_1.begin()++;
  cont_1.insert(iter_1_mid, cont_2.begin(), cont_2.end());
  printGoodsList(cont_1);

  // CHECK 4
  std::cout << std::endl << "CHECK 4 [sort list by good name]" << std::endl;
  Sort(cont_1.begin(), cont_1.end());
  printGoodsList(cont_1);

  // CHECK 5
  std::cout << std::endl
            << "CHECK 5 [find good with weight (10, 130] ]" << std::endl;
  auto foundIter = findIf(cont_1.begin(), cont_2.begin(), [](Goods &good) {
    return good.m_weight <= 130 && good.m_weight > 10;
  });
  std::cout << (*foundIter).m_id << " " << (*foundIter).m_name << " "
            << (*foundIter).m_manufacturer << " "
            << (*foundIter).m_warehouse_address << " "
            << (*foundIter).m_weight << std::endl;

  // CHECK 6
  std::cout << std::endl << "CHECK 6 [change previous with ->]" << std::endl;
  foundIter->m_warehouse_address = "Novosibirsk";
  printGoodsList(cont_1);

  // CHECK 7
  std::cout << std::endl << "CHECK 7 [copyIf manufacturer==IKEA]" <<
            std::endl;
  Functor f;
  int countOfIkea = 0;
  FunctorForCount f2{0};
  auto f2_r = forEach(cont_1.begin(),
                      cont_1.end(), f2);
  countOfIkea = f2_r.m_count;
  std::cout << "Number of IKEAS goods: " << countOfIkea << std::endl;
  List<Goods> newList(countOfIkea);
  copyIf(cont_1.begin(), cont_1.end(), newList.begin(), f);
  printGoodsList(newList);
}
