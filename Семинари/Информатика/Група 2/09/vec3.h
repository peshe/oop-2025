#ifndef __VEC3_H__
#define __VEC3_H__

class Vec3 {
public:
	double x, y, z;

	Vec3();
	Vec3(double x, double y, double z);

	Vec3 operator+(const Vec3 &o) const;
	Vec3 &operator+=(const Vec3 &o);

	Vec3 operator-() const;

	Vec3 operator-(const Vec3 &o) const;
	Vec3 &operator-=(const Vec3 &o);

	Vec3 operator*(double a) const;
	Vec3 &operator*=(double a);

	double operator*(const Vec3 &o) const;
	Vec3 operator^(const Vec3 &o) const;

	double len() const;

	Vec3 normalized() const;
	void normalize();

	double operator[](const Vec3& o) const;
};

#endif // __VEC3_H__

