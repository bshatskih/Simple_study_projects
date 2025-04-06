#include "Application.h"

Application::Application() : operation(0), base1(nullptr), base2(nullptr), result(nullptr) {}

void Application::run() {
  try {
    bool key = true;
    while (key) {
      std::cout << "_____Main Menu_____" << std::endl;
      std::cout << "1 - XorArray_run\n2 - SortArray_run\n0 - Exit\n" << std::endl;
      std::cin >> operation;
      switch (operation) {
        case 1:
          XorArray_run();
          break;
        case 2:
          SortArray_run();
          break;
        case 0:
          key = false;
          break;
      }
    }
  }
  catch (std::exception& exception) {
    std::cerr << exception.what() << std::endl;
  }
}

void Application::SortArray_run() {
  base1 = new SortArray();
  base2 = new SortArray();
  result = new SortArray();
  auto *object1 = dynamic_cast<SortArray *>(base1);
  auto *res = dynamic_cast<SortArray *>(result);
  std::cout << "Enter arrays:" << std::endl;
  object1->enter();
  base2->enter();
  object1->print();
  base2->print();
  static bool check = true;
  do {
    std::cout << "\n_____SortArray menu_____" << std::endl;
    std::cout << " 1: generate new arrays\n"
                 " 2: check Add method\n"
                 " 3: check Sort method\n"
                 " 4: exit\n" << std::endl;
    std::cin >> operation;
    switch (operation) {
      case 1:
        object1->enter();
        base2->enter();
        object1->print();
        base2->print();
        break;
      case 2:
        *res = *object1;
        std::cout << "Addition of SortArray_1 and SortArray_2" << std::endl;
        res->Add(*base2);
        res->print();
        break;
      case 3:
        *res = *object1;
        std::cout << "Ascending sort of SortArray_1" << std::endl;
        res->Sort(1);
        res->print();
        std::cout << "Descending sort of SortArray_1" << std::endl;
        res->Sort(-1);
        res->print();
        break;
      case 4:
        check = false;
        break;
      default:
        std::cout << "Error! Command doesnt exist!\n";
        std::cout << std::endl;
        break;
    }
    std::cout << std::endl;
  } while (check);
  delete result;
  delete base2;
  delete base1;
}

void Application::XorArray_run() {
  base1 = new XorArray();
  base2 = new XorArray();
  result = new XorArray();
  auto *object1 = dynamic_cast<XorArray *>(base1);
  auto *res = dynamic_cast<XorArray *>(result);
  std::cout << "Enter arrays:" << std::endl;
  object1->enter();
  base2->enter();
  object1->print();
  base2->print();
  static bool check = true;
  do {
    std::cout << "\n_____XorArray menu_____" << std::endl;
    std::cout << " 1: generate new arrays\n"
                 " 2: check Add method\n"
                 " 3: check Sort method\n"
                 " 4: exit\n" << std::endl;
    std::cin >> operation;
    switch (operation) {
      case 1:
        object1->enter();
        base2->enter();
        object1->print();
        base2->print();
        break;
      case 2:
        *res = *object1;
        std::cout << "Addition of XorArray_1 and XorArray_2" << std::endl;
        res->Add(*base2);
        res->print();
        break;
      case 3:
        *res = *object1;
        std::cout << "Sort of XorArray_1" << std::endl;
        std::cout << "Enter the order of the arithmetic root" << std::endl;
        double a;
        std::cin >> a;
        res->Sort(a);
        res->print();
        break;
      case 4:
        check = false;
        break;
      default:
        std::cout << "Error! Command doesnt exist!\n";
        std::cout << std::endl;
        break;
    }
    std::cout << std::endl;
  } while (check);
  delete result;
  delete base2;
  delete base1;
}