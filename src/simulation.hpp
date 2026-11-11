#pragma once
#include "body.hpp"


class Simulation {
private:
    int N;
    double G;
    double end_time;
    double write_period;
    double timestep;
    int steps;
    int write_steps;
    Body* bodies;
    std::ofstream* outfiles;
public:
    Simulation(int N, double G, double end_time, double write_period, double timestep);
    ~Simulation();
    Body* get_bodies();
    void set_body(int body_index, const Body& body);
    void set_directory(std::ofstream** outfiles);
    void update_positions();
    void update_velocities();
    void simulate();
    void print_bodies();
    void Euler();
};
