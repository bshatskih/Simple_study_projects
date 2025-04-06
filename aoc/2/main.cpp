  #include <iostream>
  #include <fstream>

  int main() {
    std::ifstream fin("../test");
    std::string str;
    int score = 0;
  auto *arr = new std::pair<std::string, short>[9];
  /*
  A, X - stone    1
  B, Y - paper    2
  C, Z - scissors 3
   X - lose
   Y - draw
   Z - win
   */
  {
    arr[0].first = "A X";
    arr[0].second = 0 + 3;
    arr[1].first = "A Y";
    arr[1].second = 3 + 1;
    arr[2].first = "A Z";
    arr[2].second = 6 + 2;

    arr[3].first = "B X";
    arr[3].second = 0 + 1;
    arr[4].first = "B Y";
    arr[4].second = 3 + 2;
    arr[5].first = "B Z";
    arr[5].second = 6 + 3;

    arr[6].first = "C X";
    arr[6].second = 0 + 2;
    arr[7].first = "C Y";
    arr[7].second = 3 + 3;
    arr[8].first = "C Z";
    arr[8].second = 6 + 1;
  }
  if (!fin.is_open()) {
    std::cout << "error";
  }
  bool flag;
  while (std::getline(fin, str)) {
    flag = true;
    for (int i = 0; i < 9 && flag; i++) {
      if (str == arr[i].first) {
        score += arr[i].second;
        flag = false;
      }
    }
  }
  std::cout << score;
  return 0;
}

