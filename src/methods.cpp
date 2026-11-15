
#include "methods.hpp"
#include <cmath>
#include <filesystem>
#include "vec2.hpp"
#include "body.hpp"
#include <fstream>
#include <iostream>


Integrator::Integrator(int N, double timestep) {
    this->N = N;
    this->timestep = timestep;
}


Euler::Euler(int N, double timestep): Integrator(N, timestep) {}



void Euler::make_step(Body* bodies) {
    for (int i = 0; i < N; i++) {
        bodies[i].add_position(bodies[i].get_velocity() * timestep);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            Vec2 force = get_force(bodies[i], bodies[j]);
            bodies[i].add_velocity(force * bodies[j].get_force_parameter() * timestep);
            bodies[j].add_velocity(-force * bodies[i].get_force_parameter() * timestep);
        }
    }
}


RK2::RK2(int N, double timestep): Integrator(N, timestep) {
    this->half_positions = new Vec2[N];
    this->half_velocities = new Vec2[N];
}


