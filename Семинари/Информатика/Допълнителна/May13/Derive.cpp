#include <cassert>
#include <iostream>
#include <cmath>



// private - само класа
// protected - класа и наследниците
// public - всички


class Shape
{
    float area;

protected:
    Shape() : area(0) {}
    void setArea(float newArea)
    {
        assert(newArea >= 0);
        area = newArea;
    }

public:
    float getArea() const
    {
        return area;
    }
};


struct Square : public Shape
{
    float side;

    Square() 
        : side(0), Shape() {}

    void setSide(float newSide)
    {
        Shape::setArea(newSide*newSide);
        side = newSide;
    }
};


struct Disc : public Shape
{

    float radius;

    Disc() 
        : radius(0), Shape() {}

    void setRadius(float newRadius)
    {
        Shape::setArea(newRadius*newRadius*atan2f(0,-1));
        radius = newRadius;
    }
};


void printArea(const Shape & s)
{
    std::cout << s.getArea() << std::endl;
}

void printManyAreas(const Shape shapes[], size_t n)
{
    for(size_t k = 0; k < n; ++k)
        printArea(shapes[k]);
}


int main()
{
    // Shape a;
    Square s;
    Disc d;

    // a.setArea(3);
    s.setSide(4);
    d.setRadius(5);

    // printArea(s);
    // printArea(d);

    Shape shapes[2] { s, d };
    printManyAreas(shapes, 2);

    Disc discs[2];
    discs[1].setRadius(10);
    printManyAreas(discs, 2);

}
