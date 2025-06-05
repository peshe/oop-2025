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
    virtual ~Shape() {};
    virtual Shape * clone() const = 0;

public:
    float getArea() const
    {
        return area;
    }

    virtual void print() const
    {
        std::cout << "area=" << area << std::endl;
    }
};


struct Square : public Shape
{
    float side;


    Square() 
        : side(0), Shape() 
    {        
    }

    Square(Square const & r)
    {
        setSide(r.side);
    }

    void setSide(float newSide) noexcept
    {
        Shape::setArea(newSide*newSide);
        side = newSide;
    }

    void print() const
    {
        std::cout << "side=" << side << " ";
        Shape::print();
    }

    Square * clone() const override
    {
        return new Square(*this);
    }

};


struct Disc : public Shape
{

    float radius;

    Disc() : radius(0), Shape() {}
    Disc(Disc const & r) 
    {
        // за правилно инициализиране на 
        // Shape::area използваме мутаторът
        // setRadius
        setRadius(r.radius);
    }

    void setRadius(float newRadius) noexcept
    {
        Shape::setArea(newRadius*newRadius*atan2f(0,-1));
        radius = newRadius;
    }

    void print() const
    {
        std::cout << "radius=" << radius;
        Shape::print();
    }

    Disc * clone() const override 
    {
        return new Disc(*this);
    }
};


void print(const Shape & s)
{
    s.print();
}

void printMany(const Shape * s[], size_t n)
{
    for(size_t k = 0; k < n; ++k)
    {
        s[k]->print(); std::cout << std::endl;
    }
}


struct Shapes
{
    Shape ** shapes = 0;
    size_t size = 0;
    size_t capacity = 2;
    Shapes()
    {
        shapes = new Shape*[capacity] {};
    }

    Shapes(const Shapes & r)
    {
        try
        {
            this->shapes = new Shape*[r.capacity] {};

            for(size_t k = 0; k < r.size; ++k)
                shapes[k] = r.shapes[k]->clone();

            size = r.size;
            capacity = r.capacity;
        }
        catch(...)
        {
            for(size_t k = 0; k < r.size; ++k)
                delete shapes[k];

            delete[] shapes;

        }
    }

    Shapes & operator=(const Shapes & r)
    {
        if(&r != this)
        {

            Shape ** newShapes = 0;
            for(size_t k = 0; k < r.size; ++k)
                newShapes[k] = 0;

            try
            {
                
                newShapes = new Shape*[r.capacity] {};
    
                for(size_t k = 0; k < r.size; ++k)
                    newShapes[k] = r.shapes[k]->clone();


                delete[] shapes;
                shapes = newShapes;   
    
                size = r.size;
                capacity = r.capacity;
            }
            catch(...)
            {
                for(size_t k = 0; k < r.size; ++k)
                    delete newShapes[k];
    
                delete[] newShapes;
    
            }


        }
        return *this;
    }

    // Shapes & operator=(Shapes && r) noexcept
    // {
    //     if(&r != this)
    //     {
    //         shapes = r.shapes;
    //         size = r.size;
    //         capacity = r.capacity;

    //         r.shapes = 0;
    //         r.size = 0;
    //         r.capacity = 0;

    //     }
    //     return *this;
    // }


    // Shapes & operator=(const Shapes & r)
    // {
    //     if(&r != this)
    //     {
    //         Shapes tmp = r;
    //         *this = std::move(tmp);   

    //     }
    //     return *this;
    // }


};


int main()
{
    // Shape a;
    Square s;
    Disc d;

    // a.setArea(3);
    s.setSide(4);
    d.setRadius(5);

    s.print(); std::cout << std::endl;
    d.print(); std::cout << std::endl;

    print(s); std::cout << std::endl;
    print(d); std::cout << std::endl;

    Shape * shape = new Disc;
    delete shape;

    Shape * shapes[2];
    shapes[0] = new Disc;
    shapes[1] = new Square;


    Shapes x,y;

    x = y;

}
