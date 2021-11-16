#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

struct Node {
  int value;
  int xCoords;
  int yCoords;
  Node* left;
  Node* right;

  Node(int value = 0, int xCoords = 0, int yCoords = 0)
    : value(value),
      xCoords(xCoords),
      yCoords(yCoords),
      left(nullptr),
      right(nullptr) {}
};

class BinarySearchTree {
  private:
  Node* root;
  std::vector<Node*> positiveXCoords;
  std::vector<Node*> negativeXCoords;

  std::queue<Node*> parentsToBeDescended;

  void takeElementsPreorder(Node* root) {
    if (root == nullptr) {
      return;
    }

    if (root->xCoords < 0) {
      int xNodeCoords = std::abs(root->xCoords);
      if (negativeXCoords[xNodeCoords]->xCoords == 0) {
        negativeXCoords[xNodeCoords] = root;
      }
      //
      else {
        if (negativeXCoords[xNodeCoords]->yCoords < root->yCoords) {
          negativeXCoords[xNodeCoords] = root;
        }
      }
    }
    if (root->xCoords > 0) {
      int xNodeCoords = root->xCoords;
      if (positiveXCoords[xNodeCoords]->xCoords == 0) {
        positiveXCoords[xNodeCoords] = root;
      }
      //
      else {
        if (positiveXCoords[xNodeCoords]->yCoords < root->yCoords) {
          positiveXCoords[xNodeCoords] = root;
        }
      }
    }
    takeElementsPreorder(root->left);
    takeElementsPreorder(root->right);
  }

  public:
  BinarySearchTree(int elementsCount) {
    root = new Node();
    parentsToBeDescended.push(root);

    positiveXCoords = std::vector<Node*>(elementsCount, new Node());
    negativeXCoords = std::vector<Node*>(elementsCount, new Node());
  }

  void addDescendands(int left, int right) {
    if (parentsToBeDescended.empty()) {
      return;
    }

    Node* currNode = parentsToBeDescended.front();
    parentsToBeDescended.pop();

    if (left != -1) {
      currNode->left =
        new Node(left, currNode->xCoords - 1, currNode->yCoords - 1);
      parentsToBeDescended.push(currNode->left);
    }

    if (right != -1) {
      currNode->right =
        new Node(right, currNode->xCoords + 1, currNode->yCoords - 1);
      parentsToBeDescended.push(currNode->right);
    }
  }

  void printTreeSpikes() {
    takeElementsPreorder(root);

    std::sort(negativeXCoords.begin(), negativeXCoords.end(),
              [](Node* left, Node* right) {
                if (left->xCoords < right->xCoords) {
                  return true;
                }
                return false;
              });

    for (auto& negativeCoordinates : negativeXCoords) {
      if (negativeCoordinates->xCoords == 0) {
        break;
      }
      std::cout << negativeCoordinates->value << ' ';
    }

    std::cout << root->value << ' ';

    for (auto& positiveCoordinates : positiveXCoords) {
      if (positiveCoordinates->xCoords != 0) {
        std::cout << positiveCoordinates->value << ' ';
      }
    }
  }
};

int main() {
  int countOfElements;
  std::cin >> countOfElements;

  BinarySearchTree tree(countOfElements);

  int leftChild;
  int rightChild;
  for (int i = 0; i < countOfElements; i++) {
    std::cin >> leftChild >> rightChild;
    tree.addDescendands(leftChild, rightChild);
  }

  tree.printTreeSpikes();
}