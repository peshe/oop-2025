// #include <climits>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

class String {
  // размер на буфера при въвеждане
  static const unsigned short MAX_INPUT_SIZE{100};

  char *data{nullptr};

  void destroy();
  void assign(const char *value);

public:
  String() = default;
  String(const char *value);
  String(std::istream &file, char delim = '\n');
  String(const String &other);
  String &operator=(const String &other);
  ~String();

  const char *getData() const { return data; }

  void print() const;
};

class Book {
  static inline unsigned short numberOfBooks;

  String name;
  String author;
  unsigned short numberOfPages;
  unsigned short id;

  short shelfIndex{-1}, positionOnShelf{-1};

  void assign(const String &name, const String &author,
              unsigned short numberOfPages);

  void generateID();

public:
  static const unsigned short MAX_NUMBER_OF_BOOKS{500};

  Book() = delete;
  Book(const String &name, const String &author, unsigned short numberOfPages);
  Book(std::istream &file);
  Book(const Book &other);
  Book &operator=(const Book &other);

  const String &getName() const { return name; }
  const String &getAuthor() const { return author; }
  unsigned short getNumberOfPages() const { return numberOfPages; }
  unsigned short getID() const { return id; }
  short getShelfIndex() const { return shelfIndex; }
  short getPositionOnShelf() const { return positionOnShelf; }

  void setName(const String &name) { this->name = name; }
  void setAuthor(const String &author) { this->author = author; }
  void setShelfIndex(short shelfIndex) { this->shelfIndex = shelfIndex; }
  void setPositionOnShelf(short positionOnShelf) {
    this->positionOnShelf = positionOnShelf;
  }

  void print() const;
};

class Shelf {
  unsigned short maxNumberOfPages;

  unsigned short numberOfBooks{0};
  Book *books[Book::MAX_NUMBER_OF_BOOKS];

  short getIndexAtMax(unsigned short maxNumberOfPages) const;

public:
  Shelf() = default;
  Shelf(const Shelf &) = delete;
  Shelf &operator=(const Shelf &) = delete;
  ~Shelf();

  unsigned short getNumberOfPages() const;

  void setMaxNumberOfPages(unsigned short maxNumberOfPages) {
    this->maxNumberOfPages = maxNumberOfPages;
  }

  bool addBook(Book &book);
  Book *searchForBook(const String &name) const;
  bool removeBook(Book &book);
  void resize(unsigned short maxNumberOfPages, Shelf &removedBooks);
};

class Bookshelf {
  const unsigned short numberOfShelves;
  Shelf *shelves;

public:
  Bookshelf(unsigned short numberOfShelves,
            unsigned short maxNumberOfPagesPerShelf);
  Bookshelf(const Bookshelf &) = delete;
  Bookshelf &operator=(const Bookshelf &) = delete;
  ~Bookshelf();

  bool addBook(Book &book);
  Book *searchForBook(const String &name) const;
  bool removeBook(Book &book);
  void resizeShelves(unsigned short maxNumberOfPagesPerShelf,
                     Shelf &removedBooks);
};

void assertIsNonEmpty(const char *value) {
  if (value == nullptr)
    throw "стойността на низа не може да е null";

  if (*value == '\0')
    throw "стойността на низа не може да е празна";
}

void String::destroy() {
  delete[] data;
  data = nullptr;
}

void String::assign(const char *value) {
  assertIsNonEmpty(value);

  destroy();

  size_t len{strlen(value) + 1};
  data = new char[len];
  strncpy(data, value, len);
}

String::String(const char *value) { assign(value); }

void handleInputErrors(const std::istream &input) {
  if (input.bad())
    throw "критична грешка при четене/въвеждане";

  if (!input)
    throw "опит за четене/въвеждане на невалидна или прекалено голяма стойност";
}

String::String(std::istream &file, char delim)
    : data{new char[MAX_INPUT_SIZE]} {
  file.getline(data, MAX_INPUT_SIZE, delim);
  handleInputErrors(file);
}

String::String(const String &other) : String{other.data} {}

String &String::operator=(const String &other) {
  if (&other != this) {
    assign(other.data);
  }
  return *this;
}

String::~String() { destroy(); }

void String::print() const {
  if (data != nullptr)
    std::cout << data;
}

void Book::assign(const String &name, const String &author,
                  unsigned short numberOfPages) {
  setName(name);
  setAuthor(author);
  this->numberOfPages = numberOfPages;
}

void Book::generateID() {
  if (++numberOfBooks > MAX_NUMBER_OF_BOOKS)
    throw "опит за създаване на повече книги от максималния позволен брой";

  id = numberOfBooks;
}

Book::Book(const String &name, const String &author,
           unsigned short numberOfPages) {
  assign(name, author, numberOfPages);
  generateID();
}

Book::Book(std::istream &file) : name{file, ','}, author{file, ','} {
  file >> numberOfPages;
  handleInputErrors(file);

  file.ignore();

  generateID();
}

Book::Book(const Book &other)
    : Book{other.name, other.author, other.numberOfPages} {}

Book &Book::operator=(const Book &other) {
  if (&other != this) {
    assign(other.name, other.author, other.numberOfPages);
  }
  return *this;
}

void Book::print() const {
  std::cout << "Име на книгата: ";
  name.print();
  std::cout << std::endl;
  std::cout << "Автор на книгата: ";
  author.print();
  std::cout << std::endl;
  std::cout << "Брой страници в книгата: " << numberOfPages << std::endl;
  std::cout << "Идентификатор на книгата: IS-INF-" << std::setfill('0')
            << std::setw(4) << id << std::endl;
  if (shelfIndex >= 0 && positionOnShelf >= 0) {
    std::cout << "Номер на рафт в библиотеката, на който се намира книгата: "
              << shelfIndex + 1 << std::endl;
    std::cout << "Позиция на книгата на съответния рафт в библиотеката: "
              << positionOnShelf + 1 << std::endl;
  }
  std::cout << std::endl;
}

short Shelf::getIndexAtMax(unsigned short maxNumberOfPages) const {
  unsigned short numberOfPages{0};
  for (unsigned short i{0}; i < numberOfBooks; i++) {
    numberOfPages += books[i]->getNumberOfPages();
    if (numberOfPages > maxNumberOfPages) {
      return i;
    }
  }

  return -1;
}

Shelf::~Shelf() {
  for (unsigned short i{0}; i < numberOfBooks; i++) {
    delete books[i];
  }
}

unsigned short Shelf::getNumberOfPages() const {
  unsigned short numberOfPages{0};
  for (unsigned short i{0}; i < numberOfBooks; i++) {
    numberOfPages += books[i]->getNumberOfPages();
  }
  return numberOfPages;
}

bool Shelf::addBook(Book &book) {
  unsigned short numberOfPages{getNumberOfPages()};
  numberOfPages += book.getNumberOfPages();
  if (numberOfPages > maxNumberOfPages)
    return false;

  book.setPositionOnShelf(numberOfBooks);
  books[numberOfBooks++] = &book;
  return true;
}

Book *Shelf::searchForBook(const String &name) const {
  for (unsigned short i{0}; i < numberOfBooks; i++) {
    const char *bookName{books[i]->getName().getData()};
    if (strncmp(bookName, name.getData(), strlen(bookName)) == 0)
      return books[i];
  }

  return nullptr;
}

bool Shelf::removeBook(Book &book) {
  for (unsigned short i{0}; i < numberOfBooks; i++) {
    if (books[i] == &book) {
      book.setPositionOnShelf(-1);
      unsigned short j;
      for (j = i + 1; j < numberOfBooks; j++)
        books[j - 1] = books[j];
      books[j - 1] = nullptr;
      numberOfBooks--;
      return true;
    }
  }

  return false;
}

void Shelf::resize(unsigned short maxNumberOfPages, Shelf &removedBooks) {
  short indexAtMax{getIndexAtMax(maxNumberOfPages)};
  if (indexAtMax >= 0) {
    for (short i{indexAtMax}; i < numberOfBooks; i++) {
      removedBooks.addBook(*books[i]);
      books[i]->setPositionOnShelf(-1);
      books[i]->setShelfIndex(-1);
      books[i] = nullptr;
    }
    numberOfBooks = indexAtMax;
  }

  this->maxNumberOfPages = maxNumberOfPages;
}

Bookshelf::Bookshelf(unsigned short numberOfShelves,
                     unsigned short maxNumberOfPagesPerShelf)
    : numberOfShelves{numberOfShelves}, shelves{new Shelf[numberOfShelves]} {
  for (unsigned short i{0}; i < numberOfShelves; i++)
    shelves[i].setMaxNumberOfPages(maxNumberOfPagesPerShelf);
}

Bookshelf::~Bookshelf() { delete[] shelves; }

bool Bookshelf::addBook(Book &book) {
  for (unsigned short i{0}; i < numberOfShelves; i++)
    if (shelves[i].addBook(book)) {
      book.setShelfIndex(i);
      return true;
    }

  return false;
}

Book *Bookshelf::searchForBook(const String &name) const {
  for (unsigned short i{0}; i < numberOfShelves; i++) {
    Book *book{shelves[i].searchForBook(name)};
    if (book != nullptr)
      return book;
  }

  return nullptr;
}

bool Bookshelf::removeBook(Book &book) {
  for (unsigned short i{0}; i < numberOfShelves; i++) {
    if (shelves[i].removeBook(book)) {
      book.setShelfIndex(-1);
      return true;
    }
  }

  return false;
}

void Bookshelf::resizeShelves(unsigned short maxNumberOfPagesPerShelf,
                              Shelf &removedBooks) {
  for (unsigned short i{0}; i < numberOfShelves; i++)
    shelves[i].resize(maxNumberOfPagesPerShelf, removedBooks);
}

int main() {
  try {
    unsigned short n;
    std::cout << "Въведете броя рафтове на библиотеката: ";
    std::cin >> n;
    handleInputErrors(std::cin);
    std::cin.ignore();

    unsigned short m;
    std::cout
        << "Въведете максималния брой страници на всеки рафт на библиотеката: ";
    std::cin >> m;
    handleInputErrors(std::cin);
    std::cin.ignore();

    Bookshelf bookshelf{n, m};

    std::cout << "Въведете име на файл, откъдето да се прочете съдържанието на "
                 "библиотеката: ";
    String filename{std::cin};
    std::ifstream file{filename.getData()};
    if (!file.is_open())
      throw "неуспешен опит за отваряне на файла със съдържанието на "
            "библиотеката";

    std::cout << std::endl;

    while (!file.eof()) {
      Book *book{new Book{file}};
      if (!bookshelf.addBook(*book)) {
        book->print();
        delete book;
      }
    }

    Book *rana{bookshelf.searchForBook("Рана")};
    if (rana == nullptr) {
      std::cout << "Книгата \"Рана\" НЕ е в библиотеката." << std::endl;
    } else {
      std::cout << "Книгата \"Рана\" е в библиотеката." << std::endl;
      bookshelf.removeBook(*rana);
      delete rana;
    }

    // Shelf removedBooks;
    // removedBooks.setMaxNumberOfPages(UINT_MAX);
    // bookshelf.resizeShelves(maxNumberOfPagesPerShelf, removedBooks);
  } catch (const char *error) {
    std::cerr << "грешка: " << error << std::endl;
  }

  return 0;
}
