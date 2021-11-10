#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string lectures;
  std::cin >> lectures;

  const unsigned int ASCII_LENGTH = 127;
  const int FREE_POS = -69;
  const int TAKEN_POS = -420;

  std::vector<int> indexOfLectures(ASCII_LENGTH, FREE_POS);

  int asciiNumberForChar = 0;
  for (int i = 0; i < lectures.length(); i++) {
    asciiNumberForChar = lectures[i];
    // Check if this character is unique and it hasn't been seen before give the
    // value of the ascii number of this character with the position of the char
    if (indexOfLectures[asciiNumberForChar] == FREE_POS) {
      indexOfLectures[asciiNumberForChar] = i;
    }
    // If its already seen more than once give it value of TAKEN_POS
    else {
      indexOfLectures[asciiNumberForChar] = TAKEN_POS;
    }
  }

  std::sort(indexOfLectures.begin(), indexOfLectures.end());

  for (auto&& positions : indexOfLectures) {
    if (positions >= 0) {
      std::cout << positions << ' ';
    }
  }
}