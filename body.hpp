#include <iostream>
#include "vec2.hpp"

class Body {
private:
    double mass;
    Vec2 position;
    Vec2 velocity;
public:
    Body();
    Body(double new_mass, const Vec2& new_position, const Vec2& new_velocity);
    void set_mass(double new_mass);
    void set_position(Vec2& new_position);
    void set_velocity(Vec2& new_velocity);

    double get_mass();
    Vec2 get_position();
    Vec2 get_velocity();
    void add_position(const Vec2& addition_position);
    void add_velocity(const Vec2& addition_velocity);

    friend std::ostream& operator<<(std::ostream& out, const Body& body);
    void write_position(std::ofstream& outfile);
};
