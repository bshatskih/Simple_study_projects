#include <iostream>
#include <fstream>


void Insertion_sort(unsigned long long *a) {
  for (int i = 1; i < 3; i++) {
    int j = i;
    while (j > 0 && a[j] < a[j - 1]) {
      std::swap(a[j], a[j - 1]);
      j--;
    }
  }
}

int main() {
  std::ifstream fin("../test");
  if (!fin.is_open()) {
    std::cout << "error";
  }
  std::string str;
  auto *arr = new unsigned long long[3];
  unsigned long long sum = 0;
  int k = 0;
  while (std::getline(fin, str) && k != 3) {
    if (!str.empty()) {
      sum += atoi(str.c_str());
    } else {
      arr[k] = sum;
      sum = 0;
      k++;
    }
  }
  Insertion_sort(arr);

  while (std::getline(fin, str)) {
    if (!str.empty()) {
      sum += atoi(str.c_str());
    } else {
      if (sum > arr[0]) {
        arr[0] = sum;
        Insertion_sort(arr);
      }
      sum = 0;
    }
  }
  unsigned long long max_sum = arr[0] + arr[1] + arr[2];
  std::cout << max_sum;
  return 0;
}
