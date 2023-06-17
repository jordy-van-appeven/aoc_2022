#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <set>
#include <unordered_map>

#include "../utility.h"

enum class Choice : int { ROCK = 1, PAPER = 2, SCISSORS = 3 };

auto operator<(Choice lhs, Choice rhs) {
  if (lhs == Choice::ROCK) {
    return rhs == Choice::PAPER;
  } else if (lhs == Choice::PAPER) {
    return rhs == Choice::SCISSORS;
  } else {
    return rhs == Choice::ROCK;
  }
}

auto operator>(Choice lhs, Choice rhs) { return !(lhs < rhs || lhs == rhs); }

using EncodedChoice = const std::unordered_map<char, Choice>;

EncodedChoice kAbc{
    {'A', Choice::ROCK}, {'B', Choice::PAPER}, {'C', Choice::SCISSORS}};
EncodedChoice kXyz{
    {'X', Choice::ROCK}, {'Y', Choice::PAPER}, {'Z', Choice::SCISSORS}};

int ComputeScore(Choice lhs, Choice rhs) {
  int score = static_cast<int>(lhs);
  if (lhs > rhs) {
    return score + 6;
  } else if (lhs == rhs) {
    return score + 3;
  } else {
    return score + 0;
  }
}

int PartOne(std::ifstream &&file_handle) {

  auto total_score = 0;
  char abc, xyz;

  while (file_handle >> abc >> xyz) {
    const Choice player_abc = kAbc.at(abc);
    const Choice player_xyz = kXyz.at(xyz);
    total_score += ComputeScore(player_xyz, player_abc);
  }

  assert(total_score == 13484);
  return total_score;
}

int PartTwo(std::ifstream &&file_handle) {
  using EncodedOutcome =
      std::unordered_map<char, std::function<bool(Choice, Choice)>>;
  EncodedOutcome kXyz{{'X', operator<},
                       {'Y', [](auto lhs, auto rhs) { return lhs == rhs; }},
                       {'Z', operator> } };
  std::set<Choice> choices{Choice::ROCK, Choice::PAPER, Choice::SCISSORS};

  auto total_score = 0;
  char abc, xyz;

  while (file_handle >> abc >> xyz) {
    Choice player_abc = kAbc.at(abc);
    auto comp_func = kXyz.at(xyz);
    auto desired_outcome = [player_abc,
                            comp_func](const auto player_xyz) -> bool {
      return comp_func(player_xyz, player_abc);
    };

    Choice player_xyz =
        *std::find_if(choices.begin(), choices.end(), desired_outcome);

    total_score += ComputeScore(player_xyz, player_abc);
  }

  assert(total_score == 13433);
  return total_score;
}

int main() {
  const std::string kFileName = "input.txt";

  std::cout << "Part one answer: " << PartOne(GetOpenFileHandle(kFileName))
            << std::endl;
  std::cout << "Part two answer: " << PartTwo(GetOpenFileHandle(kFileName))
            << std::endl;

  return 0;
}

