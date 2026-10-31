
#include <fstream>
#include <chrono>
#include <iomanip>
#include "simulation.cpp"



int main() {
    double G = 6.67e-11;
    int N = 3;
    double end_time = 5000000;
    double write_period = 20;
    double timestep = 0.5;
    Simulation simulation = Simulation(N, G, end_time, write_period, timestep);
    Body a = Body(1,
        Vec2(-0.5, 0),
        Vec2(0, 0.0));
    simulation.set_body(1, a);
    Body b = Body(0.1,
            Vec2(0.5, 0),
            Vec2(0, 0.0));
    simulation.set_body(0, b);
    Body c = Body(0.01,
            Vec2(0.2637098062, 0.3223452642),
            Vec2(0, 0.0));
    simulation.set_body(2, c);
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
