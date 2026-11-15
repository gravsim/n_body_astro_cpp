
#include "simulation.hpp"
#include "body.hpp"
#include <fstream>
#include <iostream>


Simulation::Simulation(int N, double G, double end_time, double write_period, double timestep) {
    this->N = N;
    this->G = G;
    this->end_time = end_time;
    this->write_period = write_period;
    this->timestep = timestep;
    this->steps = static_cast<int>(end_time / timestep);
    this->write_steps = static_cast<int>(write_period / timestep);
    this->steps = static_cast<int>(end_time / timestep);
    this->bodies = new Body[N];
}


Simulation::~Simulation() {
    for (int i = 0; i < N; i++) {
        outfiles[i].close();
    }
    delete[] bodies;
    delete[] outfiles;
}


Body *Simulation::get_bodies() {
    return bodies;
}


void Simulation::set_body(int body_index, const Body& body) {
    bodies[body_index] = body;
}


void Simulation::print_bodies() {
    for (int i = 0; i < N; i++) {
        std::cout << bodies[i] << "\n";
    }
}


void Simulation::simulate(Integrator* integrator) {
    for (int step = 0; step < steps; step++) {
        integrator->make_step(G, bodies);
        if (step % write_steps == 0) {
            for (int i = 0; i < N; i++) {
                bodies[i].write_position(outfiles[i]);
            }
        }
        if (step * 100 % steps == 0) {
            std::cout << "Calculation: " << step * 100 / steps << "%\r";
        }
    }
}
