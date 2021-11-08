#include <deque>
#include <iostream>
#include <vector>

struct Node {
  int value;
  int index;
  Node(int value, int index) : value(value), index(index) {}
};

int main(){
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
    if (!subarray.empty() && subarray.front().index <= i - subArraySize) {
        subarray.pop_front();
    }

    while(true){   //(!subarray.empty() && subarray.back().value >= elements[i])
        if(subarray.empty()){
            break;
        }
        if(subarray.back().value < elements[i]){
            break;
        }
        subarray.pop_back();
    }

    subarray.push_back(Node(elements[i],i));

    if(i >= subArraySize - 1){
        sumAllLowestElements += subarray.front().value;
    }
  }

  std::cout << sumAllLowestElements;
  return 0;
}