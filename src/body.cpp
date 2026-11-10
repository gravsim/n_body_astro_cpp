#include <iostream>
#include "vec2.cpp"
#include "body.hpp"
#include <cmath>
#include <fstream>


Body::Body() {
    mass = 0;
    position = Vec2();
    velocity = Vec2();
}


Body::Body(double new_mass, const Vec2& new_position, const Vec2& new_velocity) {
    mass = new_mass;
    position = new_position;
    velocity = new_velocity;
}


inline void Body::set_mass(double new_mass) {
    mass = new_mass;
}


inline void Body::set_position(Vec2 &new_position) {
    velocity = new_position;
}


inline void Body::set_velocity(Vec2 &new_velocity) {
    velocity = new_velocity;
}


inline double Body::get_mass() {
    return mass;
}


inline Vec2 Body::get_position() {
    return position;
}


inline Vec2 Body::get_velocity() {
    return velocity;
}


inline void Body::add_position(const Vec2& addition_position) {
    position += addition_position;
}


inline void Body::add_velocity(const Vec2& addition_velocity) {
    velocity += addition_velocity;
}


inline Vec2 get_distance(Body& body1, Body& body2) {
    return body2.get_position() - body1.get_position();
}


inline Vec2 get_force(double G, Body& body1, Body& body2) {
    Vec2 distance = get_distance(body1, body2);
    return distance.normalized() * G / distance.get_norm_squared();
}


std::ostream& operator<<(std::ostream& out, const Body& body) {
    out << "Mass: " << body.mass << " Position: " << body.position << "Velocity: " << body.velocity;
    return out;
}


inline void Body::write_position(std::ofstream& outfile) {
    outfile << position.get_x() << " " << position.get_y() << "\n";
}
