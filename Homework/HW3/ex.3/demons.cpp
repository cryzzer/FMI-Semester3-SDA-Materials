#include <algorithm>
#include <iostream>
#include <vector>

class Demon {
 public:
  Demon(const int defence = 1, const int attack = 1)
      : defence(defence), attack(attack) {}

  int getDefence() const {
    return defence;
    //
  }
  int getAttack() const {
    return attack;
    //
  }

 private:
  int defence;
  int attack;
};

int maxFights(std::vector<Demon>& allDemons, int size) {
  std::vector<Demon> finalDemonBattled(size, Demon());
  int length = 1;

  finalDemonBattled[0] = allDemons[0];

  for (int i = 1; i < size; i++) {
    int indexToLastDemonBattled =
        std::lower_bound(finalDemonBattled.begin(), finalDemonBattled.end(),
                         allDemons[i],
                         [](const Demon& left, const Demon& right) {
                           if (left.getDefence() > right.getDefence() &&
                               left.getAttack() > right.getAttack()) {
                             return true;
                           } else {
                             return false;
                           }
                         }) -
        finalDemonBattled.begin();

    if (indexToLastDemonBattled == length) {
      finalDemonBattled[length] = allDemons[i];
      length++;
    }
    //
    else {
      finalDemonBattled[indexToLastDemonBattled] = allDemons[i];
    }
  }
  return length;
}

int main() {
  int demonCount;
  std::cin >> demonCount;

  std::vector<Demon> demons;

  int defence;
  int attack;

  for (int i = 0; i < demonCount; i++) {
    std::cin >> defence;

    std::cin >> attack;
    demons.push_back(Demon(defence, attack));
  }

  std::sort(demons.begin(), demons.end(), [](Demon& left, Demon& right) {
    if (left.getDefence() > right.getDefence()) {
      return true;
    }
    //
    else if (left.getDefence() < right.getDefence()) {
      return false;
    }
    //
    else {
      return left.getAttack() >= right.getAttack();
    }
  });

  std::cout << maxFights(demons, demonCount);
}