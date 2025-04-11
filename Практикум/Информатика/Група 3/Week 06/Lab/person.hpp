class Person {
public:
  Person();                                   // default constructor
  Person(const char *name, unsigned int age); // constructor with parameters
  Person(const Person &);                     // copy constructor
  Person &operator=(const Person &);          // copy assignment operator
  ~Person();                                  // destructor

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

private:
  void copyName(const char *name);
  void destroyName();

  void copy(const Person &);
  void destroy();

  char *name;
  unsigned int age;
};