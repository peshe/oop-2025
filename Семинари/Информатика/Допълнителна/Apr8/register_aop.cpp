#include <iostream>
#include <sstream>
#include <cstring>
#include <cassert>


// Малък регистър в община - регистрира хора и бракове.


// static, за да е невидима от другите файлове
static void allocCopy(const char * from, char *& to)
{
    delete[] to; to = new char[1+strlen(from)]; strcpy(to,from);
}

class Person 
{
    char * family = 0;
    int id = 0;
public:
    Person() {};
    Person(const char * familyName, int id)
    : id(id)
    {
        allocCopy(familyName, family);
    }


    ~Person()
    {
        delete[] family;
    }

    // Хаджилък
    void hadj()
    {
        const char * prefix = "Хаджи";
        char * newFamily = new char[strlen(prefix)+strlen(family)+1];
        strcpy(newFamily, prefix);
        strcat(newFamily, family);
        delete[] family;
        family = newFamily;
    }

    const char * getFamily() const
    {
        return family;
    }

    int getId() const
    {
        return id;
    }

    void appendFamily(const char * suffix)
    {
        const char * mid = " - ";
        char * newFamily = new char[strlen(family) + strlen(mid) + strlen(suffix)+1];
        strcpy(newFamily, family);
        strcat(newFamily, mid);
        strcat(newFamily, suffix);
        delete[] family;
        family = newFamily;
    }

    // сериализация
    void print() const
    {
        std::cout << family << " " << id;
    }

    // десериализация от същия формат
    void read(std::istream & is)
    {
        if(!is)
            return;

        // ще определим дължината на низа 
        // четейки фйала
        int curPos = is.tellg();
        while(is.peek() != ' ') is.get();
        if(!is)
            return;

        int newPos = is.tellg();
        int allocSize = newPos - curPos + 1;
        delete[] family; family = new char[allocSize];
        is.seekg(curPos);
        is >> family;
        is >> id;
        
    }

};

class Marriage 
{
    Person *persons[2];
    public:
    Marriage(Person * p1, Person * p2)
    {
        persons[0] = p1; persons[1] = p2;
    }

    // в деструктора не освобождаваме памет
    // доколкото указателите сочат към хора
    // в регистъра за хора
    // .. а и края на брака не значи смърт за
    // участниците
    ~Marriage()
    {

    }

    void print()
    {
        persons[0]->print(); std::cout << " "; persons[1]->print();
    }

    Person * getPerson(int n) 
    {
        assert(0<=n && n < 2);
        if(0 <= n && n < 2) return persons[n];
        return nullptr;
    }
};


class Register
{

    // Използваме масиви от указатели към динамично
    // заделени обекти. По този начин те са фиксирани 
    // в паметта и указателите в Marriagе ще са валидни
    Person ** persons = 0;
    Marriage ** marriages = 0;
    int capacity = 0;
    int numPersons = 0;
    int capacitym = 0;
    int numMarriages = 0;

public:
    Register()
    {
        capacity = 5;
        persons = new Person*[5];
        capacitym = 5;
        marriages = new Marriage*[5];
    }

    ~Register()
    {
        for(int k = 0; k < numPersons; ++k)
            delete persons[k];

        delete[] persons;

        for(int k = 0; k < numMarriages; ++k)
            delete marriages[k];

        delete[] marriages;
    }

    void addPerson(const char * family, int id)
    {
        if(numPersons == capacity)
        {
            int newCapacity = 3*capacity/2;
            Person ** newPersons = new Person*[newCapacity];
            capacity = newCapacity;
            for(int k = 0; k < numPersons; ++k)
                newPersons[k] = persons[k];
            
            delete[] persons;
            persons = newPersons;
        }
        persons[numPersons] = new Person(family, id);
        numPersons++;
    }

    Person * findPerson(int id)
    {
        for(int k = 0; k<numPersons; ++k)
            if(id == persons[k]->getId())
                return persons[k];

        return nullptr;        
    }

    void deletePerson(int id)
    {
        for(int k = 0; k<numPersons; ++k)
        {
            if(id == persons[k]->getId())
            {
                
                deleteMarriage(persons[k]);
                delete persons[k];
                
                for(int l = k; l < numPersons - 1; ++l)
                {
                    persons[l] = persons[l+1];
                }
                numPersons = numPersons - 1;
            }
        }
    }

    void hadj(int id)
    {
        Person * p = findPerson(id);
        if(p) p->hadj();
    }

    void marry(int id1, int id2)
    {
        Person * p1 = findPerson(id1);
        Person * p2 = findPerson(id2);

        if(!p1) return;
        if(!p2) return;

        char * oldFamily1 = 0;
        char * oldFamily2 = 0;
        allocCopy(p1->getFamily(), oldFamily1);
        allocCopy(p2->getFamily(), oldFamily2);

        p1->appendFamily(oldFamily2);
        p2->appendFamily(oldFamily1);

        delete[] oldFamily1;
        delete[] oldFamily2;
    

        if(numMarriages == capacitym)
        {
            capacitym = capacitym*3/2;
            Marriage ** newMarriages = new Marriage* [capacitym];
            for(int k = 0; k < numMarriages; ++k)
                newMarriages[k] = marriages[k];        
        }

        marriages[numMarriages] = new Marriage(p1,p2);
        numMarriages++;
 
    }

    void printPersons()
    {
        for(int k = 0; k < numPersons; ++k)
        {
            persons[k]->print();
            std::cout << std::endl;
        }
    }

    void printMarriages()
    {
        for(int k = 0; k < numMarriages; ++k)
        {
            marriages[k]->print();
            std::cout << std::endl;
        }
    }

 private:
    void deleteMarriage(Person * p)
    {
        for(int k = 0; k < numMarriages; ++k)
        {
            if(p == marriages[k]->getPerson(0) || p == marriages[k]->getPerson(1))
            {
                delete marriages[k];
                for(int l = k; l < numMarriages-1; ++l)
                {
                    marriages[l] = marriages[l+1];
                }
                numMarriages--;
            }
        }
    }   

};

int main()
{
    Person p;
    std::istringstream iss("Ivan 100");
    p.read(iss);
    
  
    Register r;
    r.addPerson("Иванов", 1);
    r.addPerson("Петров", 2);
    r.addPerson("Петров", 3);

    r.addPerson("Гемеджиев",40);
    r.addPerson("Георгиев",50);
    r.addPerson("Георгиева",60);
    r.addPerson("Герасимов",70);
    r.addPerson("Гоцев",80);
    r.addPerson("Гошев",90);
    r.addPerson("Григориев",100);
    r.addPerson("Григоров",110);
    r.addPerson("Грозданов",120);

    r.printPersons();

    r.deletePerson(90);

    r.printPersons();

    r.hadj(80);

    r.printPersons();

    r.marry(80,110);

    r.printMarriages();

    r.printPersons();

    r.deletePerson(110);
    
   
    r.printMarriages();
    r.printPersons();

}