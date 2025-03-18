/******************************************************/
/* Примерен код към курса ООП, ФМИ (2025)
*  Пример за работа със структурирани файлове:
*  четене и запис на структури.                       */
/******************************************************/


#include <fstream>
#include <iostream>
#include <cassert>
#include <cstdio>

struct Date
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
};

bool isValidDate(unsigned d, unsigned m, unsigned y)
{
    return true;
}

bool sameDates(const Date& d1, const Date& d2)
{
    return d1.day == d2.day &&
        d1.month == d2.month &&
        d1.year == d2.year;
}

struct Person
{
    char firstName[64];
    char lastName[64];
    Date dob;
};

bool samePersons(const Person& p1, const Person& p2)
{
    return
        strcmp(p1.firstName, p2.firstName) == 0 &&
        strcmp(p1.lastName, p2.lastName) == 0 &&
        sameDates(p1.dob, p2.dob);
}

bool printDate(const Date& d, std::ostream& stream)
{
    stream << (unsigned)d.day << '/' << (unsigned)d.month << '/' << d.year;
    return stream.good();
}

bool readDate(Date& date, std::istream& stream)
{
    unsigned y, m, d;
    char ch;
    stream >> d >> ch;
    if (!stream || ch != '/') return false;
    stream >> m >> ch;
    if (!stream || ch != '/') return false;
    stream >> y;
    if (!stream) return false;
    
    if (!isValidDate(d, m, y)) return false;

    date.day = d;
    date.month = m;
    date.year = y;
    return true;
}

void testDateTextStream()
{
    using namespace std;
    Date dates[] = { { 1999, 3, 11 }, { 2022, 11, 1 } };
    
    const char* const fileName = "dates.txt";

    printDate(dates[0], cout);
    cout << endl;
    fstream file;
    file.open(fileName, ios::out);
    if (!file) {
        cerr << "Not oppened!";
        return;
    }
    for (size_t ind = 0; ind < sizeof(dates) / sizeof(dates[0]); ++ind) {
        if (!printDate(dates[ind], file)) {
            cerr << "Problem print date " << ind << "\n";
            return;
        }
        file << '\n';
    }
    file.close();
    if (file) clog << "Data storred!\n";
    else cerr << "Problem storing!\n";

    file.open(fileName, ios::in);
    if (!file) {
        cerr << "Not oppened!";
        return;
    }

    for (const Date& d : dates) {
        Date read;
        if (!readDate(read, file) || !sameDates(d, read)) {
            cerr << "Problem reading date!\n";
        }
    }

    if (file) clog << "Data read!\n";
    else cerr << "Problem reading!\n";
}

bool printPerson(const Person& p, std::ostream& stream)
{
    stream << p.firstName << '|' << p.lastName << '|';
    printDate(p.dob, stream);
    return stream.good();
}

bool readPerson(Person& p, std::istream& stream)
{
    Person toRead;
    stream.getline(toRead.firstName, sizeof(Person::firstName), '|');
    stream.getline(toRead.lastName, sizeof(Person::lastName), '|');
    if (stream && readDate(toRead.dob, stream)) {
        p = toRead;
    }
    return stream.good();
}

void testPersonTextStream()
{
    using namespace std;
    const Person persons[] = {
        {"Pesho", "Petrov", {1985, 3, 11}},
        {"Maria", "Petrova", {1988, 8, 8}},
        {"Ivan Asen", "Georgiev", {1933, 3, 3}},
        {"Ana-Maria", "Ivanova - Genchova", {2020, 2, 20}}
    };

    const char* const fileName = "persons.txt";

    printPerson(persons[2], cout);
    cout << endl;

    fstream file;
    file.open(fileName, ios::out);
    if (!file) {
        cerr << "Not oppened!";
        return;
    }
    for (size_t ind = 0; ind < sizeof(persons) / sizeof(persons[0]); ++ind) {
        if (!printPerson(persons[ind], file)) {
            cerr << "Problem print person " << ind << "\n";
            printPerson(persons[ind], cerr);
            return;
        }
        file << '\n';
    }

    file.close();
    if (file) clog << "Data storred!\n";
    else cerr << "Problem storing!\n";

    file.open(fileName, ios::in);
    if (!file) {
        cerr << "Not oppened!";
        return;
    }

    for (const Person& p : persons) {
        Person read;
        if (!readPerson(read, file) || !samePersons(p, read)) {
            cerr << "Problem reading person!\n";
            printPerson(p, cerr);
            cerr << '\n';
        }
        else {
            file.ignore();// '\n'
        }
    }

    if (file) clog << "All persons read!\n";
    else cerr << "Problem reading persons!\n";
}

//TODO: Implement binary-file version of the same functionality.
bool writeDate(const Date& d, std::ofstream& file);
bool writePerson(const Person& p, std::ofstream& file);
bool readDate(Date& d, std::ifstream& file);
bool readPerson(Person& p, std::ifstream& file);

int main()
{
    std::fstream file("test.txt", std::ios::in);
    testDateTextStream();
    testPersonTextStream();
}
