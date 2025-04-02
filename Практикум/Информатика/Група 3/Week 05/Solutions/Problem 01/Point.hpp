#ifndef POINT_HEADER_INCLUDED
#define POINT_HEADER_INCLUDED



#include <cmath>

#include <iostream>



#define EPSILON 1e-9



class Point {
public:
    Point();

    Point(double, double, double);


public:
    inline  double  getXCoordinate()    const   { return this->xCoordinate; }
    inline  double  getYCoordinate()    const   { return this->yCoordinate; }
    inline  double  getZCoordinate()    const   { return this->zCoordinate; }


public:
    unsigned int    findPositive()  const;
    unsigned int    findNegative()  const;
    unsigned int    findZeroCrds()  const;


public:
    void printInformation   ()  const;
    void printStatistics    ()  const; 


public:
    double  calculateDistance1(const Point&)    const;
    double  calculateDistance2(const Point&)    const;
    double  calculateDistance3(const Point&)    const;
    double  calculateDistance4(const Point&)    const;


private:
    bool isCoordinateZero   (double)    const;
    bool isCoordinateValid  (double)    const;


private:
    double xCoordinate;
    double yCoordinate;
    double zCoordinate;
};



inline double min(double a, double b, double c) { return std::min(std::min(a, b), c);   }
inline double max(double a, double b, double c) { return std::max(std::max(a, b), c);   }



#endif
