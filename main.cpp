#include "body.cpp"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <filesystem>
#include <ctime>

void update_positions(int N, double timestep, Body* bodies) {
    for (int i = 0; i < N; i++) {
        bodies[i].add_position(bodies[i].get_velocity() * timestep);
    }
}


void update_velocities(int N, double timestep, double G, Body* bodies) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            Vec2 force = get_force(G, bodies[i], bodies[j]);
            bodies[i].add_velocity(force * bodies[j].get_mass() * timestep);
            bodies[j].add_velocity(-force * bodies[i].get_mass() * timestep);
        }
    }
}


void print_bodies(int N, Body* bodies) {
    for (int i = 0; i < N; i++) {
        std::cout << bodies[i] << "\n";
    }
}


void write_bodies(int N, Body body, std::ofstream& outfile) {
    outfile << body << "\n";
}


void set_directory(int N, std::ofstream** outfiles) {
    time_t timestamp;
    time(&timestamp);
    tm datetime = *localtime(&timestamp);
    char output[50];
    strftime(output, 50, "%Y-%b-%d_%H.%M.%S", &datetime);

    std::string res = "results/";
    std::string dir_name = res + output;
    std::filesystem::create_directory(dir_name);
    *outfiles = new std::ofstream[N];
    for (int i = 0; i < N; i++) {
        std::string output_name = dir_name + "/body" + std::to_string(i) + ".txt";
        (*outfiles)[i].open(output_name, std::ios_base::out);
    }
}


void Euler() {

}


void simulate(int N, int steps, double timestep, double G, ) {
    for (int step = 0; step < steps; step ++) {
        update_velocities(N, timestep, G, bodies);
        update_positions(N, timestep, bodies);
        if (step % write_steps == 0) {
            for (int i = 0; i < N; i++) {
                bodies[i].write_position(outfiles[i]);
            }
        }
        if (step * 100 % steps == 0) {
            std::cout << "Calculation: " << step * 100 / steps << "%\r";
        }
    }
}



int main() {
    double G = 6.67e-11;
    int N = 3;
    double end_time = 5000000;
    double write_period = 20;
    double timestep = 0.5;
    int steps = (int)(end_time / timestep);
    int write_steps = (int)(write_period / timestep);
    Body* bodies = new Body[N];
    bodies[0] = Body(1,
        Vec2(-0.5, 0),
        Vec2(0, 0.0));
    bodies[1] = Body(0.1,
            Vec2(0.5, 0),
            Vec2(0, 0.0));
    bodies[2] = Body(0.01,
            Vec2(0.2637098062, 0.3223452642),
            Vec2(0, 0.0));
    std::ofstream* outfiles = nullptr;
    set_directory(N, &outfiles);
    std::cout << "Calculation_started.\n";
    auto t1 = std::chrono::high_resolution_clock::now();

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    std::cout << "Calculation time: " << ms_double.count() / 1000 << " sec\n";
    std::cout << "Calculation complete. \n";
    // print_bodies(N, bodies);
    for (int i = 0; i < N; i++) {
        outfiles[i].close();
    }
    delete[] bodies;
    delete[] outfiles;
    system("pause");
    return 0;
}
