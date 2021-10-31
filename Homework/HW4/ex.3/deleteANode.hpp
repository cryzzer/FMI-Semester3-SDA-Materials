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

SinglyLinkedListNode* deleteNode(SinglyLinkedListNode* llist, int position) {
  // If position is 0, just return the pointer to the next element, if its
  // nullptr(if head is the only element in the list, it will return nullptr)
  if (position == 0) {
    return llist->next;
  }

  // Create a pointer to point to the beginning of the original `llist`
  SinglyLinkedListNode* head = llist;

  // Create a pointer to the previous list
  SinglyLinkedListNode* previous;
  for (size_t i = 0; i < position; i++) {
    // This pointer now points to the pointer that `next` used to point
    // [1] -> [2] -> [3]
    // if `llist` is a pointer to [1], and `llist->next` points to [2], now
    // llist points to [2] and `llist->next` to [3]
    // previous now points to [1]
    previous = llist;
    llist = llist->next;
  }

  // Previous element now points to the element after 'llist'
  previous->next = llist->next;

  return head;
}