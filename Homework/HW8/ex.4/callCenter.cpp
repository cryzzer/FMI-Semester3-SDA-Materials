#include <algorithm>
#include <iostream>
#include <vector>

class Operator {
  static int operatorsCreated;

  public:
  int index;
  long long timeFree;
  int callsTaken;
  Operator() : index(operatorsCreated++), timeFree(0), callsTaken(0) {}
};

int Operator::operatorsCreated = 0;

int main() {
  int countOfClients;
  int countOfOperators;
  std::cin >> countOfClients >> countOfOperators;

  std::vector<Operator> operators(countOfOperators);

  int callTime;
  int callLength;

  // Each call should be positioned at position starting from the 'index %
  // countOfOperators' and move through all free operators that can take the
  // call at this current time
  for (int i = 0; i < countOfClients; i++) {
    std::cin >> callTime >> callLength;

    bool acceptedCall = false;
    for (int j = i % countOfOperators; j < countOfOperators; j++) {
      if (operators[j].timeFree <= callTime) {
        operators[j].timeFree = callTime + callLength;
        operators[j].callsTaken++;
        acceptedCall = true;
        break;
      }
    }
    if (!acceptedCall) {
      for (int j = 0; j < i % countOfOperators; j++) {
        if (operators[j].timeFree <= callTime) {
          operators[j].timeFree = callTime + callLength;
          operators[j].callsTaken++;
          break;
        }
      }
    }
  }

  // Sort operators by most calls taken
  std::sort(operators.begin(), operators.end(),
            [](const Operator& left, const Operator& right) {
              if (left.callsTaken > right.callsTaken) {
                return true;
              } else if (left.callsTaken == right.callsTaken) {
                if (left.index < right.index) {
                  return true;
                }
                return false;
              }
              return false;
            });

  // Print all operators' indexes
  int mostCallsTaken = operators[0].callsTaken;
  std::cout << operators[0].index;

  for (int i = 1; i < countOfOperators; i++) {
    if (operators[i].callsTaken < mostCallsTaken) {
      break;
    }
    std::cout << ' ' << operators[i].index;
  }
}