#include <iostream>

unsigned int presentCount(long long int& points) {
  // How many presents can we buy
  unsigned int presentCount = 0;

  long long int currentNumber = 1;
  long long int i = 1;

  // Loop while there are no points left(points = 0)
  while (points > 0) {
    // Set all numbers to start from 1 and start the loop
    currentNumber = 1;
    i = 1;

    // Then take the cubic equivalent to the number and its higher than our
    // points we we take the one lower number i (i-1) and multiply it by itself
    // three times then subsitute this number from the points and go back to the
    // start
    while (true) {
      currentNumber = i * i * i;

      if (currentNumber > points) {
        break;
      }
      i += 1;
    }

    i -= 1;
    currentNumber = i * i * i;
    points -= currentNumber;
    presentCount += 1;
  }

  return presentCount;
}

int main() {
  long long int points;
  std::cin >> points;

  std::cout << presentCount(points);
}