#include <iostream>
#include <vector>

class DoublyLinkedListNode {
 public:
  int color;
  int idNumber;
  DoublyLinkedListNode* next;
  DoublyLinkedListNode* previous;

  DoublyLinkedListNode(int color, int idNumber)
      : color(color), idNumber(idNumber), next(nullptr), previous(nullptr) {}
};

class DoublyLinkedList {
  DoublyLinkedListNode* head;
  DoublyLinkedListNode* tail;

 public:
  std::vector<DoublyLinkedListNode*> numberPtrs;

  DoublyLinkedList(int numberCount) : head(nullptr), tail(nullptr) {
    numberPtrs = std::vector<DoublyLinkedListNode*>(numberCount, nullptr);
  }

  void push_backNode(int color, int idNumber) {
    if (!head) {
      DoublyLinkedListNode* firstNode =
          new DoublyLinkedListNode(color, idNumber);
      head = firstNode;
      tail = firstNode;

      numberPtrs[idNumber] = firstNode;
      return;
    }

    if (head == tail) {
      DoublyLinkedListNode* secondNode =
          new DoublyLinkedListNode(color, idNumber);
      head->next = secondNode;
      secondNode->previous = head;
      tail = secondNode;

      numberPtrs[idNumber] = secondNode;
      return;
    }

    DoublyLinkedListNode* newNode = new DoublyLinkedListNode(color, idNumber);
    tail->next = newNode;
    newNode->previous = tail;
    tail = newNode;

    numberPtrs[idNumber] = newNode;
  }

  void insertNote_atPos(int insertionPos, int color, int idNumber) {
    DoublyLinkedListNode* newNode = new DoublyLinkedListNode(color, idNumber);
    numberPtrs.push_back(newNode);

    DoublyLinkedListNode* insertionPtr = numberPtrs[insertionPos];

    if (insertionPtr == tail) {
      insertionPtr->next = newNode;
      newNode->previous = insertionPtr;
      tail = newNode;
      return;
    }

    DoublyLinkedListNode* nextElement = insertionPtr->next;
    nextElement->previous = newNode;
    newNode->next = nextElement;

    insertionPtr->next = newNode;
    newNode->previous = insertionPtr;
  }

  bool isEmptyList() {
    if (head == nullptr && tail == nullptr) {
      return true;
    }
    return false;
  }
};

std::pair<DoublyLinkedListNode*, DoublyLinkedListNode*> addressOfDestroyedBalls(
    DoublyLinkedListNode* hittingBall) {
  int destroyedBallCounter = 1;
  DoublyLinkedListNode* rightMovingIndex = hittingBall;
  DoublyLinkedListNode* leftMovingIndex = hittingBall;

  while (rightMovingIndex->next &&
         rightMovingIndex->color == rightMovingIndex->next->color) {
    rightMovingIndex = rightMovingIndex->next;
    destroyedBallCounter++;
  }
  while (leftMovingIndex->previous &&
         leftMovingIndex->color == leftMovingIndex->previous->color) {
    leftMovingIndex = leftMovingIndex->previous;
    destroyedBallCounter++;
  }

  if (destroyedBallCounter < 3) {
    return std::pair<DoublyLinkedListNode*, DoublyLinkedListNode*>(nullptr,
                                                                   nullptr);
  } else {
    return std::pair<DoublyLinkedListNode*, DoublyLinkedListNode*>(
        leftMovingIndex, rightMovingIndex);
  }
}

int main() {
  int ballsCount;
  std::cin >> ballsCount;

  DoublyLinkedList* list = new DoublyLinkedList(ballsCount);
  int color;
  for (int i = 0; i < ballsCount; i++) {
    std::cin >> color;
    list->push_backNode(color, i);
  }

  int shotRequests;
  std::cin >> shotRequests;

  int shootingPos;
  int ballIdNum = ballsCount;
  for (int i = 0; i < shotRequests; i++) {
    std::cin >> shootingPos >> color;

    if (!list->isEmptyList()) {
      list->insertNote_atPos(shootingPos, color, ++ballIdNum);
      std::pair<DoublyLinkedListNode*, DoublyLinkedListNode*> ballsToRemove =
          addressOfDestroyedBalls(list->numberPtrs[ballIdNum]);
      
      if(ballsToRemove.first && ballsToRemove.second){
        
      }
    }
  }
}