#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <vector>

#include "../utility.h"

int AlphabeticToNumeric(const char c) {
  return c > 'a' ? c - 'a' + 1 : c - 'A' + 27;
}

int PartOne(std::ifstream &&file_handle) {
  std::vector<char> duplicated_chars;
  std::string line;
  while (file_handle >> line) {

    std::set<char> first_half(line.begin(), line.begin() + line.size() / 2);
    std::set<char> second_half(line.rbegin(), line.rbegin() + line.size() / 2);

    std::set_intersection(first_half.begin(), first_half.end(),
                          second_half.begin(), second_half.end(),
                          std::back_inserter(duplicated_chars));
  }

  auto result =
      std::accumulate(duplicated_chars.begin(), duplicated_chars.end(), 0,
                      [](auto partial_sum, const auto c) {
                        return partial_sum += AlphabeticToNumeric(c);
                      });
  assert(result == 8252);
  return result;
}

template <class InputIt, class OutputIt>
OutputIt set_intersection(InputIt first1, InputIt last1, InputIt first2,
                          InputIt last2, InputIt first3, InputIt last3,
                          OutputIt out) {
  while (first1 != last1 && first2 != last2 && first3 != last3) {
    if (*first1 < *first2 || *first1 < *first3) {
      ++first1;
    } else if (*first2 < *first1 || *first2 < *first3) {
      ++first2;
    } else if (*first3 < *first1 || *first3 < *first2) {
      ++first3;
    } else {
      // All elements are equivalent.
      *out++ = *first1;
      ++first1;
      ++first2;
      ++first3;
    }
  }
  return out;
}

int PartTwo(std::ifstream &&file_handle) {
  std::vector<char> duplicated_chars;
  std::string line_one, line_two, line_three;
  while (file_handle >> line_one >> line_two >> line_three) {
    std::set<char> set_one(line_one.begin(), line_one.end());
    std::set<char> set_two(line_two.begin(), line_two.end());
    std::set<char> set_three(line_three.begin(), line_three.end());

    set_intersection(set_one.begin(), set_one.end(), set_two.begin(),
                     set_two.end(), set_three.begin(), set_three.end(),
                     std::back_inserter(duplicated_chars));
  }

  auto result =
      std::accumulate(duplicated_chars.begin(), duplicated_chars.end(), 0,
                      [](auto partial_sum, const auto c) {
                        return partial_sum += AlphabeticToNumeric(c);
                      });
  assert(result == 2828);
  return result;
}

int main() {
  const std::string kFileName = "input.txt";
  std::cout << "Part one answer: " << PartOne(GetOpenFileHandle(kFileName))
            << std::endl;
  std::cout << "Part two answer: " << PartTwo(GetOpenFileHandle(kFileName))
            << std::endl;
  return 0;
}
