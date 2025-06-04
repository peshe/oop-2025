#pragma once

#include <iostream>

#include "string_list.h"

class Worker {
private:
	Worker() {
		std::cout << "Created Pesho" << std::endl;
	}
	~Worker() = delete;
	Worker& operator=(const Worker&) = delete;

	static Worker* pesho;


public:
	StringList jobs;

	static Worker *getInstance() {
		if (pesho == nullptr) {
			pesho = new Worker();
		}

		return pesho;
	}

	void doJob(const MyString &job) {
		this->jobs += job;
	}
};

Worker *Worker::pesho = nullptr;
