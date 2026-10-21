#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <iostream>
#include "task.hpp"

using namespace std;

class Scheduler {
private:
    void runSimpleQueue(userdef* tasks[], int size) {
        cout << "\n--- Running Simple Queue (FCFS) ---" << endl;
        for (int i = 0; i < size; ++i) {
            cout << "Executing Task ID: " << tasks[i]->getTaskID() 
                 << " (Takes " << tasks[i]->getExecutionTime() << " ms)" << endl;
            tasks[i]->setStatus("Completed");
        }
    }

    void runPriorityQueue(userdef* tasks[], int size) {
        cout << "\n--- Running Priority Queue ---" << endl;
        
        userdef** sortedTasks = new userdef*[size];
        for (int i = 0; i < size; ++i) {
            sortedTasks[i] = tasks[i];
        }
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if (sortedTasks[j]->getPriority() > sortedTasks[j + 1]->getPriority()) {
                    userdef* temp = sortedTasks[j];
                    sortedTasks[j] = sortedTasks[j + 1];
                    sortedTasks[j + 1] = temp;
                }
            }
        }

        for (int i = 0; i < size; ++i) {
            cout << "Executing Task ID: " << sortedTasks[i]->getTaskID() 
                 << " with Priority: " << sortedTasks[i]->getPriority() << endl;
            sortedTasks[i]->setStatus("Completed");
        }

        delete[] sortedTasks; 
    }

    void runRoundRobin(userdef* tasks[], int size, int processTime) {
        cout << "\n--- Running Round Robin (Process Time: " << processTime << "ms) ---" << endl;
        
        int* remainingTime = new int[size];
        for (int i = 0; i < size; ++i) {
            remainingTime[i] = tasks[i]->getExecutionTime();
        }

        bool allCompleted = false;
        while (!allCompleted) {
            allCompleted = true;
            for (int i = 0; i < size; ++i) {
                if (remainingTime[i] > 0) {
                    allCompleted = false;
                    if (remainingTime[i] > processTime) {
                        cout << "Task " << tasks[i]->getTaskID() << " executed for " << processTime << "ms." << endl;
                        remainingTime[i] -= processTime;
                    } else {
                        cout << "Task " << tasks[i]->getTaskID() << " executed for remaining " << remainingTime[i] << "ms and Finished." << endl;
                        remainingTime[i] = 0;
                        tasks[i]->setStatus("Completed");
                    }
                }
            }
        }
        delete[] remainingTime;
    }

public:
    void executeScheduler(userdef* tasks[], int size, int choice, int processTime = 10) {
        switch (choice) {
            case 1:
                runSimpleQueue(tasks, size);
                break;
            case 2:
                runPriorityQueue(tasks, size);
                break;
            case 3:
                runRoundRobin(tasks, size, processTime);
                break;
            default:
                cout << "Invalid choice! Please select 1, 2, or 3." << endl;
                break;
        }
    }
};

#endif