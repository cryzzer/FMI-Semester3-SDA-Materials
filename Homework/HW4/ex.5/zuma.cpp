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

  std::vector<DoublyLinkedListNode*> numberPtrs;

 public:
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
      DoublyLinkedListNode* secondNode = new DoublyLinkedListNode(color, idNumber);
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

  void insertNote_atPos(int insertionPos, int color, int idNumber){
      DoublyLinkedListNode* newNode = new DoublyLinkedListNode(color, idNumber);
      numberPtrs.push_back(newNode);

      DoublyLinkedListNode* insertionPtr = numberPtrs[insertionPos];

      if(insertionPtr == tail){
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
};

int main() {}