#include <iostream>
#include <string>
#include <vector>

std::vector<int> examSeats(std::string variants, char uniqueVariant) {
  // getting the length of all available test variants
  // and creating vector, who holds all available seats
  const size_t VARIANT_COUNT = variants.length();
  std::vector<int> allSeats;

  bool hasMetUniqueVar = false;
  int counter = 0;

  for (size_t i = 0; i < VARIANT_COUNT; i++) {
    // we start to go through the array from position 0 to the end, if the
    // unique character/var matches, set the counter to 0 and start to count
    // again
    if (hasMetUniqueVar) {
      if (variants[i] == uniqueVariant) {
        counter = 0;
        allSeats.push_back(counter);
      }
      if (variants[i] != uniqueVariant) {
        allSeats.push_back(++counter);
      }
      continue;
    }

    // the first time we meet the unique variant we start to count from there,
    // and after we meet the unique char again we set the counter to 0
    if (variants[i] == uniqueVariant && (!hasMetUniqueVar)) {
      hasMetUniqueVar = true;
      allSeats.push_back(counter);
      continue;
    } else {
      allSeats.push_back(counter);
    }
  }

  // set the flag to false because the next for will do the exact same thing as
  // the one before, but from the end to the start
  hasMetUniqueVar = false;
  counter = 0;

  // same logic goes here
  for (int i = VARIANT_COUNT - 1; i >= 0; i--) {
    if (variants[i] == uniqueVariant && (!hasMetUniqueVar)) {
      hasMetUniqueVar = true;
      continue;
    }
    if (hasMetUniqueVar) {
      if (variants[i] == uniqueVariant) {
        counter = 0;
      }
      if (variants[i] != uniqueVariant) {
        ++counter;
        // if the number on this position si higher than the counter or equal to
        // zero, set the counter to its place
        if (allSeats[i] > counter || allSeats[i] == 0) {
          allSeats[i] = counter;
        }
      }
    }
  }

  return allSeats;
}

int main() {
  std::string allVariants;
  std::cin >> allVariants;

  char uniqueVariant;
  std::cin >> uniqueVariant;

  std::vector<int> availableSeats;

  availableSeats = examSeats(allVariants, uniqueVariant);

  for (int x : availableSeats) {
    std::cout << x << " ";
  }

  return 0;
}
