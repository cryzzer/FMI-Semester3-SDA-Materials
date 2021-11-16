#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

class Node {
 public:
  int value;
  Node* left;
  Node* right;

  Node(int value = 0) : value(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
 private:
  Node* root;

  Node* findMinElement(Node* currNode) {
    if (currNode->left != nullptr) {
      return findMinElement(currNode->left);
    }
    return currNode;
  }

  Node* addNode(Node* currNode, int value) {
    if (currNode == nullptr) {
      Node* newElement = new Node(value);
      return newElement;
    }

    if (value < currNode->value) {
      currNode->left = addNode(currNode->left, value);
    }
    if (value >= currNode->value) {
      currNode->right = addNode(currNode->right, value);
    }
    return currNode;
  }

  Node* remove(Node* currNode, int value) {
    if (currNode == nullptr) {
      return nullptr;
    }

    if (value < currNode->value) {
      currNode->left = remove(currNode->left, value);
    }
    //
    else if (value > currNode->value) {
      currNode->right = remove(currNode->right, value);
    }
    //
    else {
      if (currNode->left == nullptr && currNode->right == nullptr) {
        delete currNode;
        return nullptr;
      }
      //
      else if (currNode->left == nullptr || currNode->right == nullptr) {
        Node* temp =
            (currNode->left != nullptr) ? currNode->left : currNode->right;
        delete currNode;
        return temp;
      }

      Node* minElementInLeftSubtree = findMinElement(currNode->right);
      currNode->value = minElementInLeftSubtree->value;
      currNode->right = remove(currNode->right, currNode->value);
    }

    return currNode;
  }

 public:
  BinarySearchTree() : root(nullptr) {}

  void add(int value) {
    root = addNode(root, value);
    //
  }

  void erase(int value) {
    root = remove(root, value);
    //
  }

  void printByLevels() {
    if (root == nullptr) {
      return;
    }

    Node* currNode = root;
    std::queue<Node*> levels;

    levels.push(currNode);

    while (!levels.empty()) {
      currNode = levels.front();
      levels.pop();

      std::cout << currNode->value << ' ';

      if (currNode->left != nullptr) {
        levels.push(currNode->left);
      }
      if (currNode->right != nullptr) {
        levels.push(currNode->right);
      }
    }
  }
};

int main() {
  int countOfElements;
  std::cin >> countOfElements;

  int kBiggestElement;
  std::cin >> kBiggestElement;

  BinarySearchTree tree;
  std::vector<int> sortingContainer;

  int currNumber;
  for (int i = 0; i < countOfElements; i++) {
    std::cin >> currNumber;
    tree.add(currNumber);
    sortingContainer.push_back(currNumber);
  }

  kBiggestElement--;

  std::sort(sortingContainer.begin(), sortingContainer.end(),
            [](int& left, int& right) {
              if (left < right) {
                return false;
              }
              return true;
            });

  tree.erase(sortingContainer[kBiggestElement]);

  tree.printByLevels();
}