#include "task_list.hpp"
#include <iostream>

using namespace std;

bool isValidPriority(int priority) {
    // TODO: Return true when priority is from 1 to 5.
    return priority >= 1 && priority <= 5;
}

Task createTask(string description, int priority) {
    Task task;

    task.description = description;
    task.priority = isValidPriority(priority) ? priority : 1;
    task.completed = false;
    
    return task;
}
//peer review (greta): Made spacing edits for readability. 
void insertFront(TaskNode*& head, Task task) {
    TaskNode* newNode = new TaskNode;

    newNode->data = task;
    newNode->next = head;
    head = newNode;
}

int countTasks(const TaskNode* head) {
    int count = 0;
    const TaskNode* current = head;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

TaskNode* findTask(TaskNode* head, string description) {
    while (head != nullptr) {
        if (head->data.description == description) {
            return head;
        }

        head = head->next;
    }

    return nullptr;
}

bool markTaskComplete(TaskNode* head, string description) {
   TaskNode* task = findTask(head, description);

    if (task != nullptr) {
        task->data.completed = true;
        return true;
    }

    return false;
}

int removeCompletedTasks(TaskNode*& head) {
    int removed = 0;

    while (head != nullptr && head->data.completed) {
        TaskNode* temp = head;
        head = head->next;
        delete temp;
        removed++;
    }

TaskNode* current = head;

while (current != nullptr && current->next != nullptr) {
    if (current->next->data.completed) {
        TaskNode* temp = current->next;
        current->next = temp->next;
        delete temp;
        removed++;
     } else {
        current = current->next;
    }
}

    return removed;
}

void clearTasks(TaskNode*& head) {
    while (head != nullptr) {
        TaskNode* temp = head;
        head = head->next;
        delete temp;
    }

    head = nullptr;
}

void printTask(const Task& task) {
    cout << task.description
         << " | priority " << task.priority
         << " | " << (task.completed ? "complete" : "not complete")
         << endl;
}

void printTasks(const TaskNode* head) {
    if (head == nullptr) {
        cout << "No tasks." << endl;
        return;
    }

    const TaskNode* current = head;

    while (current != nullptr) {
        printTask(current->data);
        current = current->next;
    }
}
