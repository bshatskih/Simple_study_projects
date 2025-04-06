#ifndef DIVIDE_TWO_INTEGERS__SOLUTION_H_
#define DIVIDE_TWO_INTEGERS__SOLUTION_H_

template<typename T>
int sign(T value) {
  return (value > T(0)) - (value < T(0));
}

class Solution {
 public:

  static int divide(int dividend, int divisor) {
    long long result = 0;
    bool sgn;
    std::vector<std::pair<int, int>> table_of_divisor;

    if (sign(dividend) * sign(divisor) == 1) {
      sgn = true;
    } else if (sign(dividend) * sign(divisor) == -1) {
      sgn = false;
    } else {
      if (divisor == 0) {
        throw std::invalid_argument("Error: divide by zero");
      }
    }

    long long dividend_copy = dividend;
    long long divisor_copy = divisor;
    if (dividend_copy < 0) {
      dividend_copy *= (-1);
    }
    if (divisor_copy < 0) {
      divisor_copy *= (-1);
    }
    table_of_divisor.emplace_back(1, divisor_copy);
    table_of_divisor.emplace_back(1, divisor_copy);
    while (dividend_copy >= table_of_divisor.back().second) {
      dividend_copy -= table_of_divisor.back().second;
      result += table_of_divisor.back().first;
      if ((long long)(table_of_divisor.back().second + table_of_divisor[table_of_divisor.size() - 2].second) < INT_MAX) {
        table_of_divisor.emplace_back(
            table_of_divisor.back().first + table_of_divisor[table_of_divisor.size() - 2].first,
            table_of_divisor.back().second + table_of_divisor[table_of_divisor.size() - 2].second);
      } else
        break;
    }
    for (int i = table_of_divisor.size() - 2; i >= 0 && dividend_copy >= table_of_divisor.front().second; --i) {
      while (dividend_copy >= table_of_divisor[i].second) {
        dividend_copy -= table_of_divisor[i].second;
        result += table_of_divisor[i].first;
      }
    }
    if (sgn && result > INT_MAX) {
      result = INT_MAX;
    }

    return sgn ? result : -result;
  }
};

#endif //DIVIDE_TWO_INTEGERS__SOLUTION_H_
