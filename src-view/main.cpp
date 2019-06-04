#include <sealib/_types.h>
#include <sealib/fpt/threehittingset.h>
#include <sealib/graph/graphcreator.h>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "./test_algorithms.h"
#include "./test_visual.h"
#include <set>
using Sealib::ThreeHittingSet;

std::ostream &operator<<(std::ostream &out,
                         const Sealib::solution_t &H);
std::ostream &operator<<(std::ostream &out,
                         const Sealib::hyper_graph_t &C);

std::ostream &operator<<(std::ostream &out,
                         const Sealib::solution_t &H) {
    out << "{ ";
    for (auto &e : H) {
        out << e << " ";
    }
    out << "}";
    return out;
}

std::ostream &operator<<(std::ostream &out,
                         const Sealib::hyper_graph_t &C) {
    out << "{ ";
    for (auto &e : C) {
        out << e << " ";
    }
    out << "}";
    return out;
}

int main(/*int argc, char **argv*/) {
    /*if (argc < 6) {
        printf("Usage: bin/main <program> <file1> <file2> <from> <to>\n");
        return 1;
    }
    return Sealib::AlgorithmComparison::launch(
        argv[1], argv[2], argv[3],
        static_cast<uint64_t>(strtod(argv[4], nullptr)),
        static_cast<uint64_t>(strtod(argv[5], nullptr)));*/

    Sealib::hyper_graph_t C = {{6, 8, 9},      {1, 2, 3},          {2},
                       {2, 9},         {999, 2, 4},        {999, 2, 12},
                       {999, 2, 59},   {999, 2},           {999, 3},
                       {999, 4},       {999, 5},           {999, 2, 3},
                       {999, 3, 4},    {999, 5, 6},        {999, 86, 58},
                       {999, 59, 666}, {999, 1111, 11111}, {999, 29348, 69}};

    uint64_t k = 3;
    Sealib::solution_t H;
    if (Sealib::ThreeHittingSet::fpt(C, H, k, false)) {
        std::cout << "The solution to: " << C << " is " << H << std::endl;
        std::cout << "This solution is "
                  << (Sealib::ThreeHittingSet::isSolution(C, H) ? "valid"
                                                                : "invalid")
                  << std::endl;
    } else {
        std::cout << "No solution of size " << k << " found for " << C
                  << std::endl;
    }
}
