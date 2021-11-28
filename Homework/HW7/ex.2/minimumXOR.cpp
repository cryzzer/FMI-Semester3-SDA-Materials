#include <iostream>
#include <set>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int requests;
  std::cin >> requests;

  std::set<int> set;
  std::set<int>::iterator itUB, itLB;  // upper and lower bounds
  set.insert(0);

  const int INTMAX = 2147483647;
  // the first minimum is the highest possible integer, so new minimums can be
  // assigned
  int minimum = INTMAX;
  int number;
  for (int i = 0; i < requests; i++) {
    std::cin >> number;
    set.insert(number);

    itLB = set.lower_bound(number);
    itLB = --itLB;
    itUB = set.upper_bound(number);

    if (itUB == set.end()) {  // no upper bound
      if (minimum > (*itLB ^ number)) {
        minimum = (*itLB ^ number);
      }
    }
    //
    else {
      // XOR of upper bound and number is lower
      if ((*itUB ^ number) < (*itLB ^ number)) {
        if (minimum > (*itUB ^ number)) {
          minimum = (*itUB ^ number);
        }
      }
      // XOR of lower bound and number is lower
      else {
        if (minimum > (*itLB ^ number)) {
          minimum = (*itLB ^ number);
        }
      }
    }
    std::cout << minimum << '\n';
  }
}