#pragma once


class StaticData
{
public:
    StaticData(int val = 0);
    StaticData(int val, const char* name);
    StaticData(const StaticData& other);
    StaticData(StaticData&& other) noexcept;
    ~StaticData() noexcept;

    StaticData& operator=(const StaticData& other);
    StaticData& operator=(StaticData&& other) noexcept;

    int getID() const noexcept;
    const char* getName() const noexcept { return name; }
    bool setName(const char* name);

    static int getNumInstances() { return instances; }

private:
    static int getNextId();

private:
    int value;
    char* name;

    const int ID;

    static int instances;
    static int nextId;
    static StaticData obj;
};
