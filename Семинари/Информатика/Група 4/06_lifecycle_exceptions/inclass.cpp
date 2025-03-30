#pragma warning (disable : 4996 )

#include <iostream>
#include <cstring>
#include <stdexcept>

class Song {
private:
	char *name;
	char *performer;
	unsigned int duration; // In seconds

public:
	Song(const char *name, const char *performer, unsigned int duration) : name(nullptr), performer(nullptr),
	                                                                       duration(duration) {
		validateString(name);
		validateString(performer);

		this->name = copyString(name);
		this->performer = copyString(performer);
	}

	~Song() {
		delete[] this->name;
		delete[] this->performer;
	}

	Song(const Song &other) {
		this->name = copyString(other.name);
		this->performer = copyString(other.performer);
		this->duration = other.duration;
	}

	Song &operator=(const Song &other) {
		if (this != &other) {
			char *newName = copyString(other.name);
			char *newPerformer = copyString(other.performer);

			delete[] this->name;
			delete[] this->performer;

			this->name = newName;
			this->performer = newPerformer;
			this->duration = other.duration;
		}
		return *this;
	}

private:
	void validateString(const char *str) {
		if (!str || std::strlen(str) == 0) {
			throw std::invalid_argument("Song name/performer cannot be empty!");
		}
	}

	char *copyString(const char *src) {
		if (!src) {
			throw std::invalid_argument("Source string cannot be empty!");
		}

		std::size_t length = std::strlen(src);

		char *dest = new char[length + 1];
		std::strcpy(dest, src);

		return dest;
	}
};

int main() {
	try {
		Song s("One", "", 500);
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
