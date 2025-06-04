#include "vec3.h"

#include <cmath>

Vec3::Vec3() : Vec3(0, 0, 0) {}

Vec3::Vec3(double x, double y, double z): x(x), y(y), z(z) {}

Vec3 Vec3::operator+(const Vec3 &o) const {
	return Vec3(this->x + o.x, this->y + o.y, this->z + o.z);
}

Vec3 &Vec3::operator+=(const Vec3& o) {
	this->x += o.x;
	this->y += o.y;
	this->z += o.z;

	return *this;
}

Vec3 Vec3::operator-() const {
	return Vec3(-this->x, -this->y, -this->z);
}

Vec3 Vec3::operator-(const Vec3& o) const {
	return *this + -o;
}

Vec3& Vec3::operator-=(const Vec3& o) {
	*this += -o;

	return *this;
}

Vec3 Vec3::operator*(double a) const {
	return Vec3(this->x * a, this->y * a, this->z * a);
}

Vec3 &Vec3::operator*=(double a) {
	this->x *= a;
	this->y *= a;
	this->z *= a;

	return *this;
}

double Vec3::operator*(const Vec3 &o) const {
	return this->x * o.x + this->y * o.y + this->z * o.z;
}

Vec3 Vec3::operator^(const Vec3 &o) const {
	// Maybe???
	return Vec3(
		this->y * o.z - this->z * o.y,
		this->z * o.x - this->x * o.z,
		this->x * o.y - this->y * o.x
	);
}

double Vec3::len() const {
	return sqrt(*this * *this);
}

Vec3 Vec3::normalized() const {
	return *this * (1 / this->len());
}

void Vec3::normalize() {
	*this *= 1 / this->len();
}

double Vec3::operator[](const Vec3 &o) const {
	return *this * o * (1 / (this->len() * o.len()));
}
