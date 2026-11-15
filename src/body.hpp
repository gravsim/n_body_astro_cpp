#pragma once
#include <iostream>
#include "vec2.hpp"


class Body {
private:
    double mass;
    double force_parameter;
    Vec2 position;
    Vec2 velocity;
public:
    Body();
    Body(double mass, const Vec2& position, const Vec2& velocity);
    void set_mass(double new_mass);
    void set_force_parameter(double force_parameter);
    void set_position(const Vec2& new_position);
    void set_velocity(const Vec2& new_velocity);
    void set_pos2(const Vec2& new_pos2);
    void set_vel2(const Vec2& new_vel2);

    double get_mass() const;
    double get_force_parameter() const;
    Vec2 get_position() const;
    Vec2 get_velocity() const;
    Vec2 get_pos2() const;
    Vec2 get_vel2() const;

    void add_position(const Vec2& addition_position);
    void add_velocity(const Vec2& addition_velocity);
    void add_vel2(const Vec2& addition_vel2);

    friend std::ostream& operator<<(std::ostream& out, const Body& body);
    void write_position(std::ofstream& outfile);
};

Vec2 get_force(Body& body1, Body& body2);
Vec2 get_force_pos(double G, const Vec2& position1, const Vec2& position2);