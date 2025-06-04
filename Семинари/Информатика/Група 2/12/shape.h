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
	virtual ~Shape();

	Shape& operator=(const Shape &o);

	const char *getName() const;

	virtual double perimeter() const = 0;
	virtual double area() const = 0;
};

#endif // __SHAPE_H__
