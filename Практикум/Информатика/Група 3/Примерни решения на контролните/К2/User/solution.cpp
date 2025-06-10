#include <cstddef>
#include <cstring>
#include <iostream>

class String {
  static const unsigned int MAX_INPUT_SIZE{100};

  char *data{nullptr};

  void destroy();
  void assign(const char *value);

public:
  String();
  String(const String &other);
  String &operator=(const String &other);
  ~String();

  const char *getData() const { return data; }

  bool contains(char c) const;

  friend std::istream &operator>>(std::istream &is, String &s);
};

void assertIsNonEmpty(const char *s) {
  if (!s)
    throw "string may not be null";

  if (*s != '\0')
    throw "string may not be empty";
}

void String::destroy() { delete[] data; }

void String::assign(const char *value) {
  assertIsNonEmpty(value);

  destroy();

  size_t len{strlen(value) + 1};
  data = new char[len];
  strncpy(data, value, len);
}

String::String() : data{new char[1]} { *data = '\0'; }

String::String(const String &other) { assign(other.data); }

String &String::operator=(const String &other) {
  if (&other != this) {
    assign(other.data);
  }

  return *this;
}

String::~String() { destroy(); }

bool String::contains(char c) const {
  char *it{data};
  while (*it != '\0' && *it != c)
    it++;

  return *it == c;
}

std::ostream &operator<<(std::ostream &os, const String &s) {
  return os << s.getData();
}

void handleInputErrors(const std::istream &is) {
  if (is.bad())
    throw "critical error during input";

  if (!is)
    throw "attempted to input invalid value or value is too big";
}

std::istream &operator>>(std::istream &is, String &s) {
  s.destroy();

  s.data = new char[String::MAX_INPUT_SIZE];
  is.getline(s.data, String::MAX_INPUT_SIZE, ' ');
  handleInputErrors(is);

  return is;
}

bool operator==(const String &lhs, const String &rhs) {
  return strcmp(lhs.getData(), rhs.getData()) != 0;
}

class User {
protected:
  String email;
  String password;

public:
  User() = default;
  User(const String &email, const String &password);
  User(std::istream &is);

  const String &getEmail() const { return email; }
  const String &getPassword() const { return password; }

  void setPassword(const String &password);

  friend std::istream &operator>>(std::istream &os, User &user);
};

User::User(const String &email, const String &password)
    : email{email}, password{password} {
  if (!email.contains('@'))
    throw "invalid user email: it should contain '@'";
}

User::User(std::istream &is) { is >> *this; }

void User::setPassword(const String &password) { this->password = password; }

std::ostream &operator<<(std::ostream &os, const User &user) {
  os << "Email: " << user.getEmail() << std::endl;
  os << "Password: " << user.getPassword() << std::endl;
  return os;
}

std::istream &operator>>(std::istream &is, User &user) {
  is >> user.email;
  handleInputErrors(is);

  is >> user.password;
  handleInputErrors(is);

  return is;
}

bool operator==(const User &lhs, const User &rhs) {
  return lhs.getEmail() == rhs.getEmail();
}

class Admin : public User {
protected:
  unsigned int yearsOfExperience;
  unsigned int levelOfQualification;

public:
  Admin() = default;
  Admin(const String &email, const String &password,
        unsigned int yearsOfExperience, unsigned int levelOfQualification);
  Admin(std::istream &is);

  unsigned int getYearsOfExperience() const { return yearsOfExperience; }
  unsigned int getLevelOfQualification() const { return levelOfQualification; }

  void setYearsOfExperience(unsigned int yearsOfExperience);
  void setLevelOfQualification(unsigned int levelOfQualification);

  Admin &operator++();
  Admin operator++(int);
  Admin &operator--();
  Admin operator--(int);

  friend std::istream &operator>>(std::istream &is, Admin &admin);
};

Admin::Admin(const String &email, const String &password,
             unsigned int yearsOfExperience, unsigned int levelOfQualification)
    : User{email, password}, yearsOfExperience{yearsOfExperience},
      levelOfQualification{levelOfQualification} {
  if (levelOfQualification < 1 || levelOfQualification > 5)
    throw "invalid admin level of qualification: should be between 1 and 5";
}

Admin::Admin(std::istream &is) { is >> *this; }

void Admin::setYearsOfExperience(unsigned int yearsOfExperience) {
  this->yearsOfExperience = yearsOfExperience;
}

void Admin::setLevelOfQualification(unsigned int levelOfQualification) {
  this->levelOfQualification = levelOfQualification;
}

Admin &Admin::operator++() {
  levelOfQualification++;
  return *this;
}

Admin Admin::operator++(int) { return Admin::operator++(); }

Admin &Admin::operator--() {
  levelOfQualification--;
  return *this;
}

Admin Admin::operator--(int) { return Admin::operator--(); }

std::ostream &operator<<(std::ostream &os, const Admin &admin) {
  operator<<(os, (const User &)admin);
  os << "Years of experience: " << admin.getYearsOfExperience() << std::endl;
  os << "Level of qualification: " << admin.getLevelOfQualification()
     << std::endl;
  return os;
}

std::istream &operator>>(std::istream &is, Admin &admin) {
  operator>>(is, (User &)admin);

  is >> admin.yearsOfExperience;
  handleInputErrors(is);
  is.ignore();

  is >> admin.levelOfQualification;
  handleInputErrors(is);
  is.ignore();

  return is;
}

bool operator<(const Admin &lhs, const Admin &rhs) {
  return lhs.getLevelOfQualification() < rhs.getLevelOfQualification() ||
         lhs.getLevelOfQualification() == rhs.getLevelOfQualification() &&
             lhs.getYearsOfExperience() < rhs.getYearsOfExperience();
}

bool operator>(const Admin &lhs, const Admin &rhs) {
  return lhs.getLevelOfQualification() > rhs.getLevelOfQualification() ||
         lhs.getLevelOfQualification() == rhs.getLevelOfQualification() &&
             lhs.getYearsOfExperience() > rhs.getYearsOfExperience();
}

class System;

class SuperUser : public Admin {
  size_t numOfUsersCreatedBySelf{0}, capacityOfUsersCreatedBySelf{0};
  String *namesOfUsersCreatedBySelf{nullptr};

  System &system;

  void destroyNames();
  void assign(String *usernames, size_t n);
  void assignNames(const SuperUser &superUser);

public:
  SuperUser() = delete;
  SuperUser(const String &email, const String &password,
            unsigned int yearsOfExperience, unsigned int levelOfQualification,
            System &system);
  SuperUser(std::istream &is);
  SuperUser(const SuperUser &other);
  SuperUser &operator=(const SuperUser &other) = delete;
  ~SuperUser();

  void operator()(const String &email, const String &password);

  bool operator[](const String &email);

  friend std::ostream &operator<<(std::ostream &os, const SuperUser &superUser);
  friend std::istream &operator>>(std::istream &is, SuperUser &superUser);
};

void SuperUser::destroyNames() { delete[] namesOfUsersCreatedBySelf; }

void SuperUser::assignNames(const SuperUser &other) {
  destroyNames();

  capacityOfUsersCreatedBySelf = other.capacityOfUsersCreatedBySelf;
  numOfUsersCreatedBySelf = other.numOfUsersCreatedBySelf;
  namesOfUsersCreatedBySelf = new String[other.capacityOfUsersCreatedBySelf];
  for (size_t i{0}; i < other.numOfUsersCreatedBySelf; i++)
    namesOfUsersCreatedBySelf[i] = other.namesOfUsersCreatedBySelf[i];
}

SuperUser::SuperUser(const String &email, const String &password,
                     unsigned int yearsOfExperience,
                     unsigned int levelOfQualification, System &system)
    : Admin{email, password, yearsOfExperience, levelOfQualification},
      capacityOfUsersCreatedBySelf{1}, namesOfUsersCreatedBySelf{new String[1]},
      system{system} {}

SuperUser::SuperUser(const SuperUser &other)
    : Admin{other.email, other.password, other.yearsOfExperience,
            other.levelOfQualification},
      system{other.system} {
  assignNames(other);
}

SuperUser::~SuperUser() { destroyNames(); }

bool SuperUser::operator[](const String &username) {
  for (size_t i{0}; i < numOfUsersCreatedBySelf; i++)
    if (namesOfUsersCreatedBySelf[i] == username)
      return true;

  return false;
}

std::ostream &operator<<(std::ostream &os, const SuperUser &superUser) {
  operator<<(os, (const Admin &)superUser);
  for (size_t i{0}; i < superUser.numOfUsersCreatedBySelf; i++)
    os << superUser.namesOfUsersCreatedBySelf[i] << std::endl;
  return os;
}

std::istream &operator>>(std::istream &is, SuperUser &superUser) {
  operator>>(is, (Admin &)superUser);

  is >> superUser.numOfUsersCreatedBySelf;
  handleInputErrors(is);
  is.ignore();

  for (size_t i{0}; i < superUser.numOfUsersCreatedBySelf; i++) {
    is >> superUser.namesOfUsersCreatedBySelf[i];
    handleInputErrors(is);
    is.ignore();
  }

  return is;
}

class System {
  String name;

  size_t numOfUsers{0}, capacityOfUsers{0};
  User **users{nullptr};
  size_t numOfAdmins{0}, capacityOfAdmins{1};
  Admin **admins;

  SuperUser *superUser{nullptr};

  bool contains(const String &username);

public:
  System() = delete;
  System(const String &name, SuperUser *superUser = nullptr);
  System(const System &other);
  System &operator=(const System &other) = delete;
  ~System();

  const String &getName() const { return name; }
  const User *getUserByEmail(const String &email) const;
  const Admin *getAdminByEmail(const String &email) const;
  const SuperUser *getSuperUser() const { return superUser; }

  bool operator+=(User &user);
  bool addAdmin(Admin &user);

  bool operator-=(User &user);

  const Admin *operator^(unsigned int minLevelOfQualification);
};

void SuperUser::operator()(const String &email, const String &password) {
  if (numOfUsersCreatedBySelf == capacityOfUsersCreatedBySelf) {
    capacityOfUsersCreatedBySelf *= 2;
    String *reallocUsernames = new String[capacityOfUsersCreatedBySelf];
    for (size_t i{0}; i < numOfUsersCreatedBySelf; i++)
      reallocUsernames[i] = this->namesOfUsersCreatedBySelf[i];
    delete[] namesOfUsersCreatedBySelf;
    namesOfUsersCreatedBySelf = reallocUsernames;
  }

  namesOfUsersCreatedBySelf[numOfUsersCreatedBySelf++] = email;
  system += *new User{email, password};
}

System::System(const String &name, SuperUser *superUser)
    : name{name}, capacityOfUsers{1}, users{new User *[1]}, capacityOfAdmins{1},
      admins{new Admin *[1]}, superUser{superUser} {}

System::System(const System &other)
    : name{other.name}, superUser{other.superUser} {
  capacityOfUsers = other.capacityOfUsers;
  numOfUsers = other.numOfUsers;
  users = new User *[other.capacityOfUsers];
  for (size_t i{0}; i < other.numOfUsers; i++)
    users[i] = other.users[i];

  capacityOfAdmins = other.capacityOfAdmins;
  numOfAdmins = other.numOfAdmins;
  admins = new Admin *[other.capacityOfAdmins];
  for (size_t i{0}; i < other.numOfAdmins; i++)
    admins[i] = other.admins[i];
}

System::~System() {
  for (size_t i{0}; i < numOfUsers; i++)
    delete users[i];
  delete[] users;

  for (size_t i{0}; i < numOfAdmins; i++)
    delete admins[i];
  delete[] admins;

  delete superUser;
}

const User *System::getUserByEmail(const String &email) const {
  for (size_t i{0}; i < numOfUsers; i++)
    if (users[i]->getEmail() == email)
      return users[i];

  return nullptr;
}

const Admin *System::getAdminByEmail(const String &email) const {
  for (size_t i{0}; i < numOfAdmins; i++)
    if (admins[i]->getEmail() == email)
      return admins[i];

  return nullptr;
}

bool System::operator+=(User &user) {
  if (getUserByEmail(user.getEmail()) != nullptr)
    return false;

  if (numOfUsers == capacityOfUsers) {
    capacityOfUsers *= 2;
    User **reallocUsers = new User *[capacityOfUsers];
    for (size_t i{0}; i < numOfUsers; i++)
      reallocUsers[i] = this->users[i];
    delete[] users;
    users = reallocUsers;
  }

  users[numOfUsers++] = &user;
  return true;
}

bool System::addAdmin(Admin &admin) {
  if (getAdminByEmail(admin.getEmail()) != nullptr)
    return false;

  if (getUserByEmail(admin.getEmail()) != nullptr)
    return false;

  if (numOfAdmins == capacityOfAdmins) {
    capacityOfAdmins *= 2;
    Admin **reallocAdmins = new Admin *[capacityOfAdmins];
    for (size_t i{0}; i < numOfAdmins; i++)
      reallocAdmins[i] = this->admins[i];
    delete[] admins;
    admins = reallocAdmins;
  }

  admins[numOfAdmins++] = &admin;
  return true;
}

bool System::operator-=(User &user) {
  size_t i;

  for (i = 0; i < numOfAdmins; i++) {
    if (admins[i] == (Admin *)&user)
      break;
  }

  if (i < numOfAdmins) {
    if (numOfAdmins == 1)
      return false;

    delete admins[i];
    for (; i < numOfAdmins - 1; i++)
      admins[i] = admins[i + 1];
    return true;
  }

  for (i = 0; i < numOfUsers; i++) {
    if (users[i] == &user)
      break;
  }

  if (i < numOfUsers) {
    delete users[i];
    for (; i < numOfUsers - 1; i++)
      users[i] = users[i + 1];
    return true;
  }

  return false;
}

const Admin *System::operator^(unsigned int minLevelOfQualification) {
  const Admin *leastAdmin{nullptr};
  for (size_t i{0}; i < numOfAdmins; i++)
    if (admins[i]->getLevelOfQualification() >= minLevelOfQualification) {
      if (leastAdmin == nullptr ||
          leastAdmin != nullptr && *admins[i] < *leastAdmin) {
        leastAdmin = admins[i];
      }
    }

  return leastAdmin;
}

int main()
{
  SuperUser* superUser{};
  System system;

  return 0;
}
