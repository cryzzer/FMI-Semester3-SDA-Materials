/* Да пазя поинтърите на елементите във вектор, после след като веднъж обходя
 * линейно да проверявам кой играч трябва да се махне, но в същото време да
 * проверявам за следващите битки този, който се е биел туко що дали ще има
 * битка между него и между следващия играч който трябва да застане до него, и
 * ако има битка да пазя индекса на един от двамата в друг вектор, като на
 * следващото обхождане направо отивам там, и пак същата процедура с
 * проверяването, докато всичко не е ок */

#include <iostream>
#include <vector>

class Node {
 public:
  int hunger;
  int idNumber;
  Node* next;
  Node* previous;

  Node(int hunger, int idNumber)
      : hunger(hunger), idNumber(idNumber), next(nullptr), previous(nullptr) {}
};

class List {
 public:
  Node* head;
  Node* tail;

  std::vector<Node*> numberPtrs;
  std::vector<Node*> battlePtrs;

  List(int numberCount) : head(nullptr), tail(nullptr) {
    numberPtrs = std::vector<Node*>(numberCount, nullptr);
  }

  void push_backNode(int hunger, int idNumber) {
    if (!head) {
      Node* firstNode = new Node(hunger, idNumber);
      head = firstNode;
      tail = firstNode;

      numberPtrs[idNumber] = firstNode;
      return;
    }

    if (head == tail) {
      Node* secondNode = new Node(hunger, idNumber);
      head->next = secondNode;
      secondNode->previous = head;
      tail = secondNode;

      numberPtrs[idNumber] = secondNode;
      return;
    }

    Node* newNode = new Node(hunger, idNumber);
    tail->next = newNode;
    newNode->previous = tail;
    tail = newNode;

    numberPtrs[idNumber] = newNode;
  }

  void erase(Node* start, Node* end) {
    if (start == head && end == tail) {
      head = nullptr;
      tail = nullptr;
      return;
    }

    if (start == head) {
      head = end->next;
      head->previous = nullptr;
      end->next = nullptr;
      return;
    }

    if (end == tail) {
      tail = start->previous;
      tail->next = nullptr;
      start->previous = nullptr;
      return;
    }

    Node* previousElement = start->previous;
    Node* nextElement = end->next;

    previousElement->next = nextElement;
    nextElement->previous = previousElement;

    start->previous = nullptr;
    end->next = nullptr;
  }
};

bool ifPlayersBattled(List* list) {
  bool someoneBattled = false;

  Node* currPtr = list->head;
  while (currPtr != nullptr) {
    if (currPtr->next && currPtr->hunger < currPtr->next->hunger) {
      Node* battled = currPtr;
      currPtr = currPtr->next;

      someoneBattled = true;

      while (currPtr != nullptr) {
        if (!(currPtr->next) || currPtr->hunger >= currPtr->next->hunger) {
          break;
        }

        currPtr = currPtr->next;
      }
      Node* endBattle = currPtr;
      currPtr = currPtr->next;
      list->erase(battled->next, endBattle);

      if (battled->next && battled->hunger < battled->next->hunger) {
        list->battlePtrs.push_back(battled);
      }
    }
    //
    else {
      currPtr = currPtr->next;
    }
  }

  return someoneBattled;
}

std::vector<Node*> futureBattles(List* list) {
  std::vector<Node*> futurePossibleBattles;

  Node* currPtr;
  for (auto& currentBattle : list->battlePtrs) {
    currPtr = currentBattle;
    if (currPtr->next && currPtr->hunger < currPtr->next->hunger) {
      Node* battled = currPtr;
      currPtr = currPtr->next;

      while (currPtr != nullptr) {
        if (!(currPtr->next) || currPtr->hunger >= currPtr->next->hunger) {
          break;
        }

        currPtr = currPtr->next;
      }
      list->erase(battled->next, currPtr);

      if (battled->next && battled->hunger < battled->next->hunger) {
        futurePossibleBattles.push_back(battled);
      }
    }
  }

  return futurePossibleBattles;
}

int main() {
  unsigned int countOfPlayers;
  std::cin >> countOfPlayers;

  List* list = new List(countOfPlayers);
  int addingPlayerHunger;
  for (size_t i = 0; i < countOfPlayers; i++) {
    std::cin >> addingPlayerHunger;
    list->push_backNode(addingPlayerHunger, i);
  }

  int daysPassed = 0;
  if (ifPlayersBattled(list)) {
    daysPassed++;

    while (!(list->battlePtrs.empty())) {
      list->battlePtrs = futureBattles(list); 
      daysPassed++;
    }
  }

  std::cout << daysPassed;
}