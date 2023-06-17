#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

#include "../utility.h"

template <int N = 1> auto GetNLargestSums(std::ifstream &file_handle) {
  std::array<int, N> largest_sums{};

  auto sum = 0;
  auto min_element_itr =
      std::min_element(largest_sums.begin(), largest_sums.end());

  for (std::string line; std::getline(file_handle, line);) {
    if (line == "") {
      if (sum > *min_element_itr) {
        *min_element_itr = sum;
        min_element_itr =
            std::min_element(largest_sums.begin(), largest_sums.end());
      }
      sum = 0;
      continue;
    }
    sum += std::stoi(line);
  }
  return largest_sums;
}

int PartOne(std::ifstream &&file_handle) {
  const auto largest_sums = GetNLargestSums<1>(file_handle);
  const auto result =
      std::accumulate(largest_sums.begin(), largest_sums.end(), 0);
  assert(result == 75622);
  return result;
}

int PartTwo(std::ifstream &&file_handle) {
  const auto largest_sums = GetNLargestSums<3>(file_handle);
  const auto result =
      std::accumulate(largest_sums.begin(), largest_sums.end(), 0);
  assert(result == 213159);
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
