#include "task.h"

#include <cstring>

void Task::setDescription(const char *description) {
    int len = strlen(description);
    this->description = new char[len + 1];
    strcpy_s(this->description, len + 1, description);
}

void Task::copy(const Task &o) {
    this->setDuration(o.duration);
    this->setPrioroty(o.priority);
    this->setStatus(o.status);
    this->setDescription(o.description);
}

Task::Task(
    const char *description,
    unsigned priority,
    unsigned duration
) {
    this->status = false;
    this->setPrioroty(priority);
    this->setDuration(duration);
    this->setDescription(description);
}

Task::Task(std::istream &file) {
    file.read(
        (char *)&this->duration,
        sizeof(this->duration)
    );
    file.read(
        (char *)&this->status,
        sizeof(this->status)
    );
    file.read(
        (char *)&this->priority,
        sizeof(this->priority)
    );
    int len;
    file.read(
        (char *)&len,
        sizeof(len)
    );
    this->description = new char[len];
    file.read(this->description, len);
}

Task::Task(const Task &o) {
    this->status = false;
    this->copy(o);
}

Task::~Task() {
    delete[] this->description;
}

Task &Task::operator=(const Task &o) {
    delete[] this->description;

    this->copy(o);

    return *this;
}

const char *Task::getDescription() const {
    return this->description;
}

unsigned Task::getPriority() const {
    return this->priority;
}

void Task::setPrioroty(unsigned priority) {
    if (priority > MAX_PRIORITY) {
        throw "Invalid priority";
    }

    this->priority = priority;
}

bool Task::getStatus() const {
    return this->status;
}

void Task::setStatus(bool status) {
    if (this->status) {
        throw "Can't undo task";
    }

    this->status = status;
}

unsigned Task::getDuration() const {
    return this->duration;
}

void Task::setDuration(unsigned duration) {
    this->duration = duration;
}

void Task::writeToFile(std::ostream &file) const {
    file.write(
        (char *)&this->duration,
        sizeof(this->duration)
    );
    file.write(
        (char *)&this->status,
        sizeof(this->status)
    );
    file.write(
        (char *)&this->priority,
        sizeof(this->priority)
    );
    int len = strlen(this->description) + 1;
    file.write(
        (char *)&len,
        sizeof(len)
    );
    file.write(this->description, len);
}

std::ostream &operator<<(
    std::ostream &file,
    const Task &t
) {
    t.writeToFile(file);
}
