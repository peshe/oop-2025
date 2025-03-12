# ТОВА НЕ СЕ ВКЛЮЧВА В РЕШЕНИЕТО ПРОСТО МИ ОЛЕСНЯВА КОМПИЛАЦИЯТА

# Дефинираме компилатора, който ще използваме
CC=g++

# Опции за компилатора: -Wall (включва предупреждения), --pedantic (стриктно спазване на стандарта)
CFLAGS=-Wall --pedantic

# Основната цел: при изпълнение на `make` по подразбиране ще се изгради `program`
all: main

# Как се създава изпълнимият файл `program` - изисква `program.o`
main: main.o
	$(CC) $(CFLAGS) main.o World.o Weapon.o Character.o -o main

# Как се компилира `program.o` - зависи от сорс и хедър файловете
main.o: main.cpp Character.hpp Character.cpp World.hpp World.cpp Weapon.hpp Weapon.cpp
	$(CC) $(CFLAGS) -c main.cpp Character.cpp World.cpp Weapon.cpp

# Цел за изчистване на компилираните файлове - изпълнява се с `make clean`
clean:
	rm -f main main.o Character.o World.o Weapon.o

# Цел за стартиране на програмата - изпълнява се с `make run`
run: main
	./main
