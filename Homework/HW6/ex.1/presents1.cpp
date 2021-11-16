#include <iostream>
#include <vector>

struct Node {
  int employee;
  int countOfDescendants;
  std::vector<Node*> descendants;

  Node(int employee = 0) : employee(employee), countOfDescendants(0) {}

  // Calculate how many descendants this root has
  void calculateDescentants() {
    countOfDescendants = descendants.size();
    for (auto& descendant : descendants) {
      countOfDescendants += descendant->countOfDescendants;
    }
  }
};

class GeneralTree {
  private:
  // Having vector to hold pointers to all Nodes for constant accessing
  std::vector<Node*> elementsPtrs;

  public:
  GeneralTree(int peopleCount) {
    elementsPtrs    = std::vector<Node*>(peopleCount, nullptr);
    elementsPtrs[0] = new Node(0);
  }
  void add(int employer, int employee) {
    Node* newEmployee = new Node(employee);
    elementsPtrs[employer]->descendants.push_back(newEmployee);
    elementsPtrs[employee] = newEmployee;
  }

  void calculatePresents() {
    // Calculate all descendants, starting from last to first
    for (int i = elementsPtrs.size() - 1; i >= 0; i--) {
      elementsPtrs[i]->calculateDescentants();
    }
  }

  void printNeededPresents() {
    for (auto& employer : elementsPtrs) {
      std::cout << employer->countOfDescendants << ' ';
    }
  }
};

int main() {
  int workersCount;
  std::cin >> workersCount;

  GeneralTree tree(workersCount);
  int employer;
  int employee;
  for (int i = 1; i < workersCount; i++) {
    std::cin >> employer >> employee;
    tree.add(employer, employee);
  }

  tree.calculatePresents();

  tree.printNeededPresents();
}