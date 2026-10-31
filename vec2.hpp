#ifndef VEC2
#define VEC2
#include <iostream>


bool double_equal(double a, double b);


class Angle;


class Vec2
{
private:
    double x;
    double y;
public:
    Vec2();
    Vec2(double x, double y);
    double get_x() const;
    double get_y() const;
    double get_norm() const;
    double get_norm_squared() const;
    void set_x(double x0);
    void set_y(double y0);
    Vec2 normalized() const;

    Vec2& operator=(const Vec2& vec);
    Vec2 operator+(const Vec2& vec) const;
    Vec2 operator-(const Vec2& vec) const;
    Vec2 operator-() const;
    Vec2 operator*(double coefficient) const;
    Vec2 operator/(double coefficient) const;

    Vec2& operator+=(const Vec2& vec);
    Vec2& operator-=(const Vec2& vec);
    Vec2& operator*=(double coefficient);
    Vec2& operator/=(double coefficient);
    Vec2& operator++();
    Vec2& operator++(int);
    Vec2& operator--();
    Vec2& operator--(int);
    bool operator==(const Vec2& vec) const;
    bool operator<=(const Vec2& vec) const;
    bool operator>=(const Vec2& vec) const;
    bool operator<(const Vec2& vec) const;
    bool operator>(const Vec2& vec) const;
    friend std::ostream& operator<<(std::ostream& out, const Vec2& vec);
    friend std::istream& operator>>(std::istream& in, Vec2& vec);

    friend double cross2(const Vec2& a, const Vec2& b);
    friend double dot(const Vec2& a, const Vec2& b);
    explicit operator double() const;
    explicit operator int() const;
};

#endif
