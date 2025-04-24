class Person {
public:
  friend class Family;
  friend const Person *getGreatGrandmother(const Person &p);

  Person() = delete;
  Person(Person *mother, Person *father);
  Person(const char *name, unsigned int age, Person *mother = nullptr,
         Person *father = nullptr);            // constructor with parameters
  Person(const Person &) = default;            // copy constructor
  Person &operator=(const Person &) = default; // copy assignment operator
  ~Person() = default;                         // destructor

  const char *getName() const;
  void setName(const char *name);
  void printName() const;
  void readName();

  unsigned int getAge() const;
  void setAge(unsigned int age);
  void printAge() const;
  void readAge();

  void assign(const char *name, unsigned int age);
  void print() const;
  void read();

  static unsigned int getNumberOfPeople();

  static inline const char *const species{"Homo sapiens"};

private:
  static inline const unsigned int MAX_NAME_SIZE{100};

  static inline unsigned int numberOfPeople;

  char name[MAX_NAME_SIZE];
  unsigned int age;

  Person *mother;
  Person *father;
};