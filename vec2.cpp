#include "vec2.hpp"
#include <cmath>
#define PI 3.1415926535897932
#define PRECISION 1e-15


// const fun() {}
// means that the return parameter is const,
// use if you return a reference or a pointer
//
// fun() const {}
// means that the function is part of a class and
// cant change any members of that class


bool double_equal(double a, double b) {
    return fabs(a - b) <= PRECISION;
}


int int_sign(double a) {
    if (a < -PRECISION) {
        return -1;
    }
    if (a > PRECISION) {
        return 1;
    }
    return 0;
}


inline Vec2::Vec2() {
    this->x = 0;
    this->y = 0;
}


inline Vec2::Vec2(double x, double y) {
    this->x = x;
    this->y = y;
}


inline double Vec2::get_x() const {
    return x;
}


inline double Vec2::get_y() const {
    return y;
}


inline double Vec2::get_norm() const {
    return sqrt(x * x + y * y);
}


inline double Vec2::get_norm_squared() const {
    return x * x + y * y;
}


inline void Vec2::set_x(double x0) {
    this->x = x0;
}


inline void Vec2::set_y(double y0) {
    this->y = y0;
}


inline Vec2& Vec2::operator=(const Vec2& vec) {
    x = vec.x;
    y = vec.y;
    return *this;
}


inline Vec2 Vec2::operator+(const Vec2& vec) const {
    return Vec2(x + vec.x, y + vec.y);
}


inline Vec2 Vec2::operator-(const Vec2& vec) const {
    return Vec2(x - vec.x, y - vec.y);
}


inline Vec2 Vec2::operator-() const {
    return Vec2(-x, -y);
}


inline Vec2 Vec2::operator*(double coefficient) const {
    return Vec2(x * coefficient, y * coefficient);
}


inline Vec2 operator*(double coefficient, Vec2 vec) {
    return vec * coefficient;
}


inline Vec2 Vec2::operator/(double coefficient) const {
    return Vec2(x / coefficient, y / coefficient);
}


inline Vec2& Vec2::operator+=(const Vec2& vec) {
    x += vec.x;
    y += vec.y;
    return *this;
}


inline Vec2& Vec2::operator-=(const Vec2& vec) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}


inline Vec2& Vec2::operator*=(double coefficient) {
    x *= coefficient;
    y *= coefficient;
    return *this;
}


inline Vec2& Vec2::operator/=(double coefficient) {
    x /= coefficient;
    y /= coefficient;
    return *this;
}


inline Vec2& Vec2::operator++() {
    x++;
    y++;
    return *this;
}


inline Vec2& Vec2::operator++(int) {
    x++;
    y++;
    return *this;
}


inline Vec2& Vec2::operator--() {
    x--;
    y--;
    return *this;
}


inline Vec2& Vec2::operator--(int) {
    x--;
    y--;
    return *this;
}


inline bool Vec2::operator==(const Vec2& vec) const {
    return double_equal(x, vec.x) && double_equal(y, vec.y);
}


inline bool Vec2::operator<=(const Vec2& vec) const {
    if (!double_equal(x, vec.x)) {
        return x <= vec.x;
    }
    if (!double_equal(y, vec.y)) {
        return y <= vec.y;
    }
    return false;
}


inline bool Vec2::operator>=(const Vec2& vec) const {
    if (!double_equal(x, vec.x)) {
        return x >= vec.x;
    }
    if (!double_equal(y, vec.y)) {
        return y >= vec.y;
    }
    return false;
}


inline bool Vec2::operator<(const Vec2& vec) const {
    if (!double_equal(x, vec.x)) {
        return x < vec.x;
    }
    if (!double_equal(y, vec.y)) {
        return y < vec.y;
    }
    return false;
}


inline bool Vec2::operator>(const Vec2& vec) const {
    if (!double_equal(x, vec.x)) {
        return x > vec.x;
    }
    if (!double_equal(y, vec.y)) {
        return y > vec.y;
    }
    return false;
}


inline Vec2::operator double() const {
    return get_norm();
}


inline Vec2::operator int() const {
    return (int)get_norm();
}


std::ostream& operator<<(std::ostream& out, const Vec2& vec) {
    out << "(" << vec.x << ", " << vec.y << ") ";
    return out;
}


std::istream& operator>>(std::istream& in, Vec2& vec) {
    return in >> vec.x >> vec.y;
}


inline Vec2 Vec2::normalized() const {
    return Vec2(x / this->get_norm(), y / this->get_norm());
}


inline double distance(const Vec2& a, const Vec2& b) {
    return (a - b).get_norm();
}


inline double cross2(const Vec2& a, const Vec2& b) {
    return a.x * b.y - a.y * b.x;
}


inline double dot(const Vec2& a, const Vec2& b) {
    return a.x * b.x + a.y * b.y;
}


inline int vectors_sign(const Vec2& point, const Vec2& start, const Vec2& end) {
    Vec2 edge = end - start;
    Vec2 diff = point - start;
    int result = int_sign(cross2(edge, diff));
    return result;
}


inline double cos_between(const Vec2& a, const Vec2& b) {
    return dot(a.normalized(), b.normalized());
}
