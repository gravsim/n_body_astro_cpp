
#include "body.hpp"
#include "vec2.hpp"
#include <fstream>


Body::Body() {
    mass = 0;
    position = Vec2();
    velocity = Vec2();
    pos2 = Vec2();
    vel2 = Vec2();
}


Body::Body(double new_mass, const Vec2& new_position, const Vec2& new_velocity) {
    mass = new_mass;
    position = new_position;
    velocity = new_velocity;
    pos2 = Vec2();
    vel2 = Vec2();
}


void Body::set_mass(double new_mass) {
    mass = new_mass;
}


void Body::set_position(const Vec2& new_position) {
    position = new_position;
}


void Body::set_velocity(const Vec2& new_velocity) {
    velocity = new_velocity;
}

void Body::set_pos2(const Vec2& new_pos2) {
    pos2 = new_pos2;
}



void Body::set_vel2(const Vec2& new_vel2) {
    vel2 = new_vel2;
}


double Body::get_mass() const {
    return mass;
}


Vec2 Body::get_position() const {
    return position;
}


Vec2 Body::get_velocity() const {
    return velocity;
}


Vec2 Body::get_pos2() const {
    return pos2;
}


Vec2 Body::get_vel2() const {
    return vel2;
}


void Body::add_position(const Vec2& addition_position) {
    position += addition_position;
}


void Body::add_velocity(const Vec2& addition_velocity) {
    velocity += addition_velocity;
}


void Body::add_vel2(const Vec2& addition_vel2) {
    vel2 += addition_vel2;
}


Vec2 get_distance(Body& body1, Body& body2) {
    return body2.get_position() - body1.get_position();
}


Vec2 get_force(double G, Body& body1, Body& body2) {
    Vec2 distance = get_distance(body1, body2);
    return distance.normalized() * G / distance.get_norm_squared();
}


Vec2 get_force_pos(double G, const Vec2& position1, const Vec2& position2) {
    Vec2 distance = position2 - position1;
    return distance.normalized() * G / distance.get_norm_squared();
}


std::ostream& operator<<(std::ostream& out, const Body& body) {
    out << "Mass: " << body.mass << " Position: " << body.position << "Velocity: " << body.velocity;
    return out;
}


void Body::write_position(std::ofstream& outfile) {
    outfile << position.get_x() << " " << position.get_y() << "\n";
}
