#include <iostream>

#include "schedule.h"
#include "task.h"

int main() {
    Task t("zadacha 1", 10, 10);
    Task t1("zadacha 2", 100, 100);
    Task t2(t);
    t2 = t1;

    t.setStatus(true);
    try {
        t.setStatus(false);
    } catch (const char *e) {
        std::cout << e << std::endl;
    }

    std::fstream file;
    file.open(
        "data.bin",
        std::ios::binary | std::ios::in | std::ios::out
    );

    file << t1;

    file.seekg(0);

    Task t3(file);

    file.close();

    Schedule s("zadachi");
    std::cout << s.addTask(Task("zadacha1", 10, 10), 10, 10) << std::endl;
    std::cout << s.addTask(Task("zadacha2", 5, 100), 15, 15) << std::endl;
    std::cout << s.addTask(Task("zadacha3", 5, 10), 10, 11) << std::endl;
    std::cout << s.addTask(Task("zadacha4", 100, 24 * 60), 0, 0) << std::endl;
    s.printInHour(5);
    return 0;
}
