
#include "body.hpp"
#include "vec2.hpp"
#include <fstream>


Body::Body() {
    mass = 0;
    force_parameter = 0;
    position = Vec2();
    velocity = Vec2();
}


Body::Body(double mass, const Vec2& position, const Vec2& velocity) {
    this->mass = mass;
    this->position = position;
    this->velocity = velocity;
}


void Body::set_mass(double new_mass) {
    mass = new_mass;
}


void Body::set_force_parameter(double force_parameter) {
    this->force_parameter = force_parameter;
}


void Body::set_position(const Vec2& new_position) {
    position = new_position;
}


void Body::set_velocity(const Vec2& new_velocity) {
    velocity = new_velocity;
}


double Body::get_mass() const {
    return mass;
}


double Body::get_force_parameter() const {
    return force_parameter;
}



Vec2 Body::get_position() const {
    return position;
}


Vec2 Body::get_velocity() const {
    return velocity;
}


void Body::add_position(const Vec2& addition_position) {
    position += addition_position;
}


void Body::add_velocity(const Vec2& addition_velocity) {
    velocity += addition_velocity;
}


Vec2 get_distance(Body& body1, Body& body2) {
    return body2.get_position() - body1.get_position();
}


Vec2 get_force(Body& body1, Body& body2) {
    Vec2 distance = get_distance(body1, body2);
    return distance.normalized() / distance.get_norm_squared();
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
