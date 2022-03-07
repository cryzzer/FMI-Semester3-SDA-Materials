#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
  int countOfPeople;
  std::cin >> countOfPeople;

  double addPerson;
  double median = 0;

  // MAX heap
  std::priority_queue<double, std::vector<double>> decrHeap;

  // MIN heap
  std::priority_queue<double, std::vector<double>, std::greater<double>>
    incrHeap;

  for (int i = 0; i < countOfPeople; i++) {
    std::cin >> addPerson;

    // Decision where to add the person
    if (addPerson >= median) {
      incrHeap.push(addPerson);
    } else {
      decrHeap.push(addPerson);
    }

    // Maintaining balance between both sizes of the max and min heap.
    // The difference between their sizes has to be at most 1
    if (incrHeap.size() > decrHeap.size() &&
        (incrHeap.size() - decrHeap.size() > 1)) {
      decrHeap.push(incrHeap.top());
      incrHeap.pop();
    } else if (incrHeap.size() < decrHeap.size() &&
               (decrHeap.size() - incrHeap.size() > 1)) {
      incrHeap.push(decrHeap.top());
      decrHeap.pop();
    }

    // Setting the median by deciding if either one of the heaps has bigger
    // size, if yes take the top element to be the new median
    if (decrHeap.size() > incrHeap.size()) {
      median = decrHeap.top();
    } else if (decrHeap.size() < incrHeap.size()) {
      median = incrHeap.top();
    }
    // If they have equal sizes the median will be an avarage between the top
    // element of both heaps
    else {
      median = (decrHeap.top() + incrHeap.top()) / 2;
    }

    // Rounding off to first digit after decimal point
    printf("%.1f\n", median);
  }
}