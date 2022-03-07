#include <iostream>
#include <queue>
#include <vector>

class Task {
  public:
  long long startingTime;
  long long duration;
  long long index;

  Task(long long startingTime = 0, long long duration = 0, long long index = 0)
    : startingTime(startingTime), duration(duration), index(index) {}
};

// Is equivalent to operator< by comparing duration
auto compareDuration = [](Task& a, Task& b) {
  if (a.duration > b.duration) {
    return true;
  } else if (a.duration == b.duration) {
    return a.index > b.index;
  }
  return false;
};

// Is equivalent to operator< by comparing starting time
auto compareTime = [](Task& a, Task& b) {
  if (a.startingTime > b.startingTime) {
    return true;
  }
  return false;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long countOfTasks;
  std::cin >> countOfTasks;

  // Let the time of starting the first task in the queue is 0, this variable is
  // the current time after completing any task
  long long currentTime = 0;

  // One heap that holds all tasks sorted by their starting time starting from
  // the lowest starting time
  std::priority_queue<Task, std::vector<Task>, decltype(compareTime)>
    notpoppedUpTask(compareTime);

  // The other one holds all tasks that have been sorted by duration in
  // increasing order
  std::priority_queue<Task, std::vector<Task>, decltype(compareDuration)>
    poppedUpTask(compareDuration);

  std::vector<Task> taskOrder;

  long long startTime;
  long long duration;

  // Entering all tasks in the 'notpoppedUpTask' queue in order to sort them by
  // lowest duration to complete the task to minimise the total time the tasks
  // have to be completed for
  for (int i = 0; i < countOfTasks; i++) {
    std::cin >> startTime >> duration;
    Task currTask(startTime, duration, i);
    notpoppedUpTask.push(currTask);
  }

  while (true) {
    // Both queues have to have elements inside to continue this cycle
    if (poppedUpTask.empty() && notpoppedUpTask.empty()) {
      break;
    }

    // While the starting time of the next task is lower than the current time,
    // move it to the next queue
    while (!notpoppedUpTask.empty() &&
           notpoppedUpTask.top().startingTime <= currentTime) {
      poppedUpTask.push(notpoppedUpTask.top());
      notpoppedUpTask.pop();
    }

    // When moved to 'poppedUpTask' queue they are sorted by lowest time to
    // complete
    if (!poppedUpTask.empty()) {
      Task nextTask(poppedUpTask.top());
      poppedUpTask.pop();

      // After completing the task, add its duration to the total time
      // 'currentTime' and add its index to the container that holds the
      // sequence of completed tasks
      currentTime += nextTask.duration;
      taskOrder.push_back(nextTask);
    }
    // If there are no requests in the queue with popped up requests, add the
    // first in the 'notpoppedUpTask' queue to it and change the current time to
    // be the starting time of this task, because since there haven't been sent
    // any request, the worker has waited for a new one to arrive
    else {
      poppedUpTask.push(notpoppedUpTask.top());
      notpoppedUpTask.pop();
      currentTime = poppedUpTask.top().startingTime;
    }
  }

  for (auto& x : taskOrder) {
    printf("%lld ", x.index);
  }
}