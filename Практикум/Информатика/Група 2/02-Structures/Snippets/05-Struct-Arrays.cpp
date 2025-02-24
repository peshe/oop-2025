#include <iostream>

constexpr std::size_t kArraySize = 10;

struct Point {
    int x{};
    int y{};
};

void initPoint(Point& point, std::size_t index);
void printPoint(const Point& point);

int main() {
    Point points[kArraySize]{};

    for (std::size_t i = 0; i < kArraySize; ++i) {
        initPoint(points[i], i);
    }

    for (const auto& point : points) {
        printPoint(point);
    }

    Point* dynamicPoints = new (std::nothrow) Point[kArraySize];

    if (dynamicPoints == nullptr) {
        std::cout << "Failed to allocate memory for dynamicPoints" << std::endl;

        return 1;
    }

    for (std::size_t i = 0; i < kArraySize; ++i) {
        initPoint(dynamicPoints[i], i);
    }

    for (std::size_t i = 0; i < kArraySize; ++i) {
        printPoint(dynamicPoints[i]);
    }

    delete[] dynamicPoints;
    dynamicPoints = nullptr;

    return 0;
}

void initPoint(Point& point, size_t index) {
    point.x = index;
    point.y = index * 2;
}

void printPoint(const Point& point) {
    std::cout << "Point: (" << point.x << ", " << point.y << ")\n";
}
