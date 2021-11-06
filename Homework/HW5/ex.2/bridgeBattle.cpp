#include <iostream>
#include <vector>

int main() {
  unsigned int countOfWarriors;
  std::cin >> countOfWarriors;

  std::vector<int> passedWarriors;

  std::vector<int> positiveWarriors;

  int warrior;
  for (size_t i = 0; i < countOfWarriors; i++) {
    std::cin >> warrior;
    if (warrior < 0) {
      if (positiveWarriors.empty()) {
        passedWarriors.push_back(warrior);
      }
      //
      else {
        while (true) {
          if (positiveWarriors.empty()) {
            passedWarriors.push_back(warrior);
            break;
          }

          if (positiveWarriors.back() == -warrior) {
            positiveWarriors.pop_back();
            break;
          }
          else if (positiveWarriors.back() > -warrior) {
            break;
          }
          // if (positiveWarriors.top() < -warrior)
          positiveWarriors.pop_back();
        }
      }
    }
    else {
      positiveWarriors.push_back(warrior);
    }
  }

  if (passedWarriors.empty() && positiveWarriors.empty()) {
    std::cout << '\n';
  }
  else {
    for (auto& passed : passedWarriors) {
      std::cout << passed << ' ';
    }
    for (auto& positive : positiveWarriors) {
      std::cout << positive << ' ';
    }
  }
}