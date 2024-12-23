#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

struct TaskNode {
    int taskId;
    int priority;
    int executionTime; // in seconds
    TaskNode* next;

    TaskNode(int id, int prio, int time)
        : taskId(id), priority(prio), executionTime(time), next(nullptr) {}
};

class TaskScheduler {
private:
    TaskNode* head; // Head of the task list

public:
    TaskScheduler() : head(nullptr) {}

    // Insert task by priority
    void insertTask(int id, int priority, int executionTime) {
        TaskNode* newTask = new TaskNode(id, priority, executionTime);

        // Empty list case
        if (!head || head->priority < priority) {
            newTask->next = head;
            head = newTask;
            return;
        }

        // Traverse to find the correct position
        TaskNode* current = head;
        while (current->next && current->next->priority >= priority) {
            current = current->next;
        }

        // Insert the new task
        newTask->next = current->next;
        current->next = newTask;
    }

    // Complete the task at the head
    void completeTask() {
        if (!head) {
            cout << "No tasks to complete.\n";
            return;
        }

        TaskNode* temp = head;
        head = head->next;

        cout << "Task " << temp->taskId << " completed.\n";
        delete temp;
    }

    // Print current task list
    void displayTasks() {
        if (!head) {
            cout << "No tasks in the scheduler.\n";
            return;
        }

        TaskNode* current = head;
        cout << "Current Task List:\n";
        while (current) {
            cout << "Task ID: " << current->taskId
                 << ", Priority: " << current->priority
                 << ", Execution Time: " << current->executionTime << "s\n";
            current = current->next;
        }
    }

    ~TaskScheduler() {
        while (head) {
            completeTask();
        }
    }
};

int main() {
    TaskScheduler scheduler;

    scheduler.insertTask(1, 2, 5);
    scheduler.insertTask(2, 1, 3);
    scheduler.insertTask(3, 3, 2);

    scheduler.displayTasks();

    scheduler.completeTask();
    scheduler.displayTasks();

    scheduler.insertTask(4, 5, 4); // High-priority task
    scheduler.displayTasks();

    return 0;
}
