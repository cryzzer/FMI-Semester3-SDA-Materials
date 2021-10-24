#include <algorithm>
#include <iostream>
#include <vector>

int binarySearch(std::vector<int>& themesDifficulty, int left, int right,
                 int teamIntelligence) {
  // These are the numbers that we take if 'teamIntelligence' cannot be found
  // and is between two theme difficulties
  int possibleLowerNum = -1;
  int possibleHighernum = -1;

  // This is the border that indicates when the loop has to stop
  while (left <= right) {
    int middle = (left + right) / 2;

    // If the difficulty matches 'teamIntelligence' return that difficulty
    if (themesDifficulty[middle] == teamIntelligence) {
      return themesDifficulty[middle];
    }
    // If 'teamIntelligence' does not match with any difficulty and is between
    // two difficulties, take them and compare them
    if (themesDifficulty[middle] < teamIntelligence &&
        themesDifficulty[middle + 1] > teamIntelligence) {
      possibleLowerNum = themesDifficulty[middle];
      possibleHighernum = themesDifficulty[middle + 1];
      break;
    }
    // This indicates which side of the array you need to check and divide the
    // array to check all over again
    if (themesDifficulty[middle] > teamIntelligence) {
      right = middle - 1;
    }
    if (themesDifficulty[middle] < teamIntelligence) {
      left = middle + 1;
    }
  }
  // If 'teamIntelligence' is lower that the lowest difficulty, return the
  // lowest difficulty
  if (teamIntelligence < themesDifficulty[0]) {
    return themesDifficulty[0];
  }
  // If 'teamIntelligence' is higher that the highest difficulty, return the
  // highest difficulty
  else if (teamIntelligence > themesDifficulty[themesDifficulty.size() - 1]) {
    return themesDifficulty[themesDifficulty.size() - 1];
  }

  // Return the closest difficulty, and if equal, return the smallest
  if ((teamIntelligence - possibleLowerNum) <=
      (possibleHighernum - teamIntelligence)) {
    return possibleLowerNum;
  }
  else {
    return possibleHighernum;
  }
}

int main() {
  int themesCount;
  std::cin >> themesCount;

  int teamsCount;
  std::cin >> teamsCount;

  std::vector<int> themeDifficulties;
  for (int i = 0; i < themesCount; i++) {
    int themediff;
    std::cin >> themediff;
    themeDifficulties.push_back(themediff);
  }

  std::vector<int> allteams;
  for (int i = 0; i < teamsCount; i++) {
    int team;
    std::cin >> team;
    allteams.push_back(team);
  }

  std::sort(themeDifficulties.begin(), themeDifficulties.end());

  for (int i = 0; i < teamsCount; i++) {
    std::cout << binarySearch(themeDifficulties, 0,
                              themeDifficulties.size() - 1, allteams[i])
              << std::endl;
  }
}