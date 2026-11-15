#pragma once
#include "body.hpp"


class Integrator {
protected:
    int N;
    double timestep;
public:
    Integrator(int N, double timestep);
    virtual ~Integrator() = default;
    virtual void make_step(double G, Body* bodies) = 0;
};


class Euler: public Integrator {
public:
    Euler(int N, double timestep);
    void make_step(double G, Body* bodies) override;
};


class RK2: public Integrator {
protected:
    Vec2* half_velocities;
    Vec2* half_positions;
public:
    RK2(int N, double timestep);
    ~RK2() override;
    void make_step(double G, Body* bodies) override;
};
