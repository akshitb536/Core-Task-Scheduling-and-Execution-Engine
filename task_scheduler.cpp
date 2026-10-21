#include <iostream>
#include <cassert>
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
void runAutomatedTests() {
    cout << "=== Starting Automated Scheduler Tests ===" << endl;
    cout << "\n[Test 1] Verifying Task Getters and System Task Inheritance..." << endl;
    userdef* standardTask = new userdef(105, 25, 4, "Pending");
    assert(standardTask->getTaskID() == 105);
    assert(standardTask->getExecutionTime() == 25);
    assert(standardTask->getPriority() == 4);
    assert(standardTask->getStatus() == "Pending");

    systemdef* systemTask = new systemdef(101, 10, "Pending");
    assert(systemTask->getTaskID() == 101);
    assert(systemTask->getPriority() == 1); 
    cout << "-> Test 1 Passed Successfully!" << endl;
    cout << "\n[Test 2] Verifying BST Insertion and Sorted Extraction..." << endl;
    BSTNode* root = nullptr;
    root = insertBST(root, standardTask);
    root = insertBST(root, systemTask);   
    root = insertBST(root, new userdef(103, 15, 2, "Pending")); 

    int totalTasks = countNodes(root);
    assert(totalTasks == 3);

    userdef** taskArray = new userdef*[totalTasks];
    int index = 0;
    extractToArray(root, taskArray, index);
    assert(taskArray[0]->getTaskID() == 101);
    assert(taskArray[1]->getTaskID() == 103);
    assert(taskArray[2]->getTaskID() == 105);
    cout << "-> Test 2 Passed Successfully!" << endl;
    cout << "\n[Test 3] Verifying Scheduler Execution & Status Updates..." << endl;
    Scheduler cpuScheduler;
    cpuScheduler.executeScheduler(taskArray, totalTasks, 1);
    for (int i = 0; i < totalTasks; ++i) {
        assert(taskArray[i]->getStatus() == "Completed");
    }
    cout << "-> Test 3 Passed Successfully!" << endl;
    delete[] taskArray;
    deleteBST(root);
    cout << "\n=== All Automated Tests Passed Successfully! ===" << endl;
}

int main() {
    runAutomatedTests();
    return 0;
}