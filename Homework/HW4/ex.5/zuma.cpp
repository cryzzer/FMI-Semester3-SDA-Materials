#include <iostream>
#include <sstream>
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
  // Vector to hold the addresses of all Nodes(Balls)
  std::vector<DoublyLinkedListNode*> numberPtrs;

  DoublyLinkedList(int numberCount) : head(nullptr), tail(nullptr) {
    // Fill the vector with null pointers and make it as large as the count of
    // all numbers
    numberPtrs = std::vector<DoublyLinkedListNode*>(numberCount, nullptr);
  }

  void push_backNode(int color, int idNumber) {
    // If there are no elements added, add this one to be the first one
    if (!head) {
      DoublyLinkedListNode* firstNode =
          new DoublyLinkedListNode(color, idNumber);
      head = firstNode;
      tail = firstNode;

      // Add the address of the element to the vector
      numberPtrs[idNumber] = firstNode;
      return;
    }

    // If these is only 1 element added, add this one to be the second one and
    // connect all nodes
    if (head == tail) {
      DoublyLinkedListNode* secondNode =
          new DoublyLinkedListNode(color, idNumber);
      head->next = secondNode;
      secondNode->previous = head;
      tail = secondNode;

      // Add the address of the element to the vector
      numberPtrs[idNumber] = secondNode;
      return;
    }

    // Add the next node and connect them, then move tail to point to the last
    // added node
    DoublyLinkedListNode* newNode = new DoublyLinkedListNode(color, idNumber);
    tail->next = newNode;
    newNode->previous = tail;
    tail = newNode;

    // Add the address of the element to the vector
    numberPtrs[idNumber] = newNode;
  }

  void insertNote_atPos(int insertionPos, int color, int idNumber) {
    DoublyLinkedListNode* newNode = new DoublyLinkedListNode(color, idNumber);
    // push_back the address of this node into the vector
    numberPtrs.push_back(newNode);

    // Take the address of the element that needs to be inserted after
    DoublyLinkedListNode* insertionPtr = numberPtrs[insertionPos];

    // If the new element needs to be inserted after tail, insert it after tail,
    // connect them and move tail to the new element
    if (insertionPtr == tail) {
      insertionPtr->next = newNode;
      newNode->previous = insertionPtr;
      tail = newNode;
      return;
    }

    // Insert the new element between the pointer of 'insertionPtr' and its next
    // element(insertionPtr->next) and connect all of them
    DoublyLinkedListNode* nextElement = insertionPtr->next;
    nextElement->previous = newNode;
    newNode->next = nextElement;

    insertionPtr->next = newNode;
    newNode->previous = insertionPtr;
  }

  bool isEmptyList() {
    // If head and tail are nullpointers, the list is empty and return true
    if (head == nullptr && tail == nullptr) {
      return true;
    }
    return false;
  }

  void erase(DoublyLinkedListNode* start, DoublyLinkedListNode* end) {
    // If the starting position and the ending position of the elements that
    // need to be deleted are head and tail, just kame head and tail point null
    // pointer
    if (start == head && end == tail) {
      head = nullptr;
      tail = nullptr;
      return;
    }

    // If only the start position is head move head to the next position of
    // 'end' and disconnect all connections between the elements that have to be
    // deleted
    if (start == head) {
      head = end->next;
      head->previous = nullptr;
      end->next = nullptr;
      return;
    }

    // If the end position matches with tail, make the new tail to point to the
    // previous element of 'start' and disconnect all connections between the
    // elements that have to be deleted
    if (end == tail) {
      tail = start->previous;
      tail->next = nullptr;
      start->previous = nullptr;
      return;
    }

    // Connect the previous element of 'start' with the next element of 'end'
    // and disconnect all connections between the elements that have to be
    // deleted
    DoublyLinkedListNode* previousElement = start->previous;
    DoublyLinkedListNode* nextElement = end->next;

    previousElement->next = nextElement;
    nextElement->previous = previousElement;

    start->previous = nullptr;
    end->next = nullptr;
  }

  void printBalls() {
    DoublyLinkedListNode* cursor = head;
    while (cursor) {
      std::cout << cursor->color << ' ';
      cursor = cursor->next;
    }
  }
};

std::pair<DoublyLinkedListNode*, DoublyLinkedListNode*> addressOfDestroyedBalls(
    DoublyLinkedListNode* hittingBall, int& destroyedBallsCount) {
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
    destroyedBallsCount = destroyedBallCounter;
    return std::pair<DoublyLinkedListNode*, DoublyLinkedListNode*>(
        leftMovingIndex, rightMovingIndex);
  }
}

bool ifSameBallsCollision(DoublyLinkedListNode* left,
                          DoublyLinkedListNode* right) {
  if (left->color == right->color) {
    return true;
  }
  return false;
}

int main() {
  std::stringstream ss;

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
  int destroyedBallsCount = 0;
  for (int i = 0; i < shotRequests; i++) {
    std::cin >> shootingPos >> color;
    destroyedBallsCount = 0;

    if (!list->isEmptyList()) {
      list->insertNote_atPos(shootingPos, color, ballIdNum);

      std::pair<DoublyLinkedListNode*, DoublyLinkedListNode*>
          ballsToRemovePtrs = addressOfDestroyedBalls(
              list->numberPtrs[ballIdNum], destroyedBallsCount);

      ballIdNum++;
      if (destroyedBallsCount < 3) {
        ss << 0 << '\n';
      }
      //
      else {
        DoublyLinkedListNode* collisionPtrLeft =
            ballsToRemovePtrs.first->previous;
        DoublyLinkedListNode* collisionPtrRight =
            ballsToRemovePtrs.second->next;
        list->erase(ballsToRemovePtrs.first, ballsToRemovePtrs.second);

        if (collisionPtrLeft && collisionPtrRight) {
          int collisionDestroyedBalls = 0;
          do {
            collisionDestroyedBalls = 0;

            if (ifSameBallsCollision(collisionPtrLeft, collisionPtrRight)) {
              ballsToRemovePtrs = addressOfDestroyedBalls(
                  collisionPtrLeft, collisionDestroyedBalls);
              if (collisionDestroyedBalls >= 3) {
                destroyedBallsCount += collisionDestroyedBalls;

                collisionPtrLeft = ballsToRemovePtrs.first->previous;
                collisionPtrRight = ballsToRemovePtrs.second->next;
                list->erase(ballsToRemovePtrs.first, ballsToRemovePtrs.second);
              }
            }
            //
            else {
              break;
            }

          } while (collisionDestroyedBalls >= 3 && collisionPtrLeft &&
                   collisionPtrRight);
        }
        ss << destroyedBallsCount << '\n';
      }
    }
    //
    else {
      ss << "Game Over\n";
    }
  }

  std::cout << ss.str();

  if (list->isEmptyList()) {
    std::cout << -1 << '\n';
  }
  //
  else {
    list->printBalls();
  }

  return 0;
}