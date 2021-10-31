#pragma once

class SinglyLinkedListNode {
 public:
  int data;
  SinglyLinkedListNode* next;

  SinglyLinkedListNode(int node_data) {
    this->data = node_data;
    this->next = nullptr;
  }
};

SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist,
                                           int data, int position) {
  if (position == 0) {
    SinglyLinkedListNode* start = new SinglyLinkedListNode(data);
    start->next = llist;

    return start;
  }

  SinglyLinkedListNode* head = llist;

  SinglyLinkedListNode* previous;
  for (size_t i = 0; i < position; i++) {
    previous = llist;
    llist = llist->next;
  }

  SinglyLinkedListNode* newPos = new SinglyLinkedListNode(data);
  previous->next = newPos;
  newPos->next = llist;

  return head;
}