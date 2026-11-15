#pragma once
#include "body.hpp"


class Integrator {
protected:
    int N;
    double timestep;
public:
    Integrator(Body* bodies, int N, double timestep);
    virtual ~Integrator() = default;
    virtual void make_step(double G, Body* bodies) = 0;
};


class Euler: public Integrator {
protected:
    Vec2* accelerations;
public:
    Euler(Body* bodies, int N, double timestep);
    ~Euler() override;
    void make_step(double G, Body* bodies) override;
};


class Implicit_Euler: public Integrator {
public:
    Implicit_Euler(Body* bodies, int N, double timestep);
    void make_step(double G, Body* bodies) override;
};


class RK2: public Integrator {
protected:
    Vec2* half_velocities;
    Vec2* half_positions;
public:
    RK2(Body* bodies, int N, double timestep);
    ~RK2() override;
    void make_step(double G, Body* bodies) override;
};


class Verlet: public Integrator {
protected:
    Vec2* old_positions;
    Vec2* accelerations;
public:
    Verlet(Body* bodies, int N, double timestep);
    ~Verlet() override;
    void make_step(double G, Body* bodies) override;
};
