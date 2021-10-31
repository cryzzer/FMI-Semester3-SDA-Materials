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
  // If position is 0, we create new `SinglyLinkedListNode` and write its data,
  // next make it point to the original `llist`
  if (position == 0) {
    SinglyLinkedListNode* start = new SinglyLinkedListNode(data);
    start->next = llist;

    return start;
  }
  // Create a pointer to point to the beginning of the original `llist`
  SinglyLinkedListNode* head = llist;

  // Create a pointer to the previous list
  SinglyLinkedListNode* previous;
  for (size_t i = 0; i < position; i++) {
    previous = llist;
    // This pointer now points to the pointer that `next` used to point
    // [1] -> [2] -> [3]
    // if `llist` is a pointer to [1], and `llist->next` points to [2], now
    // llist points to [2] and `llist->next` to [3]
    // previous now points to [1]
    llist = llist->next;
  }

  // Writing the data to the new created list and making previous to point to
  // the newest created list, and this list to point to `llist`
  SinglyLinkedListNode* newPos = new SinglyLinkedListNode(data);
  previous->next = newPos;
  newPos->next = llist;

  return head;
}