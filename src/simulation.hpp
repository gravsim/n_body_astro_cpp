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
    Simulation(std::string& config_name, int N, double G, double end_time, double write_period, double timestep);
    ~Simulation();
    Body* get_bodies();
    void set_body(int body_index, const Body& body);
    void set_directory(std::string& config_name, std::ofstream** outfiles);
    void update_positions(double step);
    void update_velocities(double step);
    void simulate();
    void print_bodies();
    void Euler();
    void RK2();
};
