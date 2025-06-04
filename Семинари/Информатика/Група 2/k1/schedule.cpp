#include "schedule.h"

#include <cstring>
#include <iostream>

bool areTasksIntersecting(
    const Task &t1, unsigned s1,
    const Task &t2, unsigned s2
) {
    return s1 < s2 + t2.getDuration() && s2 < s1 + t1.getDuration();
}

void Schedule::copy(const Schedule &o) {
    int len = strlen(o.name);
    this->name = new char[len + 1];
    strcpy_s(this->name, len + 1, o.name);

    this->tasks = new Task*[o.taskCapacity];
    this->startTimes = new unsigned[o.taskCapacity];
    this->taskCapacity = o.taskCapacity;
    this->taskCount = o.taskCount;
}

void Schedule::del() {
    delete[] this->name;
    for (int i = 0; i < this->taskCount; i++) {
        delete this->tasks[i];
    }
    delete[] this->tasks;
    delete[] this->startTimes;
}

Schedule::Schedule(const char *name) {
    int len = strlen(name);
    this->name = new char[len + 1];
    strcpy_s(this->name, len + 1, name);

    this->taskCapacity = 4;
    this->taskCount = 0;
    this->tasks = new Task*[this->taskCapacity];
    this->startTimes = new unsigned[this->taskCapacity];
}

Schedule::Schedule(const Schedule &o) {
    this->copy(o);
}

Schedule::~Schedule() {
    this->del();
}

Schedule &Schedule::operator=(const Schedule &o) {
    this->del();
    this->copy(o);
}

bool Schedule::addTask(
    const Task &task,
    unsigned startHour,
    unsigned startMinute
) {
    unsigned startTime = startHour * 60 + startMinute;
    if (startTime + task.getDuration() > 24 * 60) {
        throw
            "Task continues after the end of the day";
    }

    for (int i = 0; i < this->taskCount; i++) {
        if (this->startTimes[i] == startTime) {
            throw "Duplicate start time";
        }

        if (areTasksIntersecting(
            task, startTime,
            *this->tasks[i], this->startTimes[i]
        )) {
            if (task.getPriority() < this->tasks[i]->getPriority()) {
                return false;
            }
        }
    }
    std::cout << "Task count" << this->taskCount << std::endl;
    for (int i = 0; i < this->taskCount; i++) {
        if (areTasksIntersecting(
            task, startTime,
            *this->tasks[i], this->startTimes[i]
        )) {
            if (task.getPriority() > this->tasks[i]->getPriority()) {
                delete this->tasks[i];
                for (int j = i + 1; j < this->taskCount; j++) {
                    this->tasks[j - 1] = this->tasks[j];
                    this->startTimes[j - 1] = this->startTimes[j];
                }
                this->taskCount--;
                i--;
            }
        }
    }

    int insertIndex;
    for (insertIndex = 0; insertIndex < this->taskCount; insertIndex++) {
        if (this->startTimes[insertIndex] > startTime) {
            break;
        }
    }

    if (this->taskCount + 1 > this->taskCapacity) {
        this->taskCapacity *= 2;
        Task **newTasks = new Task*[this->taskCapacity];
        unsigned *newTimes = new unsigned[this->taskCapacity];
        for (int i = 0; i < taskCount; i++) {
            newTasks[i] = this->tasks[i];
            newTimes[i] = this->startTimes[i];
        }
        delete[] this->tasks;
        delete[] this->startTimes;
        this->tasks = newTasks;
        this->startTimes = newTimes;
    }

    if (this->taskCount > 0) {
        for (int i = this->taskCount - 1; i >= insertIndex; i--) {
            this->tasks[i + 1] = this->tasks[i];
        }
    }
    this->tasks[insertIndex] = new Task(task);
    this->startTimes[insertIndex] = startTime;
    this->taskCount++;

    return true;
}

void Schedule::printInHour(unsigned hour) const {
    unsigned startTime = hour * 60;
    Task tmp("temp", 0, 60);

    for (int i = 0; i < this->taskCount; i++) {
        if (
            !this->tasks[i]->getStatus() &&
            areTasksIntersecting(
                tmp, startTime,
                *this->tasks[i], this->startTimes[i]
            )
        ) {
            std::cout << this->tasks[i]->getDescription() << std::endl;
        }
    }
}

Task &Schedule::getMostImportant(
    unsigned hour,
    unsigned minute
) const {
    unsigned time = hour * 60 + minute;

    for (int i = 0; i < this->taskCount; i++) {
        if (
            this->startTimes[i] <= time &&
            this->startTimes[i] + this->tasks[i]->getDuration() >= time
        ) {
            return *this->tasks[i];
        }
    }
}
