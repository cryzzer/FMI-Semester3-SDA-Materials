#include <iostream>
#include <vector>
// Let's say that we have 2 vectors with X elements, this way we combine them
// into 1 vector,if the vector has 1 element, we compare each one and writhe the
// lowest one in the first place, then the second one, but if there are more
// than 1 elements, we have something like pointers that point to the position
// of the first element and after comparing with the second vector we move these
// pointers for other comparisons.
void mergeVec(std::vector<int>& ogArray, std::vector<int>& tempArray,
              int beginning, int middle, int end) {
  int leftIndex = beginning;
  int rightIndex = middle + 1;
  int sortedIndex = beginning;

  while (leftIndex <= middle && rightIndex <= end) {
    if (ogArray[leftIndex] < ogArray[rightIndex]) {
      tempArray[sortedIndex] = ogArray[leftIndex];
      leftIndex++;
    } else {
      tempArray[sortedIndex] = ogArray[rightIndex];
      rightIndex++;
    }
    sortedIndex++;
  }

  while (leftIndex <= middle) {
    tempArray[sortedIndex] = ogArray[leftIndex];
    leftIndex++;
    sortedIndex++;
  }
  while (rightIndex <= end) {
    tempArray[sortedIndex] = ogArray[rightIndex];
    rightIndex++;
    sortedIndex++;
  }

  for (int i = beginning; i <= end; i++) {
    ogArray[i] = tempArray[i];
  }
}

// We call this recursive function until there are vectors with only one element
// inside, and then we call the function merge, to compare the elements and
// combine these vectors.
void mergeSortRecursiveVec(std::vector<int>& ogArray,
                           std::vector<int>& tempArray, int beginning,
                           int end) {
  if (beginning < end) {
    int middle = (beginning + end) / 2;
    mergeSortRecursiveVec(ogArray, tempArray, beginning, middle);
    mergeSortRecursiveVec(ogArray, tempArray, middle + 1, end);

    mergeVec(ogArray, tempArray, beginning, middle, end);
  }
}

//Merge sort.
void mergeSortVec(std::vector<int>& ogArray) {
  std::vector<int> tempArray(ogArray.size());
  mergeSortRecursiveVec(ogArray, tempArray, 0, ogArray.size() - 1);
}

// Calculate the lowest sum that has to be paid so every employee has a present.
long long int calculateSmallestSum(std::vector<int>& presents,
                                   size_t employeesCount) {
  long long int sum = 0;
  for (int i = 0; i < employeesCount; i++) {
    sum += presents[i];
  }
  return sum;
}

int main() {
  size_t presentsCount;
  std::cin >> presentsCount;

  std::vector<int> presents;
  for (size_t i = 0; i < presentsCount; i++) {
    int currentPresent;
    std::cin >> currentPresent;
    presents.push_back(currentPresent);
  }

  size_t employeesCount;
  std::cin >> employeesCount;

  mergeSortVec(presents);

  std::cout << calculateSmallestSum(presents, employeesCount);

  return 0;
}