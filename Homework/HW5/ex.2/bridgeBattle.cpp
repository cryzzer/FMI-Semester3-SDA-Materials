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
      // If the warrior is negative and there are no positive warrios in the
      // vector, add him to warriors that have passed the bridge
      if (positiveWarriors.empty()) {
        passedWarriors.push_back(warrior);
      }
      //
      else {
        while (true) {
          // If no positive warriors to fight, add negative warrior to passed
          // warriors
          if (positiveWarriors.empty()) {
            passedWarriors.push_back(warrior);
            break;
          }

          // If the last added positive warrior has equal power with the
          // negative, remove them both
          if (positiveWarriors.back() == -warrior) {
            positiveWarriors.pop_back();
            break;
          }

          // If the last added positive warrior has higher power than negative
          // warrior, remove negative warrior
          else if (positiveWarriors.back() > -warrior) {
            break;
          }
          // 'if (positiveWarriors.top() < -warrior)'
          // If negative warrior has higher power than the last added positive
          // one, remove the last positive warrior and continue the loop
          positiveWarriors.pop_back();
        }
      }
    } 
    // If warrior is positive, add him to the vector
    else {
      positiveWarriors.push_back(warrior);
    }
  }

  // Print all passed warriors
  if (passedWarriors.empty() && positiveWarriors.empty()) {
    std::cout << '\n';
  } else {
    for (auto& passed : passedWarriors) {
      std::cout << passed << ' ';
    }
    for (auto& positive : positiveWarriors) {
      std::cout << positive << ' ';
    }
  }
}