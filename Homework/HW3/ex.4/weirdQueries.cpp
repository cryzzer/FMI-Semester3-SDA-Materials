#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

class Request {
 public:
  Request(const int& maxSum = 0, const int& maxNumber = 0)
      : maxSum(maxSum), maxNumber(maxNumber) {}
  int maxNumber;
  int maxSum;
};

int binarySearch(std::vector<int>& elements, int left, int right,
                 int highestPossibleNum) {
  while (left <= right) {
    int middle = (left + right) / 2;

    // If there are several numbers, and they are equal, take the one that is on
    // the far left position
    if (highestPossibleNum == elements[middle]) {
      if (middle - 1 >= 0 && elements[middle - 1] == elements[middle]) {
        right = middle - 1;
      } else {
        return middle;
      }
    }

    // If the number is between two numbers, take the lower one
    if (elements[middle] > highestPossibleNum &&
        highestPossibleNum > elements[middle + 1]) {
      return middle + 1;
    }

    if (highestPossibleNum > elements[middle]) {
      right = middle - 1;
    }
    if (highestPossibleNum < elements[middle]) {
      left = middle + 1;
    }
  }

  // If the number is higher than the highest element, take the highest one
  if (highestPossibleNum > elements[0]) {
    return 0;
  }

  return -1;
}

int main() {
  std::ios_base::sync_with_stdio(false);  // Some magic stuff
  std::cin.tie(nullptr);

  int elementCount;
  std::cin >> elementCount;

  int requestCount;
  std::cin >> requestCount;

  std::vector<int> elements;
  int currElement;
  for (int i = 0; i < elementCount; i++) {
    std::cin >> currElement;
    elements.push_back(currElement);
  }

  std::vector<Request> requests;
  int firstRequest;
  int secondRequest;
  for (int i = 0; i < requestCount; i++) {
    std::cin >> firstRequest >> secondRequest;
    requests.push_back(Request(firstRequest, secondRequest));
  }

  // Sorting from highest to lowest
  std::sort(elements.begin(), elements.end(), [](int& left, int& right) {
    if (left >= right) {
      return true;
    }
    return false;
  });

  for (int i = 0; i < requestCount; i++) {
    // Taking the number that is equal or lower to the requested one
    int startingPos =
        binarySearch(elements, 0, elements.size() - 1, requests[i].maxNumber);

    // If there isn't such number or the number is higher that the maximum sum,
    // return 0
    if (startingPos == -1 || elements[startingPos] > requests[i].maxSum) {
      printf("%d \n", 0);
      continue;
    }
    int sum = 0;
    int numsTaken = 0;

    // Doing a linear search while the current sum plus the nex element to be
    // added is lower than the max sum, add that number and write how many
    // numbers we've taken
    for (int j = startingPos; j < elementCount; j++) {
      if (sum + elements[j] <= requests[i].maxSum) {
        sum += elements[j];
        numsTaken++;
      } 
      else {
        break;
      }
    }
    printf("%d \n", numsTaken);
  }
}