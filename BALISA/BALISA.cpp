#pragma once
#include<iostream>
#include<string>
#include <chrono>

//#include<map>
#include "SteadyDiffusion1D.hpp"
#include "LinearSystem.hpp"
//#include "MathFunctions.hpp"
#include <Eigen/Dense>
//using std::map;
using std::string;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
using Eigen::MatrixXd;
using Eigen::VectorXd;

int main() {
    int number_of_nodes = 100;
    double total_length = 0.5;
    double area = 0.01;
    string static_temp = "ts";
    double thermal_conductivity = 1000.;
    double west_ts = 100.;
    double east_ts = 500.;

    Mesh1D mesh = create_uniform_1d_mesh(number_of_nodes, total_length, area);
    printf("Mesh created succesfully\n");
    //mesh.to_csv("mesh_test");

    SteadyDiffusion1D solver(&mesh);
    printf("Solver created succesfully\n");
    solver.set_transport_equation(static_temp, west_ts, east_ts, thermal_conductivity);
    printf("Transport equation set\n");
    string method = "gauss-seidel";
    auto t1 = high_resolution_clock::now();
    solver.solve("ts", 100, 1e-6, 300.);
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    duration<double, std::milli> ms_double = t2 - t1;
    //solver.display_solution();
    printf("System was solved in %lf ms with Gauss Seidel method\n", ms_double);
    printf("Press enter to close application");
    char trash;
    scanf("\c");
    return 0;
};