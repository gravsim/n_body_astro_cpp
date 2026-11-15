
#include <fstream>
#include <chrono>
#include <iomanip>
#include "src/yaml_reader.hpp"
#include "src/simulation.hpp"


int main() {
    std::string config_name;
    std::cout << "Enter config_name: ";
    std::cin >> config_name;
    std::cout << "Calculating: " << config_name << "\n";
    Yaml_reader yaml_reader = Yaml_reader(config_name);
    Simulation simulation = Simulation(
        yaml_reader.get_N(),
        yaml_reader.get_G(),
        yaml_reader.get_end_time(),
        yaml_reader.get_write_period(),
        yaml_reader.get_timestep()
        );
    yaml_reader.set_bodies(simulation);

    Integrator* integrator;
    if (yaml_reader.get_integrator() == "euler") {
        integrator = new Euler(simulation.get_bodies(), yaml_reader.get_N(), yaml_reader.get_timestep());
    } else if (yaml_reader.get_integrator() == "implicit_euler") {
        integrator = new Implicit_Euler(simulation.get_bodies(), yaml_reader.get_N(), yaml_reader.get_timestep());
    } else if (yaml_reader.get_integrator() == "RK2") {
        integrator = new RK2(simulation.get_bodies(), yaml_reader.get_N(), yaml_reader.get_timestep());
    } else if (yaml_reader.get_integrator() == "verlet") {
        integrator = new Verlet(simulation.get_bodies(), yaml_reader.get_N(), yaml_reader.get_timestep());
    } else {
        integrator = new Euler(simulation.get_bodies(), yaml_reader.get_N(), yaml_reader.get_timestep());
    }

    std::cout << "Calculation_started.\n";
    auto t1 = std::chrono::high_resolution_clock::now();
    simulation.simulate(integrator, yaml_reader.get_outfiles());
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    std::cout << "Calculation time: " << ms_double.count() / 1000 << " sec\n";
    std::cout << "Calculation complete. \n";
    system("pause");
    return 0;
}
