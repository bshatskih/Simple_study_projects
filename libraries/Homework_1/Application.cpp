#include "Application.h"

Application::Application() : operation(0) {}

void Application::run() {
  try {
    bool key = true;
    while (key) {
      std::cout << "____Main Menu____" << std::endl;
      std::cout << "1 - LongLong\n2 - Money\n0 - Exit\n" << std::endl;
      std::cin >> operation;
      switch (operation) {
        case 0:
          key = false;
          break;
        case 1:
          LongLong_run();
          break;
        case 2:
          Money_run();
          break;
      }
    }
  }
  catch (std::exception& exception) {
    std::cerr << exception.what() << std::endl;
  }
}

void Application::Money_run() {
  Money money1,money2;
  std::cout << "Enter the first amount in format: rubles , kopecks" << std::endl;
  std::cin >> money1;
  std::cout << "Enter the first amount in format: rubles , kopecks; (the first amount is less than the second)" << std::endl;
  std::cin >> money2;
  std::cout << "First amount: " << money1;
  std::cout << "Second amount: " << money2;
  std::cout << std::endl;
  static bool check = true;
  do {
    int key;
    std::cout << "____Money Menu____" << std::endl;
    std::cout << " 1: generate new amount\n"
                 " 2: check 'get' methods\n"
                 " 3: check 'set' methods\n"
                 " 4: check sum and difference of money\n"
                 " 5: check division and multiplication of money\n"
                 " 6: check bool operators\n"
                 " 7: check Money's object count\n"
                 " 8: check operations with numbers\n"
                 " 9: check Conversion metod\n"
                 "10: exit" << std::endl;
    std::cin >> key;
    switch (key) {
      case 1:
        Money_run();
        break;
      case 2:
        std::cout << "First amount: " << money1.get_rubles() << "," << (int)money1.get_kopeks() << "\nSecond amount: " << money2.get_rubles() << "," << (int)money2.get_kopeks() << std::endl;
        std::cout << std::endl;
        break;
      case 3: {
        std::cout << "Set rubles and kopeks of amount moment #1:" << std::endl;
        int kopeks;
        char c;
        unsigned long rubles;
        std::cin >> rubles >> c >> kopeks;
        money1.set_rubles(rubles);
        money1.set_kopeks(kopeks);
        std::cout <<  "First amount: " << money1.get_rubles() << "," << (int)money1.get_kopeks()  << std::endl;
        std::cout << std::endl;
        break;
      }
      case 4:
        std::cout << "Sum of money is " << money1 + money2;
        std::cout << "Difference of time is " << money2 - money1 << std::endl;
        std::cout << std::endl;
        break;
      case 5:
        std::cout << "Division of money is " << money1 * money2;
        std::cout << "Multiplication of time is " << money2 / money1 << std::endl;
        std::cout << std::endl;
        break;
      case 6:
        if (money1 > money2)
          std::cout << "First amount is greater than second amount" << std::endl;
        if (money1 < money2)
          std::cout << "First amount is lesser than second amount" << std::endl;
        if (money1 == money2)
          std::cout << "First amount equals second amount" << std::endl;
        if (money1 >= money2)
          std::cout << "First amount is not less than second amount" << std::endl;
        if (money1 <= money2)
          std::cout << "First amount is not more than second amount" << std::endl;
        std::cout << std::endl;
        break;
      case 7:
        std::cout << "Total object count is " << Money::get_ExistMoney() << std::endl;
        std::cout << std::endl;
        break;
      case 8:
        double number;
        std::cout << "Enter an arbitrary positive real number:" << std::endl;
        std::cin >> number;
        std::cout << "Multiplying first amount by a number:  " << money1*number << std::endl;
        std::cout << "Dividing the first sum by a number: " << money1/number << std::endl;
        std::cout << std::endl;
        break;
      case 9:
        unsigned long kopek;
        std::cout << "Enter the amount in kopecks to convert:" << std::endl;
        std::cin >> kopek;
        std::cout << "The amount in the normal representation: " << Money::kopeksToMoney(kopek) << std::endl;
        std::cout << std::endl;
        break;
      case 10:
        check = false;
        break;
      default:
        std::cout << "Error! Command doesnt exist!\n";
        std::cout << std::endl;
        break;
    }
  } while (check);
}




void Application::LongLong_run() {
  LongLong rubles;
  std::cout << "Enter rubles:" << std::endl;
  std::cin >> rubles;
  std::cout << rubles;
  static bool check = true;
  do {
    int key;
    std::cout << "____LongLong Menu____" << std::endl;
    std::cout << " 1: generate new rubles\n"
                 " 2: check toLongLong() method\n"
                 " 3: check Bill's object count\n"
                 " 4: exit" << std::endl;
    std::cin >> key;
    switch(key) {
      case 1:
        LongLong_run();
        break;
      case 2:
        std::cout << rubles.toLongLong() << std::endl;
        break;
      case 3:
        std::cout << "Total object count is " << LongLong::get_ExistLongLong() << std::endl;
        break;
      case 4:
        check = false;
        break;
      default:
        std::cout << "Error! Command doesnt exist!\n";
        break;
    }
  } while (check);
}
