#pragma once
#include<iostream>
#include <string>
#include <map>

using std::string;
using std::map;

class Node1D{
    public:
        map<string, double> transported_vars;
        Node1D(int node_id, double x, double area);

        int get_id();
        double get_x();
        double get_area();
        void display_node_data();
    private:
        int node_id;
        double x;
        double area;
};

void write_node_to_csv(FILE* node_file, Node1D node_to_print);
