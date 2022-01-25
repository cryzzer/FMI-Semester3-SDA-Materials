#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int numberCount;
  int k;
  std::cin >> numberCount >> k;

  // Original order of given numbers
  std::vector<int> numbersOrder(numberCount);

  // All results by default are '-1'
  std::vector<int> result(numberCount, -1);

  int currNum;
  for (int i = 0; i < numberCount; i++) {
    std::cin >> currNum;
    numbersOrder[i] = currNum;
  }

  std::multimap<int, int> sortedNums;

  for (int i = numberCount - 1; i >= 0; i--) {
    // Starting from the end towards the start, by inserting the pair into a
    // tree and moving through it by iterator
    int currNum = numbersOrder[i];
    sortedNums.insert({currNum, i});

    auto iterator = sortedNums.find(currNum);
    iterator++;

    while (iterator != sortedNums.end()) {
      // The first time the subtraction between the iterator's number and the
      // current number is higher than 'k' break the loop and continue with the
      // next number in the order
      if (iterator->first - currNum > k) {
        break;
      }
      // If two numbers are equal, continue to the next one
      else if (iterator->first == currNum) {
        iterator++;
      }
      // Make the result at position 'iterator->second' be equal to index 'i',
      // then delete the pair which the iterator is pointing at
      else {
        int resultIndex     = iterator->second;
        result[resultIndex] = i;

        auto nextElement = iterator;
        nextElement--;

        sortedNums.erase(iterator);

        nextElement++;
        iterator = nextElement;
      }
    }
  }

  for (auto element : result) {
    printf("%d ", element);
  }
}