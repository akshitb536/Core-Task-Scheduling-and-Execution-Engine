#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <string>

using namespace std;

class userdef {
protected:
    int taskeid;
    int execution_time;
    int priority;
    string status;

public:
    userdef(int id, int execTime, int prio, string stat) {
        taskeid = id;
        execution_time = execTime;
        priority = prio;
        status = stat;
    }
    virtual ~userdef() {}

    void setStatus(string newStatus) {
        status = newStatus;
    }

    int getTaskID() const { 
        return taskeid; 
    }
    
    int getExecutionTime() const { 
        return execution_time;
    }
    
    int getPriority() const { 
        return priority;
    }
    
    string getStatus() const { 
        return status;
    }
    bool operator<(const userdef& other) const {
        return taskeid < other.taskeid;
    }
    virtual void display() const {
        cout << "Task ID: " << taskeid 
             << " | Exec Time: " << execution_time << "ms" 
             << " | Priority: " << priority 
             << " | Status: " << status << endl;
    }
};

class systemdef : public userdef {
public:
    systemdef(int id, int execTime, string stat) 
        : userdef(id, execTime, 1, stat) { 
    }
};

#endif