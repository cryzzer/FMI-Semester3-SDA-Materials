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

int findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
  // Creating pointers that point to the beginning of 'head1' nad 'head2', and
  // these pointers will move
  SinglyLinkedListNode* list1 = head1;
  SinglyLinkedListNode* list2 = head2;

  // While this pointer is valid( != nullptr)
  while (list1) {
    // set 'list2' to point to the beginning again
    list2 = head2;

    // While this pointer is valid( != nullptr)
    while (list2) {
      // If these two pointes are the same, return the value of the 'data'
      if (list1 == list2) {
        return list1->data;
      }

      // Move the pointer to the next one in the list
      list2 = list2->next;
    }

    // Move the pointer to the next one in the list
    list1 = list1->next;
  }

  // If none are found return `-1`
  return -1;
}