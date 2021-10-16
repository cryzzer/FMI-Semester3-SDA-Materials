#include <iostream>
#include <string>
#include <vector>

//turning char into encoded number
int fromCharToNum(char player) {
  //from '0'-'9' goes to 1-10
  if (player >= '0' && player <= '9') {
    const int asciiDigitShift = 1;
    return (player - '0') + asciiDigitShift;
  } 
  //from 'a'-'z' goes to 11-36
  else if (player >= 'a' && player <= 'z') {
    const int asciiLowerCaseLetterShift = 38;
    return (player - '0') - asciiLowerCaseLetterShift;
  } 
  //from 'A'-'Z' goes to 37-62
  else if (player >= 'A' && player <= 'Z') {
    const int asciiUpperCaseLetterShift = 20;
    return (player - '0') + asciiUpperCaseLetterShift;
  } 
  else {
    return 0;
  }
}

//turning int to char
char formNumToChar(int number) {
  //from 1-10 goes to '0'-'9'
  if (number >= 1 && number <= 10) {
    const int asciiDigitShift = 1;
    return (number - asciiDigitShift) + '0';
  } 
  //from 11-36 goes to 'a'-'z'
  else if (number >= 11 && number <= 36) {
    const int asciiLowerCaseLetterShift = 38;
    return (number + asciiLowerCaseLetterShift) + '0';
  } 
  //from 37-62 goes to 'A' - 'Z'
  else if (number >= 37 && number <= 62) {
    const int asciiUpperCaseLetterShift = 20;
    return (number - asciiUpperCaseLetterShift) + '0';
  } 
  else {
    return '-';
  }
}

void countingSortVec(std::vector<int>& arr) {
  int maxNumber = 0;  // or some very small number

  // Finding highest number
  for (auto x : arr) {
    if (x > maxNumber) {
      maxNumber = x;
    }
  }

  // Creating a storage where we will store how many times a number is met
  std::vector<int> countingArr(maxNumber + 1);

  // When we see a number, we add 1 to its position in the container were we
  // count how many times we've met it
  for (auto numberFromArr : arr) {
    countingArr[numberFromArr] += 1;
  }

  // this indicates if on this position in the container there are written any
  // numbers
  int sortedIndex = 0;

  for (int i = 0; i < arr.size(); i++) {
    // if on this position there are no repeated numbers, continue to the next
    // one
    while (countingArr[sortedIndex] == 0) {
      sortedIndex += 1;
    }

    // let the number on position [i] be equal to the position where there are
    // many elements of this index
    arr[i] = sortedIndex;

    // after that lower their count and redo all of this until their count is 0
    // example: if we have two 1's(ones) in the original array we will write
    // "1", after that the count of the ones will lower to one, and after that
    // it will be added to the original array as "1,1", and once their count is
    // 0, it will t the next position where there can be 0 elements of this type
    // or more than 1
    countingArr[sortedIndex] -= 1;
  }
}

int main() {
  unsigned int playerCount;
  std::cin >> playerCount;

  std::vector<int> codedPlayers;

  for (size_t i = 0; i < playerCount; i++) {
    char player;
    std::cin >> player;

    //encoding all characters with their value into numbers
    codedPlayers.push_back(fromCharToNum(player));
  }

  countingSortVec(codedPlayers);

  for (size_t i = 0; i < playerCount; i++) {
    //decoding the numbers back to chars
    std::cout << formNumToChar(codedPlayers[i]);
  }

  return 0;
}