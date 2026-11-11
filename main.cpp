
#include <fstream>
#include <chrono>
#include <iomanip>
#include "yaml-cpp/yaml.h"
#include "src/simulation.hpp"


int main() {
    YAML::Node config = YAML::LoadFile("cases/circles/30_body_circle.yaml");
    YAML::Node case_settings = config["case_settings"];
    double G = case_settings["gravitational_constant"].as<double>();
    int bodies_number = case_settings["bodies_number"].as<int>();
    double end_time = case_settings["end_time"].as<double>();
    double write_period = case_settings["write_period"].as<double>();
    double timestep = case_settings["custom_time_step"].as<double>();
    Simulation simulation = Simulation(bodies_number, G, end_time, write_period, timestep);
    YAML::Node bodies = config["bodies"];

    for (int i = 0; i < bodies_number; i++) {
        YAML::Node body_node = bodies["body" + std::to_string(i)];
        Body body = Body(bodies["body" + std::to_string(i)]["mass"].as<double>(),
        Vec2(body_node["position"][0].as<double>(), body_node["position"][1].as<double>()),
        Vec2(body_node["velocity"][0].as<double>(), body_node["velocity"][1].as<double>()));
        simulation.set_body(i, body);
    }

    std::cout << "Calculation_started.\n";
    auto t1 = std::chrono::high_resolution_clock::now();
    simulation.simulate();
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    std::cout << "Calculation time: " << ms_double.count() / 1000 << " sec\n";
    std::cout << "Calculation complete. \n";
    system("pause");
    return 0;
}
