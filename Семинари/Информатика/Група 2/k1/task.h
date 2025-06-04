#ifndef __TASK_H__
#define __TASK_H__

#include <fstream>

class Task {
private:
    char *description;
    unsigned priority;
    bool status;
    unsigned duration;

    static const unsigned MAX_PRIORITY = 100;

    void setDescription(const char *description);
    void copy(const Task &o);
    
public:
    Task(
        const char *description,
        unsigned priority,
        unsigned duration
    );
    Task(std::istream &file);
    Task(const Task &o);

    ~Task();

    Task &operator=(const Task &o);

    const char *getDescription() const;

    unsigned getPriority() const;
    void setPrioroty(unsigned priotiry);

    bool getStatus() const;
    void setStatus(bool status);

    unsigned getDuration() const;
    void setDuration(unsigned duration);

    void writeToFile(std::ostream &file) const;
};

std::ostream &operator<<(
    std::ostream &file,
    const Task &t
);

#endif // __TASK_H__