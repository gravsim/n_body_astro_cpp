#pragma once
#include "body.hpp"
#include "simulation.hpp"
#include "yaml-cpp/yaml.h"

class Yaml_reader {
private:
    int N;
    double G;
    double end_time;
    double write_period;
    double timestep;
    std::string integrator;
    YAML::Node bodies_config;
    std::ofstream* outfiles;
public:
    explicit Yaml_reader(std::string& config_name);
    ~Yaml_reader();
    void set_directory();
    void set_bodies(Simulation& simulation);
    int get_N() const {return N;}
    double get_G() const {return G;}
    double get_end_time() const {return end_time;}
    double get_write_period() const {return write_period;}
    double get_timestep() const {return timestep;}
    std::string get_integrator() const {return integrator;}
    std::ofstream* get_outfiles() const {return outfiles;}
};
