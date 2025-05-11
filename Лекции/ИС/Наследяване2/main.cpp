#include "shape.hpp"
#include "shape_factory.hpp"

#include <iostream>
#include <fstream>

using namespace fmi::oop;

static void print(const Shape& s)
{
    s.print();
    std::cout << "Area: " << s.getArea() << "\n";
}

static void clearShapes(Shape**& picture, int cnt)
{
    for (int i = 0; i < cnt; ++i)
        delete picture[i];
    delete[] picture;
    picture = nullptr;
}

static double totalShapeArea(Shape*const* picture, int cnt)
{
    double sum = 0;
    for (int i = 0; i < cnt; ++i) {
        if (picture[i]) 
            sum += picture[i]->getArea();
    }
    return sum;
}

void polyDemo2()
{
    std::ifstream file("test.txt");
    int s;
    file >> s;

    Shape** picture = new Shape * [s];
    for (int i = 0; i < s; ++i)
        picture[i] = ShapeFactory::getFactory().createShape(file);
    file.close();
    std::cout << totalShapeArea(picture, s) << "\n";

    // Как да си направим копие на масива?
    int i;
    Shape** pictureCopy = new(std::nothrow) Shape* [s];
    if (pictureCopy) {
        try {
            for (i = 0; i < s; ++i) {
                pictureCopy[i] = picture[i] ? picture[i]->clone() : nullptr;
            }
        }
        catch (const std::bad_alloc&) {
            clearShapes(pictureCopy, i);
            std::cout << "Memory problem! All resources are cleared!\n";
        }
        catch (...) {
            clearShapes(pictureCopy, i);
            std::cout << "Unknown problem! All resources are cleared!\n";
        }
    }
    clearShapes(picture, s);

    if (pictureCopy) {
        std::cout << totalShapeArea(pictureCopy, s) << "\n";
        clearShapes(pictureCopy, s);
    }
}


int main()
{
    polyDemo2();
    return 0;
}
