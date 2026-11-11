#pragma once
#include <iostream>
#include "vec2.hpp"


class Body {
private:
    double mass;
    Vec2 position;
    Vec2 velocity;
    Vec2 pos2;
    Vec2 vel2;
public:
    Body();
    Body(double new_mass, const Vec2& new_position, const Vec2& new_velocity);
    void set_mass(double new_mass);
    void set_position(const Vec2& new_position);
    void set_velocity(const Vec2& new_velocity);
    void set_pos2(const Vec2& new_pos2);
    void set_vel2(const Vec2& new_vel2);

    double get_mass() const;
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

Vec2 get_force(double G, Body& body1, Body& body2);
Vec2 get_force_pos(double G, const Vec2& position1, const Vec2& position2);