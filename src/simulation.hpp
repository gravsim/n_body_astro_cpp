#pragma once
#include "body.hpp"
#include "methods.hpp"

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
public:
    Simulation(int N, double G, double end_time, double write_period, double timestep);
    ~Simulation();
    Body* get_bodies();
    void set_body(int body_index, const Body& body);
    void simulate(Integrator* integrator, std::ofstream* outfiles);
    void print_bodies();
};
