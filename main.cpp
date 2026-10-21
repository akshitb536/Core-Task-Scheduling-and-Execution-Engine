#include <iostream>
#include <string>
#include "task.hpp"     
#include "scheduler.hpp"

using namespace std;
struct BSTNode {
    userdef* task;
    BSTNode* left;
    BSTNode* right;

    BSTNode(userdef* t) : task(t), left(nullptr), right(nullptr) {}
};

BSTNode* insertBST(BSTNode* root, userdef* task) {
    if (root == nullptr) {
        return new BSTNode(task);
    }
    if (*task < *(root->task)) {
        root->left = insertBST(root->left, task);
    } else {
        root->right = insertBST(root->right, task);
    }
    return root;
}
int countNodes(BSTNode* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}


void extractToArray(BSTNode* root, userdef* tasks[], int& index) {
    if (root == nullptr) return;
    
    extractToArray(root->left, tasks, index);
    tasks[index++] = root->task;
    extractToArray(root->right, tasks, index);
}
void deleteBST(BSTNode* root) {
    if (root == nullptr) return;
    deleteBST(root->left);
    deleteBST(root->right);
    delete root->task; 
    delete root;       
}

int main() {
    BSTNode* root = nullptr;

    cout << "=== CPU Task Scheduling System ===" << endl;
    
    int numTasks;
    cout << "Enter the number of tasks you want to create: ";
    cin >> numTasks;
    for (int i = 0; i < numTasks; ++i) {
        int id, execTime, priority, type;
        
        cout << "\n--- Task " << (i + 1) << " ---" << endl;
        cout << "Enter Task ID (integer): ";
        cin >> id;
        cout << "Enter Execution Time (ms): ";
        cin >> execTime;
        cout << "Enter Task Type (1 for User Task, 2 for System Task): ";
        cin >> type;

        userdef* newTask = nullptr;
        if (type == 2) {
            newTask = new systemdef(id, execTime, "Pending");
            cout << "System Task created (Priority fixed to 1)." << endl;
        } else {
            cout << "Enter Priority (lower number = higher priority): ";
            cin >> priority;
            newTask = new userdef(id, execTime, priority, "Pending");
        }

        
        root = insertBST(root, newTask);
    }

    
    int totalTasks = countNodes(root);
    userdef** taskArray = new userdef*[totalTasks];

    
    int index = 0;
    extractToArray(root, taskArray, index);

    cout << "\n=== Tasks Extracted from BST (Sorted by ID) ===" << endl;
    for (int i = 0; i < totalTasks; ++i) {
        taskArray[i]->display();
    }

    
    int choice, processTime = 10;
    cout << "\nSelect Scheduling Technique:" << endl;
    cout << "1. Simple Queue (FCFS)" << endl;
    cout << "2. Priority Queue" << endl;
    cout << "3. Round Robin" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> choice;

    if (choice == 3) {
        cout << "Enter Process Time (Quantum in ms): ";
        cin >> processTime;
    }

    
    Scheduler cpuScheduler;
    cpuScheduler.executeScheduler(taskArray, totalTasks, choice, processTime);

   
    delete[] taskArray;    
    deleteBST(root);         

    cout << "\nProgram executed successfully and memory cleaned up." << endl;

    return 0;
}