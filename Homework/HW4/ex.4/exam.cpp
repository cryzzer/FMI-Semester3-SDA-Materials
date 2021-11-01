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
    // If there are no nodes, create one and make 'head' and 'tail' to point to
    // the first element
    if (!head) {
      DoublyLinkedListNode* firstNode = new DoublyLinkedListNode(data);
      head = firstNode;
      tail = firstNode;

      nodesCount++;
      return;
    }

    // If there is only one element create a second one and make tail to point
    // him, make middle to point head and connect the two elements with next and
    // previous
    if (head == tail) {
      DoublyLinkedListNode* secondNode = new DoublyLinkedListNode(data);
      head->next = secondNode;
      secondNode->previous = head;
      middle = head;
      tail = secondNode;

      nodesCount++;
      return;
    }

    // Create a new element and make the next element of tail to point the
    // newest one, and the previous elment of the last to point to tail, then
    // move tail to the last element
    DoublyLinkedListNode* newNode = new DoublyLinkedListNode(data);
    tail->next = newNode;
    newNode->previous = tail;
    tail = newNode;

    nodesCount++;

    // After every two pushes move middle 1 position forward
    if (nodesCount % 2 == 0) {
      middle = middle->next;
    }
  }

  void pop_back() {
    if (nodesCount == 0) {
      return;
    }

    // If there is only one element, make head and tail to point to nullptr
    if (head == tail) {
      head = nullptr;
      tail = nullptr;
      nodesCount--;
      return;
    }

    // Create a new temporary tail to point to the new tail, then disconnect all
    // connections with the last element and make tail point to the new tail
    DoublyLinkedListNode* tempTail = tail->previous;
    tempTail->next = nullptr;
    tail->previous = nullptr;
    tail = tempTail;

    nodesCount--;

    // After every two pops, move middle one position backwards
    if (nodesCount % 2 == 1) {
      middle = middle->previous;
    }
  }

  void moveListFromMidToEnd() {
    if (nodesCount < 2) {
      return;
    }
    // If there are two elements swap them
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

    // Create new head middle and tail
    DoublyLinkedListNode* newTail = middle;
    DoublyLinkedListNode* newHead = middle->next;
    DoublyLinkedListNode* newMiddle;

    // If there are even number of elements new middle will be where tail points
    // if not, new middle will point at the element before tail
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

  //Print all elements
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
      linkedList->pop_back();
      continue;
    }
    if (command == "milen") {
      linkedList->moveListFromMidToEnd();
    }
  }

  linkedList->printNodes();
}