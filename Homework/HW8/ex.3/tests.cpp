#include <iostream>
#include <queue>
#include <vector>

class Student {
  public:
  long long submittingTime;
  long long linesCode;
  long long waitingTime = 0;
  Student(long long submittingTime = 0, long long linesCode = 0)
    : submittingTime(submittingTime), linesCode(linesCode) {};
};

// Is equivalent to operator< by comparing lines of code
auto compareCodeLines = [](Student& a, Student& b) {
  if (a.linesCode > b.linesCode) {
    return true;
  }
  return false;
};

// Is equivalent to operator< by comparing time of submittion
auto compareTime = [](Student& a, Student& b) {
  if (a.submittingTime > b.submittingTime) {
    return true;
  }
  return false;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long studentCount;
  std::cin >> studentCount;

  // Let the time of starting the verification of the first task in the queue is
  // 0, this variable is the current time after finishing with any task
  long long currentTime = 0;

  // Sorting the queue by lowest lines of codes
  std::priority_queue<Student, std::vector<Student>, decltype(compareCodeLines)>
    submittedStudents(compareCodeLines);

  // Sorting the queue by time of submittion, at first all assignments are in
  // this queue
  std::priority_queue<Student, std::vector<Student>, decltype(compareTime)>
    notsubmittedStudents(compareTime);

  std::vector<Student> allStudents;

  long long submitTime;
  long long linesCode;

  // Adding all students' assignments in this queue to be reordered
  for (int i = 0; i < studentCount; i++) {
    std::cin >> submitTime >> linesCode;
    Student currStudent(submitTime, linesCode);
    notsubmittedStudents.push(currStudent);
  }

  while (true) {
    // Both queues have to have elements inside to continue this cycle
    if (submittedStudents.empty() && notsubmittedStudents.empty()) {
      break;
    }

    // If the student from the top has submittion time lower than the current
    // time, add it to the submitted queue
    while (!notsubmittedStudents.empty() &&
           notsubmittedStudents.top().submittingTime <= currentTime) {
      submittedStudents.push(notsubmittedStudents.top());
      notsubmittedStudents.pop();
    }

    // If there are submitted students do calculating the waiting time of the
    // student and recalculating the current time
    if (!submittedStudents.empty()) {

      Student nextStudent(submittedStudents.top());
      submittedStudents.pop();

      nextStudent.waitingTime =
        currentTime - nextStudent.submittingTime + nextStudent.linesCode;
      currentTime += nextStudent.linesCode;
      allStudents.push_back(nextStudent);
    }
    // move the top notsubmitted student to the submitted ones and recalculate
    // the current time
    else {
      submittedStudents.push(notsubmittedStudents.top());
      notsubmittedStudents.pop();
      currentTime = submittedStudents.top().submittingTime;
    }
  }

  long long avarageWaitingTime = 0;
  for (auto& x : allStudents) {
    avarageWaitingTime += x.waitingTime;
  }

  std::cout << avarageWaitingTime / allStudents.size();
}
