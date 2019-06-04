#ifndef SEALIB_FPT_THREEHITTINGSET_H_
#define SEALIB_FPT_THREEHITTINGSET_H_
#include <sealib/_types.h>
#include <iostream>
#include <set>
#include <cassert>

namespace Sealib {
typedef std::set<uint64_t> hyper_edge_t;
typedef std::set<hyper_edge_t> hyper_graph_t;
typedef std::set<uint64_t> solution_t;
typedef std::set<uint64_t> universe_t;

class ThreeHittingSet {
 public:


    static bool bf(hyper_graph_t &C, solution_t &H, uint64_t k, bool assert = false);
    static bool fpt(hyper_graph_t &C, solution_t &H, uint64_t k, bool assert = false);
    static bool isSolution(const hyper_graph_t &C, const solution_t &H);

 private:
    static void r1(hyper_graph_t &C, uint64_t k);
    static void r2(hyper_graph_t &C, uint64_t k);
    static void r3(hyper_graph_t &C, uint64_t k);
    static bool r4(hyper_graph_t &C, solution_t &H, uint64_t k);
    static bool preprocess(hyper_graph_t &C, solution_t &H, uint64_t k);
    static universe_t getUniverse(const hyper_graph_t &C);

    inline static void ASSERT_INPUT_GRAPH(const hyper_graph_t &C) {
        for(const auto &c : C) {
            assert(c.size() <= 3);
        }
    }
};
}  // namespace Sealib
#endif  // SEALIB_FPT_THREEHITTINGSET_H_
