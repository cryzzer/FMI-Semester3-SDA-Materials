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
    // Print all elements
    DoublyLinkedListNode* cursor = head;
    while (cursor) {
      std::cout << cursor->color << ' ';
      cursor = cursor->next;
    }
  }
};

std::pair<DoublyLinkedListNode*, DoublyLinkedListNode*> addressOfDestroyedBalls(
    DoublyLinkedListNode* hittingBall, int& destroyedBallsCount) {
  // The destroyed balls count is always one because we include the the ball
  // that we shoot
  int destroyedBallCounter = 1;

  // Creating two indexes that will move to the left and to the right of the
  // hitting ball
  DoublyLinkedListNode* rightMovingIndex = hittingBall;
  DoublyLinkedListNode* leftMovingIndex = hittingBall;

  // While the next pointer is valid pointer and both colors match continue to
  // the right
  while (rightMovingIndex->next &&
         rightMovingIndex->color == rightMovingIndex->next->color) {
    rightMovingIndex = rightMovingIndex->next;
    destroyedBallCounter++;
  }
  // While the next pointer is valid pointer and both colors match continue to
  // the left
  while (leftMovingIndex->previous &&
         leftMovingIndex->color == leftMovingIndex->previous->color) {
    leftMovingIndex = leftMovingIndex->previous;
    destroyedBallCounter++;
  }

  // If there are less than 3 balls destroyed, return null pointers so that no
  // elements will be deleted
  if (destroyedBallCounter < 3) {
    return std::pair<DoublyLinkedListNode*, DoublyLinkedListNode*>(nullptr,
                                                                   nullptr);
  }
  // If there are at least 3 balls destroyed, return the pointers to these
  // elements that that equals to the start and the end of the elements that
  // need to be deleted
  else {
    destroyedBallsCount = destroyedBallCounter;
    return std::pair<DoublyLinkedListNode*, DoublyLinkedListNode*>(
        leftMovingIndex, rightMovingIndex);
  }
}

bool ifSameBallsCollision(DoublyLinkedListNode* left,
                          DoublyLinkedListNode* right) {
  // If both elements have the same colors, return true
  if (left->color == right->color) {
    return true;
  }
  return false;
}

int main() {
  // Using string stream to write all outputs into one string
  std::stringstream ss;

  int ballsCount;
  std::cin >> ballsCount;

  // Filling the list with the first elements
  DoublyLinkedList* list = new DoublyLinkedList(ballsCount);
  int color;
  for (int i = 0; i < ballsCount; i++) {
    std::cin >> color;
    list->push_backNode(color, i);
  }

  int shotRequests;
  std::cin >> shotRequests;

  int shootingPos;

  // This integer will determine the IDs of all new balls that will be shot
  int ballIdNum = ballsCount;
  int destroyedBallsCount = 0;
  for (int i = 0; i < shotRequests; i++) {
    std::cin >> shootingPos >> color;
    destroyedBallsCount = 0;  // set the balls that are destroyed to 0

    // If the list is not empty continue the with shooting
    if (!list->isEmptyList()) {
      // Shooting a ball at 'shootingPos' position and in the same time give the
      // color to the new ball and give it Id as well
      list->insertNote_atPos(shootingPos, color, ballIdNum);

      // Take the addresses of the start and the end where the balls have to be
      // deleted
      std::pair<DoublyLinkedListNode*, DoublyLinkedListNode*>
          ballsToRemovePtrs = addressOfDestroyedBalls(
              list->numberPtrs[ballIdNum], destroyedBallsCount);

      ballIdNum++;  // Increase the id of next ball

      // If there are potentially less than 3 destroyed balls, cout that there
      // are 0 destroyed balls this turn
      if (destroyedBallsCount < 3) {
        ss << 0 << '\n';
      }
      // If there are potentially more than or exactly 3 destroyed balls,
      // continue with deleting
      else {
        // If there are potentially more than or exactly 3 destroyed balls, get
        // the indexes of the element before start and after end to check for
        // collision
        DoublyLinkedListNode* collisionPtrLeft =
            ballsToRemovePtrs.first->previous;
        DoublyLinkedListNode* collisionPtrRight =
            ballsToRemovePtrs.second->next;

        // Delete those elements
        list->erase(ballsToRemovePtrs.first, ballsToRemovePtrs.second);

        // Check if these pointers are valid
        if (collisionPtrLeft && collisionPtrRight) {
          int collisionDestroyedBalls = 0;

          // Try at least one to check if the two balls that will collide are
          // with the same color
          do {
            collisionDestroyedBalls = 0;

            // Checking for same color here
            if (ifSameBallsCollision(collisionPtrLeft, collisionPtrRight)) {
              // If they have the same color, pick one of the two pointers and
              // try to find how many potentially destroyed balls there will be,
              // and find their addresses
              ballsToRemovePtrs = addressOfDestroyedBalls(
                  collisionPtrLeft, collisionDestroyedBalls);

              // If there are 3 or more destroyed balls delete them, and and get
              // the addresses before start and after end, then delete them
              if (collisionDestroyedBalls >= 3) {
                destroyedBallsCount += collisionDestroyedBalls;

                collisionPtrLeft = ballsToRemovePtrs.first->previous;
                collisionPtrRight = ballsToRemovePtrs.second->next;
                list->erase(ballsToRemovePtrs.first, ballsToRemovePtrs.second);
              }
            }
            // If the two colors do not match, break the loop
            else {
              break;
            }

            // Do this loop while there are 3 or more destroyed balls and the
            // two pointers are valid
          } while (collisionDestroyedBalls >= 3 && collisionPtrLeft &&
                   collisionPtrRight);
        }
        // Write the number of destroyed balls this turn in this string
        ss << destroyedBallsCount << '\n';
      }
    }
    // If the list is empty write game over in the string
    else {
      ss << "Game Over\n";
    }
  }

  // After the requests have finished print all messages regarding the destroyed
  // balls and if there are no balls left, game over
  std::cout << ss.str();

  // If there are no balls in the list, cout -1
  if (list->isEmptyList()) {
    std::cout << -1 << '\n';
  }
  // else, print all balls in the list
  else {
    list->printBalls();
  }

  return 0;
}