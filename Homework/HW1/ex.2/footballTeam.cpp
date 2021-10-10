#include <algorithm>
#include <iostream>
#include <vector>

int lowestFootballOutfit(size_t teamSize, std::vector<int> team) {
  // sorting the vector
  std::sort(team.begin(), team.begin() + teamSize);

  // lowest number of player outfit
  size_t playerNum = 1;
  // bool that indicates that we should check only once if a number is higher
  // than 1
  bool checkIfOne = false;

  for (size_t i = 0; i < teamSize; i++) {
    // if number is lower or equal to 0, continue to next one
    if (team[i] <= 0) {
      continue;
    }
    // if this number is higher than 1, the lowest positive number is 1, and we
    // do check this if only once
    if (!checkIfOne) {
      if (team[i] > 1) {
        break;
      }
      checkIfOne = true;
    }
    // if the number on position 'i' is equal or lower than the next number on
    // position 'i+1' by 1, we continue with the loop
    if (team[i] == team[i + 1] || team[i] + 1 == team[i + 1]) {
      continue;
    }
    // if the number on position 'i' is lower than the next number on position
    // 'i+1' by more than 1, the lowest positive number is on on position 'i',
    // but we add 1 to it
    else if (team[i] < team[i + 1] && team[i] + 1 < team[i + 1]) {
      playerNum = team[i] + 1;
      break;
    }
    // if all the numbers are equal or differ by 1, the answer is the last
    // number + 1
    else {
      playerNum = team[teamSize - 1] + 1;
      break;
    }
  }

  return playerNum;
}

int main() {
  size_t teamSize;
  std::cin >> teamSize;

  std::vector<int> players;
  for (size_t i = 0; i < teamSize; i++) {
    int player;
    std::cin >> player;
    players.push_back(player);
  }

  std::cout << lowestFootballOutfit(teamSize, players);
  return 0;
}