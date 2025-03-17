#include <iostream>
#include <cstring>
#include <fstream>

/* Бинарни файлове
    *   Бинарните файлове са файлове, които съхраняват информацията си в същия вид, в който са в паметта на компютъра.
        Тоест бинарните файловете съдържат информация в необработен вид, което означава,
        че данните са представени като последователност от байтове.
        Това е в контраст с текстовите файлове, които съдържат информация във вид, който е четим от човек (ASCII).

    *   Поради различния си формат, бинарните файлове са по-ефективни от текстовите файлове при съхраняване на данни.
        Те са по-бързи и по-малки, тъй като не извършват допълнителни трансформации върху съдържанието си.

    *   Бинарните файлове са подходящи за съхраняване на комплекси структури (обекти, масиви, изображения и други),
        тъй като те позволяват запазване на точната вътрешна структура на данните.

    *   Трябва да се внимава при преноса на бинарни файлове между различни операционни системи,
        тъй като те могат да имат различни формати на представяне на данните.
*/

constexpr std::size_t kMaxNameSize{ 128 };

struct StaticPerson {
    char firstName[kMaxNameSize]{};
    char lastName[kMaxNameSize]{};
    unsigned age{};
    double weight{};
};

struct DynamicPerson {
    char firstName[kMaxNameSize]{};
    char* lastName{ nullptr };
    unsigned age{};
    double weight{};
};

DynamicPerson createDynamicPerson(const char* firstName, const char* lastName, unsigned age, double weight);

bool writeNumbersToBinaryFile(const char* filename);
bool readNumbersFromBinaryFile(const char* filename);

bool writeStaticPersonObjectToBinaryFile(const StaticPerson& person, const char* filename);
bool readStaticPersonObjectToBinaryFile(StaticPerson& person, const char* filename);

bool writeDynamicPersonObjectToBinaryFile(const DynamicPerson& person, const char* filename);
bool readDynamicPersonObjectToBinaryFile(DynamicPerson& person, const char* filename);

int main() {
    if (!writeNumbersToBinaryFile("data.bin")) {
        return 1;
    }

    if (!readNumbersFromBinaryFile("data.bin")) {
        return 1;
    }

    StaticPerson staticPerson{ "Georgi", "Georgiev", 30, 80.5 };

    if (!writeStaticPersonObjectToBinaryFile(staticPerson, "georgi.bin")) {
        return 1;
    }

    StaticPerson readStaticPerson{};

    if (!readStaticPersonObjectToBinaryFile(readStaticPerson, "georgi.bin")) {
        return 1;
    }

    std::cout << "First name: " << readStaticPerson.firstName << std::endl;
    std::cout << "Last name: " << readStaticPerson.lastName << std::endl;
    std::cout << "Age: " << readStaticPerson.age << std::endl;
    std::cout << "Weight: " << readStaticPerson.weight << std::endl;


    DynamicPerson dynamicPerson{ createDynamicPerson("Ivan", "Ivanov", 25, 75.5) };

    if (!dynamicPerson.lastName) {
        return 1;
    }

    if (!writeDynamicPersonObjectToBinaryFile(dynamicPerson, "ivan.bin")) {
        return 1;
    }

    DynamicPerson readDynamicPerson{};

    if (!readDynamicPersonObjectToBinaryFile(readDynamicPerson, "ivan.bin")) {
        delete[] dynamicPerson.lastName;

        return 1;
    }

    std::cout << "First name: " << readDynamicPerson.firstName << std::endl;
    std::cout << "Last name: " << readDynamicPerson.lastName << std::endl;
    std::cout << "Age: " << readDynamicPerson.age << std::endl;
    std::cout << "Weight: " << readDynamicPerson.weight << std::endl;

    delete[] readDynamicPerson.lastName;
    delete[] dynamicPerson.lastName;

    return 0;
}

DynamicPerson createDynamicPerson(const char* firstName, const char* lastName, unsigned age, double weight) {
    DynamicPerson person;

    strcpy(person.firstName, firstName);

    person.lastName = new (std::nothrow) char[strlen(lastName) + 1];

    if (!person.lastName) {
        std::cout << "Memory allocation error" << std::endl;

        person.lastName = nullptr;

        return person;
    }

    strcpy(person.lastName, lastName);

    person.age = age;
    person.weight = weight;

    return person;
}

bool writeNumbersToBinaryFile(const char* filename) {
    std::ofstream file{ filename, std::ios::binary }; // Отваряме файл за писане в бинарен режим

    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;

        return false;
    }

    for (int i{ 0 }; i < 10; ++i) {
        // Когато записваме променлива в бинарен файл, трябва да кастнем адреса и към char*,
        // за да може да се интерпретира като непрекъсната последователност от байтове
        // Също така трябва да предоставим размера на променливата, която записваме (което са броя байтове, които искаме да запишем)
        file.write(reinterpret_cast<const char*>(&i), sizeof(i));
    }

    file.close();

    return true;
}

bool readNumbersFromBinaryFile(const char* filename) {
    std::ifstream file{ filename, std::ios::binary }; // Отваряме файл за четене в бинарен режим

    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;

        return false;
    }

    int number{};

    // Когато прочитаме информация за променлива от бинарен файл, трябва да кастнем адреса на променливата към char*,
    // за да може да се интерпретира като непрекъсната последователност от байтове
    // Също така трябва да предоставим размера на променливата, която прочитаме (което са броя байтове, които искаме да прочетем)
    while (file.read(reinterpret_cast<char*>(&number), sizeof(number))) {
        std::cout << number << std::endl;
    }

    file.close();

    return true;
}

bool writeStaticPersonObjectToBinaryFile(const StaticPerson& person, const char* filename) {
    std::ofstream file{ filename, std::ios::binary }; // Отваряме файл за писане в бинарен режим

    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;

        return false;
    }

    file.write(reinterpret_cast<const char*>(&person), sizeof(person));

    return true;
}

bool readStaticPersonObjectToBinaryFile(StaticPerson& person, const char* filename) {
    std::ifstream file{ filename, std::ios::binary }; // Отваряме файл за четене в бинарен режим

    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;

        return false;
    }

    file.read(reinterpret_cast<char*>(&person), sizeof(person));

    return true;
}

bool writeDynamicPersonObjectToBinaryFile(const DynamicPerson& person, const char* filename) {
    std::ofstream file{ filename, std::ios::binary }; // Отваряме файл за писане в бинарен режим

    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;

        return false;
    }

    file.write(reinterpret_cast<const char*>(&person.firstName), sizeof(person.firstName));

    // Тъй като lastName е динамичен масив, трябва да запишем и размера на масива, за да може да го прочетем по-късно
    const std::size_t lastNameSize{ strlen(person.lastName) + 1 };
    file.write(reinterpret_cast<const char*>(&lastNameSize), sizeof(lastNameSize));
    file.write(reinterpret_cast<const char*>(person.lastName), lastNameSize);

    file.write(reinterpret_cast<const char*>(&person.age), sizeof(person.age));
    file.write(reinterpret_cast<const char*>(&person.weight), sizeof(person.weight));

    return true;
}

bool readDynamicPersonObjectToBinaryFile(DynamicPerson& person, const char* filename) {
    std::ifstream file{ filename, std::ios::binary }; // Отваряме файл за четене в бинарен режим

    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;

        return false;
    }

    file.read(reinterpret_cast<char*>(&person.firstName), sizeof(person.firstName));

    std::size_t lastNameSize{};
    file.read(reinterpret_cast<char*>(&lastNameSize), sizeof(lastNameSize));

    if (person.lastName) {
        delete[] person.lastName;
        person.lastName = nullptr;
    }

    person.lastName = new (std::nothrow) char[lastNameSize];

    if (!person.lastName) {
        std::cout << "Memory allocation error" << std::endl;

        return false;
    }

    file.read(reinterpret_cast<char*>(person.lastName), lastNameSize);

    file.read(reinterpret_cast<char*>(&person.age), sizeof(person.age));
    file.read(reinterpret_cast<char*>(&person.weight), sizeof(person.weight));

    return true;
}
