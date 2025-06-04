#ifndef __SHAPE_H__
#define __SHAPE_H__

class Shape {
private:
	char *name = nullptr;

protected:
	Shape(const char *name);
	void setName(const char *name);

public:
	Shape(const Shape &o);
	~Shape();

	Shape& operator=(const Shape &o);

	const char *getName() const;

	double perimeter() const;
	double area() const;

};

#endif // __SHAPE_H__
