#include "task_list.hpp"
#include <iostream>

using namespace std;

bool isValidPriority(int priority) {
    // Return true when priority is from 1 to 5.
    return priority >= 1 && priority <= 5;
}

Task createTask(string description, int priority) {
    Task task;

    // Store the description.
    task.description = description;

    // Store the priority if valid; otherwise store 1.
    if (isValidPriority(priority)) {
        task.priority = priority; 
    }
    else {
        task.priority = 1;
    }

    // New tasks should start as not completed.
    task.completed = false;

    return task;
}

void insertFront(TaskNode*& head, Task task) {
    // Dynamically allocate a new TaskNode.
    TaskNode* newNode = new TaskNode;

    // Store task in the node.
    newNode->data = task;

    // Point the new node to the old head.
    newNode->next = head;

    // Update head.
    head = newNode;
}

int countTasks(const TaskNode* head) {
    // Traverse the list and count nodes.
    int count = 0;

    const TaskNode* current = head;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

TaskNode* findTask(TaskNode* head, string description) {
    TaskNode* current = head;

    // Traverse the list.
    while (current != nullptr) {

        if (current->data.description == description) {
            return current;
        }

        current = current->next;
    }
    // Return nullptr if not found.
    return nullptr;
}

bool markTaskComplete(TaskNode* head, string description) {
    // Find the task.
    TaskNode* taskNode = findTask(head, description);

    if (taskNode == nullptr) {
        return false;
    }

    taskNode->data.completed = true;

    return true;
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
        }
        else {
            current = current->next;
        }
    }
    // Remove all completed tasks.
    // Return the number of removed nodes.
    // Be sure to handle completed tasks at the head of the list.
    return removed;
}

void clearTasks(TaskNode*& head) {
    // Delete every node in the list.
    while (head != nullptr) {
        TaskNode* temp = head;
        head = head->next;

        delete temp;
    }
    // Set head to nullptr.
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
