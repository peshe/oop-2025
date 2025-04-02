#include "Point.hpp"



Point::Point() {
    this->xCoordinate   =   0.0;
    this->yCoordinate   =   0.0;
    this->zCoordinate   =   0.0;
}

Point::Point(double x, double y, double z) {
    if (
        this->isCoordinateValid(x) == false ||
        this->isCoordinateValid(y) == false ||
        this->isCoordinateValid(z) == false
    ) {
        std::cout << "Building Point... ERROR!" << std::endl;

        return;
    }

    this->xCoordinate   =   x;
    this->yCoordinate   =   y;
    this->zCoordinate   =   z;
}



unsigned int Point::findPositive()  const   { return (this->xCoordinate > 0.0) + (this->yCoordinate > 0.0) + (this->zCoordinate > 0.0); }
unsigned int Point::findNegative()  const   { return (this->xCoordinate < 0.0) + (this->yCoordinate < 0.0) + (this->zCoordinate < 0.0); }
unsigned int Point::findZeroCrds()  const   {
    return
        this->isCoordinateZero(this->xCoordinate)   +
        this->isCoordinateZero(this->yCoordinate)   +
        this->isCoordinateZero(this->zCoordinate);
}



double Point::calculateDistance1(const Point& instance) const {
    return std::sqrt(
        std::pow(this->xCoordinate - instance.xCoordinate, 2) +
        std::pow(this->yCoordinate - instance.yCoordinate, 2) +
        std::pow(this->zCoordinate - instance.zCoordinate, 2)
    );
}

double Point::calculateDistance2(const Point& instance) const {
    return
        std::fabs(this->xCoordinate - instance.xCoordinate) +
        std::fabs(this->yCoordinate - instance.yCoordinate) +
        std::fabs(this->zCoordinate - instance.zCoordinate);
}

double Point::calculateDistance3(const Point& instance) const {
    return min(
        std::fabs(this->xCoordinate - instance.xCoordinate),
        std::fabs(this->yCoordinate - instance.yCoordinate),
        std::fabs(this->zCoordinate - instance.zCoordinate)
    );
}

double Point::calculateDistance4(const Point& instance) const {
    return max(
        std::fabs(this->xCoordinate - instance.xCoordinate),
        std::fabs(this->yCoordinate - instance.yCoordinate),
        std::fabs(this->zCoordinate - instance.zCoordinate)
    );
}



void Point::printInformation() const {
    std::cout << "Point Information: " << std::endl;

    std::cout << "( ";
 
    std::cout << "X: " << this->xCoordinate << "; ";
    std::cout << "Y: " << this->yCoordinate << "; ";
    std::cout << "Z: " << this->zCoordinate << "; ";

    std::cout << " )";

    std::cout << std::endl;

    std::cout << std::endl;
}

void Point::printStatistics() const {
    std::cout << "Point Statistics: " << std::endl;

    std::cout << "Number of positive    coordinates: " << this->findPositive()  << std::endl;
    std::cout << "Number of negative    coordinates: " << this->findNegative()  << std::endl;
    std::cout << "Number of zero        coordinates: " << this->findZeroCrds()  << std::endl;

    std::cout << std::endl;
}



bool Point::isCoordinateZero(double coordinate) const {
    return std::fabs(coordinate) < EPSILON;
}

bool Point::isCoordinateValid(double coordinate) const {
    return
        std::isnan(coordinate) == false &&
        std::isinf(coordinate) == false;
}
