 #include <iostream>
 #include <limits>


 struct Point
 {
    int x;
    int y;
 };

 void readPoint(Point & p)
 {
    _again:
    std::cin >> p.x >> p.y;
    if(!std::cin.good())
    {
        std::cout << "Грешка, въведете координатите "
                  << "разделени с интервал" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        goto _again;
    }
 }

 void writePoint(const Point & p)
 {
    std::cout << p.x << " " << p.y;
 }


 int main()
 {
    Point p;
    readPoint(p);
    writePoint(p);

 }