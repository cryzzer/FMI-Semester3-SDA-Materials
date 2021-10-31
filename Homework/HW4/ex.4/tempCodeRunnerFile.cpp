#include <iostream>
#include <string>

class DoublyLinkedListNode {
 public:
  int data;
  DoublyLinkedListNode* next;
  DoublyLinkedListNode* previous;

  DoublyLinkedListNode(int data)
      : data(data), next(nullptr), previous(nullptr) {}
};

class DoublyLinkedList {
  DoublyLinkedListNode* head;
  DoublyLinkedListNode* middle;
  DoublyLinkedListNode* tail;

  int nodesCount;

 public:
  DoublyLinkedList()
      : head(nullptr), middle(nullptr), tail(nullptr), nodesCount(0) {}

  void push_back(int data) {
    if (!head) {
      DoublyLinkedListNode* firstNode = new DoublyLinkedListNode(data);
      head = firstNode;
      tail = firstNode;

      nodesCount++;
      return;
    }

    if (head == tail) {
      DoublyLinkedListNode* secondNode = new DoublyLinkedListNode(data);
      head->next = secondNode;
      secondNode->previous = head;
      middle = head;
      tail = secondNode;

      nodesCount++;
      return;
    }

    DoublyLinkedListNode* newNode = new DoublyLinkedListNode(data);
    tail->next = newNode;
    newNode->previous = tail;
    tail = newNode;

    nodesCount++;

    if (nodesCount % 2 == 0) {
      middle = middle->next;
    }
  }

  void deleteLastElement() {
    if (head == tail) {
      head = nullptr;
      tail = nullptr;
      nodesCount--;
      return;
    }

    DoublyLinkedListNode* tempTail = tail->previous;
    tempTail->next = nullptr;
    tail->previous = nullptr;
    tail = tempTail;

    nodesCount--;

    if (nodesCount % 2 == 1) {
      middle = middle->previous;
    }
  }

  void moveListFromMidToEnd() {
    if (head->next == tail) {
      head->next = nullptr;
      tail->previous = nullptr;

      DoublyLinkedListNode* temp = head;
      head = tail;
      tail = temp;
      middle = head;

      head->next = tail;
      tail->previous = head;

      return;
    }

    DoublyLinkedListNode* newTail = middle;
    DoublyLinkedListNode* newHead = middle->next;
    DoublyLinkedListNode* newMiddle;
    if (nodesCount % 2 == 0) {
      newMiddle = tail;
    } else {
      newMiddle = tail->previous;
    }

    newHead->previous = nullptr;
    newTail->next = nullptr;

    tail->next = head;
    head->previous = tail;

    head = newHead;
    middle = newMiddle;
    tail = newTail;
  }

  void printNodes() {
    std::cout << nodesCount << '\n';
    DoublyLinkedListNode* movingCursor = head;
    for (int i = 0; i < nodesCount; i++) {
      std::cout << movingCursor->data << ' ';
      movingCursor = movingCursor->next;
    }
  }
};

int main() {
  int requests;
  std::cin >> requests;

  DoublyLinkedList* linkedList = new DoublyLinkedList();

  std::string command;
  int amount;
  for (int i = 0; i < requests; i++) {
    std::cin >> command;
    if (command == "add") {
      std::cin >> amount;
      linkedList->push_back(amount);
      continue;
    }
    if (command == "gun") {
      linkedList->deleteLastElement();
      continue;
    }
    if (command == "milen") {
      linkedList->moveListFromMidToEnd();
    }
  }

  linkedList->printNodes();
}