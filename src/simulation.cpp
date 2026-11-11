
#include "simulation.hpp"
#include <cmath>
#include <filesystem>
#include "vec2.hpp"
#include "body.hpp"
#include <fstream>
#include <iostream>


Simulation::Simulation(std::string& config_name, int N, double G, double end_time, double write_period, double timestep) {
    this->N = N;
    this->G = G;
    this->end_time = end_time;
    this->write_period = write_period;
    this->timestep = timestep;
    this->steps = static_cast<int>(end_time / timestep);
    this->write_steps = static_cast<int>(write_period / timestep);
    this->steps = static_cast<int>(end_time / timestep);
    this->bodies = new Body[N];
    set_directory(config_name, &this->outfiles);
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


void Simulation::update_positions(double step) {
    for (int i = 0; i < N; i++) {
        bodies[i].add_position(bodies[i].get_velocity() * step);
    }
}


void Simulation::update_velocities(double step) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            Vec2 force = get_force(G, bodies[i], bodies[j]);
            bodies[i].add_velocity(force * bodies[j].get_mass() * step);
            bodies[j].add_velocity(-force * bodies[i].get_mass() * step);
        }
    }
}


void Simulation::print_bodies() {
    for (int i = 0; i < N; i++) {
        std::cout << bodies[i] << "\n";
    }
}



void Simulation::set_directory(std::string& config_name, std::ofstream** outfiles_ptr) {
    time_t timestamp;
    time(&timestamp);
    tm datetime = *localtime(&timestamp);
    char output[50];
    strftime(output, 50, "%Y-%b-%d_%H.%M.%S", &datetime);

    std::string res = "results/";
    std::string dir_name = res + output;
    std::filesystem::create_directory(dir_name);
    *outfiles_ptr = new std::ofstream[N];
    for (int i = 0; i < N; i++) {
        std::string output_name = dir_name + "/body" + std::to_string(i) + ".txt";
        (*outfiles_ptr)[i].open(output_name, std::ios_base::out);
    }
}


void Simulation::Euler() {
    update_positions(timestep);
    update_velocities(timestep);
}


void Simulation::RK2() {
    for (int i = 0; i < N; i++) {
        bodies[i].set_pos2(bodies[i].get_position());
        bodies[i].set_vel2(bodies[i].get_velocity());
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            Vec2 force = get_force_pos(G, bodies[i].get_pos2(), bodies[j].get_pos2());
            bodies[i].add_vel2(force * bodies[j].get_mass() * timestep / 2);
            bodies[j].add_vel2(-force * bodies[i].get_mass() * timestep / 2);
        }
    }
    for (int i = 0; i < N; i++) {
        bodies[i].set_pos2(bodies[i].get_position() + bodies[i].get_velocity() * timestep / 2);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            Vec2 force = get_force_pos(G, bodies[i].get_pos2(), bodies[j].get_pos2());
            bodies[i].add_velocity(force * bodies[j].get_mass() * timestep);
            bodies[j].add_velocity(-force * bodies[i].get_mass() * timestep);
        }
    }
    for (int i = 0; i < N; i++) {
        bodies[i].set_position(bodies[i].get_position() + bodies[i].get_vel2() * timestep);
    }
}


void Simulation::simulate() {
    for (int step = 0; step < steps; step++) {
        RK2();
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
