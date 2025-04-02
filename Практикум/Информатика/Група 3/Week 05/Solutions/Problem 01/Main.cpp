#include <limits>

#include <iostream>


#include "Point.hpp"



double  readValue();
Point   readPoint();



void printDistances(const Point&, const Point&);



int main() {
    Point point1 = readPoint(); // warning: function call has aggregate value [-Waggregate-return]
    Point point2 = readPoint(); // warning: function call has aggregate value [-Waggregate-return]

    point1.printInformation();
    point2.printInformation();

    point1.printStatistics();
    point2.printStatistics();

    printDistances(point1, point2);
    printDistances(point2, point1);

    return 0;
}



double readValue() {
    double number = 0.0;

    while (true) {
        std::cin >> number;

        if (std::cin.fail()) {
            std::cin.clear  ()                                                  ;
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n') ;
        } else {
            return number;
        }
    }
}

Point readPoint() {
    std::cout << "Enter the coordinates of Point: ";

    double temporary1 = readValue();
    double temporary2 = readValue();
    double temporary3 = readValue();

    return Point(temporary1, temporary2, temporary3);

    // warning: function returns an aggregate [-Waggregate-return]
}



void printDistances(const Point& point1, const Point& point2) {
    std::cout << "Euclidean     distance: " << point1.calculateDistance1(point2)    << std::endl;
    std::cout << "Manhattan     distance: " << point1.calculateDistance2(point2)    << std::endl;
    std::cout << "Chebyshev Min distance: " << point1.calculateDistance3(point2)    << std::endl;
    std::cout << "Chebyshev Max distance: " << point1.calculateDistance4(point2)    << std::endl;
}
