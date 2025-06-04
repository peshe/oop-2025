#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__

#include "task.h"

class Schedule {
private:
    char *name;
    int taskCapacity;
    int taskCount;
    Task **tasks;
    unsigned *startTimes;

    void copy(const Schedule &o);
    void del();

public:
    Schedule(const char *name);
    Schedule(const Schedule &o);

    ~Schedule();

    Schedule &operator=(const Schedule &o);

    bool addTask(
        const Task &task,
        unsigned startHour,
        unsigned startMinute
    );

    void printInHour(unsigned hour) const;
    Task &getMostImportant(
        unsigned hour,
        unsigned minute
    ) const;

    // TODO: write to file
};

#endif // __SCHEDULE_H__
