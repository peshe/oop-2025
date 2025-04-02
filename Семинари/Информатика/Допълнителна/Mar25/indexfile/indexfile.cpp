#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>

namespace fmi 
{
    // обърнете внимание на аргумента to
    static void copy(const char * from, char *& to)
    {
        delete[] to;
        to = new char[1+strlen(from)];
        strcpy(to, from);
    }
}


class Student
{
    char * name = nullptr;
    int fn = 0;

public:

    // ще инициализира name с nullptr
    // и fn с 0
    Student() = default;

    Student(const char * name, int fn)
    {
        this->fn = fn;
        fmi::copy(name, this->name);
    }

    Student(const Student & r)
    {
        this->fn = r.fn;
        fmi::copy(r.name, name);
    }

    Student& operator=(const Student & r)
    {
        if(this != &r)
        {
            this->fn = r.fn;
            fmi::copy(r.name, name);
        }
        return *this;
    }

    ~Student()
    {
        delete[] name;
        // не е задължително, но помага при debug
        name = nullptr; 
    }

    void writeTo(std::ostream & os) const
    {
        os << strlen(name) << "," << name << "," << fn << ";";
    }

    void readFrom(std::istream & is)
    {
        static const auto nolimit = std::numeric_limits<std::streamsize>::max();
        size_t len; is >> len; 
        delete[] name; name = new cuar[len+1];
        is.ignore(nolimit,',');
        is.getline(name, nolimit, ',');
        is >> fn;
        // спазваме правилото след четене на стойност от istream текущата
        // позиция да се установява точно след нейното описание
        is.ignore(nolimit, ';');
    }
   
};

struct IdxFile
{

    char * name = nullptr;
    char * idxname = nullptr;

    IdxFile(const char * name)
    {
        this->name = new char[1+strlen(name)];
        strcpy(this->name, name);
        this->idxname = new char[strlen(name) + 5];
        strcpy(idxname, name);
        strcat(idxname, ".idx");
    }

    ~IdxFile()
    {
        delete[] name;
        delete[] idxname;
    }

    void clear()
    {
        std::ofstream data(name, std::ios::trunc);
        std::ofstream idx(idxname, std::ios::trunc);
    }

    void appendStudent(Student const & s)
    {
        std::fstream data(name, std::ios_base::app | std::ios_base::ate);
        std::fstream idx(idxname, std::ios_base::app | std::ios_base::ate | std::ios_base::binary);

        size_t pos = data.tellp();
        
        s.writeTo(data);
        idx.write((char*)&pos, sizeof(size_t));
    
    }

    Student readAt(int n)
    {
        std::ifstream idx(idxname, std::ios::binary);
        idx.seekg(n*sizeof(size_t));
        size_t pos;
        idx.read((char*)&pos, sizeof(size_t));
        std::ifstream data(name, std::ios::binary);
        data.seekg(pos);

        Student result;   
        result.readFrom(data);
        return result;
    }

};

int main()
{
    Student s1("Ivan Ivanov", 1234);
    Student s2("Petar Petrov", 5678);
    Student s3("Georgi Georgiev", 91011);
    
    IdxFile students("students.txt");
    students.clear();
    students.appendStudent(s1);
    students.appendStudent(s2);
    students.appendStudent(s3);

    Student s2a = students.readAt(1);

    if(true)
    {
        Student s2b = s2a;
    }

    Student s2c = Student("Stefan Stefanov", 0007);

    s2a.writeTo(std::cout); std::cout.flush();
}




