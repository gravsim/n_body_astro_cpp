
#include "methods.hpp"
#include <cmath>
#include "vec2.hpp"
#include "body.hpp"


Integrator::Integrator(Body* bodies, int N, double timestep) {
    this->N = N;
    this->timestep = timestep;
}


Euler::Euler(Body* bodies, int N, double timestep): Integrator(bodies, N, timestep) {
    this->accelerations = new Vec2[N];
}


Euler::~Euler() {
    delete[] accelerations;
}


void Euler::make_step(Body* bodies) {
    for (int i = 0; i < N; i++) {
        accelerations[i] = Vec2{0, 0};
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            Vec2 force = get_force(bodies[i], bodies[j]);
            accelerations[i] += force * bodies[j].get_force_parameter();
            accelerations[j] -= force * bodies[i].get_force_parameter();
        }
    }
    for (int i = 0; i < N; i++) {
        bodies[i].add_position(bodies[i].get_velocity() * timestep);
        bodies[i].add_velocity(accelerations[i] * timestep);
    }
}


Implicit_Euler::Implicit_Euler(Body* bodies, int N, double timestep): Integrator(bodies, N, timestep) {}


void Implicit_Euler::make_step(Body* bodies) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            Vec2 force = get_force(bodies[i], bodies[j]);
            bodies[i].add_velocity(force * bodies[j].get_force_parameter() * timestep);
            bodies[j].add_velocity(-force * bodies[i].get_force_parameter() * timestep);
        }
    }
    for (int i = 0; i < N; i++) {
        bodies[i].add_position(bodies[i].get_velocity() * timestep);
    }
}


RK2::RK2(Body* bodies, int N, double timestep): Integrator(bodies, N, timestep) {
    this->half_positions = new Vec2[N];
    this->half_velocities = new Vec2[N];
}


RK2::~RK2() {
    delete[] half_positions;
    delete[] half_velocities;
}


void RK2::make_step(Body* bodies) {
    for (int i = 0; i < N; i++) {
        half_positions[i] = bodies[i].get_position();
        half_velocities[i] = bodies[i].get_velocity();
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            Vec2 force = get_force_pos(half_positions[i], half_positions[j]);
            half_velocities[i] += force * bodies[j].get_force_parameter() * timestep / 2;
            half_velocities[j] -= force * bodies[i].get_force_parameter() * timestep / 2;
        }
    }
    for (int i = 0; i < N; i++) {
        half_positions[i] = bodies[i].get_position() + bodies[i].get_velocity() * timestep / 2;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            Vec2 force = get_force_pos(half_positions[i], half_positions[j]);
            bodies[i].add_velocity(force * bodies[j].get_force_parameter() * timestep);
            bodies[j].add_velocity(-force * bodies[i].get_force_parameter() * timestep);
        }
    }
    for (int i = 0; i < N; i++) {
        bodies[i].set_position(bodies[i].get_position() + half_velocities[i] * timestep);
    }
}


Verlet::Verlet(Body* bodies, int N, double timestep): Integrator(bodies, N, timestep) {
    this->old_positions = new Vec2[N];
    this->accelerations = new Vec2[N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            Vec2 force = get_force_pos(bodies[i].get_position(), bodies[j].get_position());
            accelerations[i] += force * bodies[j].get_force_parameter();
            accelerations[j] -= force * bodies[i].get_force_parameter();
        }
    }
    for (int i = 0; i < N; i++) {
        this->old_positions[i] =
            bodies[i].get_position() - bodies[i].get_velocity() * timestep
        + timestep * timestep / 2 * accelerations[i];
    }
}


Verlet::~Verlet() {
    delete[] old_positions;
    delete[] accelerations;
}


void Verlet::make_step(Body* bodies) {
    for (int i = 0; i < N; i++) {
        accelerations[i] = Vec2(0, 0);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            Vec2 force = get_force_pos(bodies[i].get_position(), bodies[j].get_position());
            accelerations[i] += force * bodies[j].get_force_parameter();
            accelerations[j] -= force * bodies[i].get_force_parameter();
        }
    }
    for (int i = 0; i < N; i++) {
        Vec2 current = bodies[i].get_position();
        bodies[i].set_position(2 * bodies[i].get_position() - old_positions[i] + accelerations[i] * timestep * timestep);
        old_positions[i] = current;
    }
}
