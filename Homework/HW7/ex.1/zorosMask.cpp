#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int masksCount;
  std::cin >> masksCount;

  std::set<int> submasks;
  std::vector<int> allEnteredMasks;

  int currMask;
  for (int i = 0; i < masksCount; i++) {
    std::cin >> currMask;
    allEnteredMasks.push_back(currMask);
  }

  std::sort(allEnteredMasks.begin(), allEnteredMasks.end(),
            [](int& left, int& right) {
              return left > right;
              //
            });

  for (auto& mask : allEnteredMasks) {
    // After sorting the masks in decreasing order so when the submasks of
    // current mask are searched, there can be a faster way by searching if this
    // mask has already been added to the set, or not
    if (submasks.count(mask) == 0) {
      for (int i = mask; i >= 0; i--) {
        // By making bit OR, if the current mask OR the other mask give result
        // equal to current mask, the other mask is a submask to the current one
        // example: 6 | 5 != 6 (110 | 101 = 111)
        // 6 | 4 = 6 (110 | 100 = 110)
        if ((mask | i) == mask) {
          submasks.insert(i);
        }
      }
    }
  }

  std::cout << submasks.size();
}