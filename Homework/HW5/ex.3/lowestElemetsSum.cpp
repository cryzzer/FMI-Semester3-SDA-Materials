#include <deque>
#include <iostream>
#include <vector>

class Node {
 public:
  int value;
  int index;
  Node(int value, int index) : value(value), index(index) {}
};

int main() {
  unsigned int countOfElements;
  std::cin >> countOfElements;

  int subArraySize;
  std::cin >> subArraySize;

  std::vector<int> elements;
  int currElement;
  for (int i = 0; i < countOfElements; i++) {
    std::cin >> currElement;
    elements.push_back(currElement);
  }

  long long int sumAllLowestElements = 0;
  std::deque<Node> subarray;
  for (int i = 0; i < countOfElements; i++) {
    // If the element does not belong in the current subarray any longer, remove
    // it form it
    if (!subarray.empty() && subarray.front().index <= i - subArraySize) {
      subarray.pop_front();
    }

    // Keep the subarray in decreasing order, also remove all elements that are
    // lower than the next element to be added
    while (true) {
      if (subarray.empty()) {
        break;
      }
      if (subarray.back().value < elements[i]) {
        break;
      }
      subarray.pop_back();
    }

    subarray.push_back(Node(elements[i], i));

    // If the first element belongs in the subarray, add it to the sum
    if (i >= subArraySize - 1) {
      sumAllLowestElements += subarray.front().value;
    }
  }

  std::cout << sumAllLowestElements;
  return 0;
}