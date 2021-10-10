#include <iostream>
#include <string>

using namespace std;

int symbolCounter(std::string word, size_t maxSymbols, char searchedSymbol) {
  //first we get the length of the word and how many chars are counted
  size_t counterSearchedSymbol = 0;
  const size_t WORDLENGTH = word.length();

  //count how many times does the character contain in the word
  size_t searchedSymbolInWord = 0;
  for (size_t i = 0; i < WORDLENGTH; i++) {
    if (word[i] == searchedSymbol) {
      searchedSymbolInWord++;
    }
  }

  //if it contains 0 times, return 0
  if (searchedSymbolInWord == 0) {
    return 0;
  }

  //calculate how many times can we meet the character in the long word
  counterSearchedSymbol = (maxSymbols / WORDLENGTH);
  counterSearchedSymbol *= searchedSymbolInWord;

  //and check for the first part of the word how many times its contained
  for (size_t i = 0; i < maxSymbols % WORDLENGTH; i++) {
      if(word[i] == searchedSymbol){
          counterSearchedSymbol++;
      }
  }

  return counterSearchedSymbol;
}

int main() {
  std::string word;
  std::cin >> word;

  size_t maxSymbols;
  std::cin >> maxSymbols;

  char searchedSymbol;
  std::cin >> searchedSymbol;

  std::cout << symbolCounter(word, maxSymbols, searchedSymbol);
  return 0;
}