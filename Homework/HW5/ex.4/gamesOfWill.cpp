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

  // Vector that holds all the addresses of the nodes
  std::vector<Node*> numberPtrs;
  // Vector that hols the addresses of nodes where there will be battle next day
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
    // Remove all pointers who will be deleted from 'numberPtrs' so they can't
    // be accessed anymore when next battle happens
    Node* cursor = start;
    while (cursor != end) {
      numberPtrs[cursor->idNumber] = nullptr;
      cursor = cursor->next;
    }
    numberPtrs[end->idNumber] = nullptr;

    // Rearraging pointers of removed and pointer after end and before start
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

// Doing a linear search for the first time to determine which players will
// drop out and store in a vector the players that will battle the next day
bool ifPlayersBattled(List* list) {
  bool someoneBattled = false;

  Node* currPtr = list->head;
  while (currPtr != nullptr) {
    if (currPtr->next && currPtr->hunger < currPtr->next->hunger) {
      // The player on the left that battled
      Node* battled = currPtr;
      currPtr = currPtr->next;

      someoneBattled = true;

      // If the next player has higher hunger than the current one continue to
      // next one
      while (currPtr != nullptr) {
        if (!(currPtr->next) || currPtr->hunger >= currPtr->next->hunger) {
          break;
        }

        currPtr = currPtr->next;
      }
      Node* endBattle = currPtr;
      currPtr = currPtr->next;
      // Erasing all the player shat were eliminated
      list->erase(battled->next, endBattle);

      // Add the player that battled today if he will battle the next day as
      // well so we can get to him for a constant time
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

// Delete all players that have lost and return a new vector with the pointers
// of players that will battle the next day so they can be accessed for constant
// time
std::vector<Node*> futureBattles(List* list) {
  std::vector<Node*> futurePossibleBattles;

  Node* currPtr;
  for (auto& currentBattle : list->battlePtrs) {
    currPtr = currentBattle;

    // Checking if all pointers that we will use are valid and if the player in
    // the 'numberPtrs' vector has a valid pointer, which indicates if its has
    // been already removed or not
    if (list->numberPtrs[currentBattle->idNumber] && currPtr->next &&
        currPtr->hunger < currPtr->next->hunger) {
      Node* battled = currPtr;
      currPtr = currPtr->next;

      // If the next player has higher hunger than the current one continue to
      // next one
      while (currPtr != nullptr) {
        if (!(currPtr->next) || currPtr->hunger >= currPtr->next->hunger) {
          break;
        }

        currPtr = currPtr->next;
      }
      list->erase(battled->next, currPtr);

      // Add the player that battled today if he will battle the next day as
      // well so we can get to him for a constant time
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