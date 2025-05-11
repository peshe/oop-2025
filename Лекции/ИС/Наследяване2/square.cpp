#include "shape.hpp"

#include <iostream>

namespace fmi::oop {

    class Square : public Shape
    {
    public:
        Square(const Point& start, unsigned size)
            : start(start), size(size)
        {}

        virtual double getArea() const override
        {
            return size * size;
        }

        virtual void print() const override
        {
            std::cout << "Info for a square:\n";
            Shape::print();
            std::cout << "Start: " << start << "\n";
            std::cout << "Size: " << size << std::endl;
        }

        virtual Shape* clone() const override
        {
            return new Square(*this);
        }

    private:
        Point start;
        unsigned size;
    };

    class creator :public ShapeCreator
    {
    public:
        creator() : ShapeCreator("square") {}

        virtual Shape* createShape(std::istream& is) const override
        {
            Point p;
            is >> p;
            int s;
            is >> s;
            return new Square(p, s);
        }
    };

    static creator __;
}
