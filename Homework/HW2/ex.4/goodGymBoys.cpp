#include <algorithm>
#include <iostream>
#include <vector>

class GymBoy {
 public:
  GymBoy(const size_t index = 0, const size_t diameter = 0,
         const size_t time = 0)
      : index(index), diameter(diameter), time(time) {}
  // Efficiency is calculated when you multiply the diameter or the radius by
  // itself and then divide it by time
  double calculateEff() {
    return (double)diameter * (double)diameter / (double)time;
  }
  size_t getDiameter() const {
    return diameter;
  }
  size_t getIndex() const {
    return index;
  }

 private:
  size_t index;
  size_t diameter;
  size_t time;
};

int main() {
  size_t boysCount;
  std::cin >> boysCount;

  std::vector<GymBoy> gymboys;
  for (size_t i = 0; i < boysCount; i++) {
    size_t diameter;
    std::cin >> diameter;

    size_t time;
    std::cin >> time;

    GymBoy bodyBuilder(i + 1, diameter, time);
    gymboys.push_back(bodyBuilder);
  }

  // Using lambda function with std::sort to determine who has the highest
  // efficiency and sort them from high to low
  std::sort(gymboys.begin(), gymboys.end(), [](GymBoy& left, GymBoy& right) {
    // If the left one is higher eff, leave it as it is
    if (left.calculateEff() > right.calculateEff()) {
      return true;
    }
    // Otherwise swap them
    else if (left.calculateEff() < right.calculateEff()) {
      return false;
    }
    // If they have equal eff, put the one with the higher diameter on the first
    // place
    else {
      return left.getDiameter() > right.getDiameter();
    }
  });

  for (auto& boy : gymboys) {
    std::cout << boy.getIndex() << ' ';
  }
}