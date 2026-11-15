
#include "simulation.hpp"
#include <filesystem>
#include "yaml-cpp/yaml.h"
#include "yaml_reader.hpp"
#include <fstream>


Yaml_reader::Yaml_reader(std::string& config_name) {
    YAML::Node config = YAML::LoadFile("cases/" + config_name + ".yaml");
    YAML::Node case_settings = config["case_settings"];

    this->bodies_config = config["bodies"];
    this->N = case_settings["bodies_number"].as<int>();
    this->G = case_settings["gravitational_constant"].as<double>();
    this->end_time = case_settings["end_time"].as<double>();
    this->write_period = case_settings["write_period"].as<double>();
    this->timestep = case_settings["custom_time_step"].as<double>();
    set_directory(config_name, &this->outfiles);
}


Yaml_reader::~Yaml_reader() {
    for (int i = 0; i < N; i++) {
        outfiles[i].close();
    }
    delete[] outfiles;
}


void Yaml_reader::set_directory(std::string& config_name, std::ofstream** outfiles_ptr) {
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

void Yaml_reader::set_bodies(Simulation simulation) {
    for (int i = 0; i < N; i++) {
        YAML::Node body_node = bodies_config["body" + std::to_string(i)];
        Body body = Body(G,
            body_node["mass"].as<double>(),
        Vec2(body_node["position"][0].as<double>(), body_node["position"][1].as<double>()),
        Vec2(body_node["velocity"][0].as<double>(), body_node["velocity"][1].as<double>()));
        simulation.set_body(i, body);
    }
}