#pragma once
#include "body.hpp"
#include "yaml-cpp/yaml.h"

class Yaml_reader {
private:
    int N;
    double G;
    double end_time;
    double write_period;
    double timestep;
    int steps;
    int write_steps;
    YAML::Node bodies_config;
    std::ofstream* outfiles;
public:
    Yaml_reader(std::string& config_name);
    ~Yaml_reader();
    void set_directory(std::string& config_name, std::ofstream** outfiles);
    void set_bodies(Simulation simulation);

    int get_N() const {return N;}
    double get_G() const {return G;}
    double get_end_time() const {return end_time;}
    double get_write_period() const {return write_period;}
    double get_timestep() const {return timestep;}
    int get_steps() const {return steps;}
    int get_write_steps() const {return write_steps;}
};
