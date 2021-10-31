#include <iostream>

class DoublyLinkedListNode {
 public:
  int data;
  DoublyLinkedListNode* next;
  DoublyLinkedListNode* previous;

  DoublyLinkedListNode(int data) : data(data), next(nullptr), previous(nullptr) {}
};

class DoublyLinkedList {
    public:
    DoublyLinkedListNode* head;
    DoublyLinkedListNode* middle;
    DoublyLinkedListNode* tail;

    int nodesCount;

    DoublyLinkedList() : head(nullptr), middle(nullptr), tail(nullptr), nodesCount(0){}

};



int main() {
  int requests;
  std::cin >> requests;

}