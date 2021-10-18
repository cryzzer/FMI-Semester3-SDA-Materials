#include <algorithm>
#include <iostream>  // 2 2 : 4 4 : 0 5 _ 1 1  .  0  4  .  2  0  2  1
#include <string>    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
#include <utility>
#include <vector>

int compareTwoNums(std::string firstDate, std::string secondDate) {
  // Turning strings into integers
  int num1 = std::stoi(firstDate);
  int num2 = std::stoi(secondDate);

  if (num1 < num2) {
    return -1;
  }
  else if (num1 > num2) {
    return 0;
  }
  else {
    return 1;
  }
}

int firstDateIsSmaller(std::string firstDate, std::string secondDate) {
  // As shown above, we take the form element X to element Y from the string to
  // convert each string number into integer number, so we can compare it
  int compareYears =
      compareTwoNums(firstDate.substr(15, 19), secondDate.substr(15, 19));
  if (compareYears == -1) {  // first < second
    return -1;
  }
  else if (compareYears == 0) {
    return 0;
  }

  int compareMonths =
      compareTwoNums(firstDate.substr(12, 14), secondDate.substr(12, 14));
  if (compareMonths == -1) {  // first < second
    return -1;
  }
  else if (compareMonths == 0) {
    return 0;
  }

  int compareDays =
      compareTwoNums(firstDate.substr(9, 11), secondDate.substr(9, 11));
  if (compareDays == -1) {  // first < second
    return -1;
  }
  else if (compareDays == 0) {
    return 0;
  }

  int compareHours =
      compareTwoNums(firstDate.substr(0, 2), secondDate.substr(0, 2));
  if (compareHours == -1) {  // first < second
    return -1;
  }
  else if (compareHours == 0) {
    return 0;
  }

  int compareMinutes =
      compareTwoNums(firstDate.substr(3, 5), secondDate.substr(3, 5));
  if (compareMinutes == -1) {  // first < second
    return -1;
  }
  else if (compareMinutes == 0) {
    return 0;
  }

  int compareSeconds =
      compareTwoNums(firstDate.substr(6, 8), secondDate.substr(6, 8));
  if (compareSeconds == -1) {  // first < second
    return -1;
  }
  else if (compareSeconds == 0) {
    return 0;
  }
  // If both dates are equal return 1;
  else {
    return 1;
  }
}

int main() {
  int logCount;
  std::cin >> logCount;

  std::vector<std::pair<std::string, int>> logs;

  for (int i = 0; i < logCount; i++) {
    // Because when we use cin, after that we use getline, in the buffer there
    // is left one new line character: '\n' and the first time the the for goes
    // to  the getline, it takes this character without waiting for input
    if (i == 0) {
      std::string garbage;
      getline(std::cin, garbage);
    }
    std::string currentLog;
    getline(std::cin, currentLog);

    // The string is the date, and the integer is the position in the queue
    std::pair<std::string, int> pair1(currentLog, i + 1);
    logs.push_back(pair1);
  }

  // Using lambda function with std::sort
  std::sort(logs.begin(), logs.end(),
            [](std::pair<std::string, int>& left,
               std::pair<std::string, int>& right) {
              int decision = firstDateIsSmaller(left.first, right.first);
              // If left date is smaller leave it as it is
              if (decision == -1) {
                return true;
              }
              // If left date is bigger, swap them
              else if (decision == 0) {
                return false;
              }
              // If there are equal, if if the original position of the left one
              // is lower, leave it as it is
              else {
                if (left.second < right.second) {
                  return true;
                }
                // Otherwise swap them
                else {
                  return false;
                }
              }
            });

  for (int i = 0; i < logCount; i++) {
    std::cout << logs[i].second << std::endl;
  }
}