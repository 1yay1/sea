#include <sealib/fpt/threehittingset.h>
#include <algorithm>
using Sealib::ThreeHittingSet;

bool ThreeHittingSet::isSolution(const Sealib::hyper_graph_t &C,
                                 const Sealib::solution_t &H) {
    for (const auto &c : C) {
        bool found = false;
        for (const auto &h : H) {
            if (c.find(h) != c.end()) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

bool ThreeHittingSet::bf(Sealib::hyper_graph_t &C, Sealib::solution_t &H,
                         uint64_t k, bool assert) {
    if (assert) ASSERT_INPUT_GRAPH(C);
    if (H.size() > k) {
        return false;
    }
    if (C.empty()) {
        return true;
    }
    auto c = *C.begin();
    for (uint64_t i : c) {
        C.erase(c);
        H.insert(i);
        bool d = bf(C, H, k);
        C.insert(c);
        if (d) return true;
        H.erase(i);
    }
    return false;
}

Sealib::universe_t ThreeHittingSet::getUniverse(
    const Sealib::hyper_graph_t &C) {
    universe_t U;
    for (const auto &e : C) {
        for (const auto &_e : e) {
            U.insert(_e);
        }
    }
    return U;
}

void ThreeHittingSet::r1(Sealib::hyper_graph_t &C, uint64_t k) {
    Sealib::hyper_graph_t _C;
    std::copy_if(C.begin(), C.end(), std::inserter(_C, _C.begin()),
                 [](Sealib::hyper_edge_t e) { return e.size() == 3; });
    Sealib::universe_t U = getUniverse(_C);

    Sealib::hyper_graph_t possibleCores;
    for (const auto &e1 : U) {
        for (const auto &e2 : U) {
            if (e1 != e2) possibleCores.insert({e1, e2});
        }
    }

    for (const auto &c : possibleCores) {
        Sealib::hyper_graph_t tmp;
        for (const auto &e : _C) {
            Sealib::hyper_edge_t _tmp;
            std::set_intersection(e.begin(), e.end(), c.begin(), c.end(),
                                  std::inserter(_tmp, _tmp.begin()));
            if (_tmp.size() == 2) {
                tmp.insert(e);
            }
        }
        if (tmp.size() > k) {
            for (const auto &_c : tmp) {
                C.erase(_c);
            }
            C.insert(c);
        }
    }
}

void ThreeHittingSet::r2(Sealib::hyper_graph_t &C, uint64_t k) {
    Sealib::hyper_graph_t _C;
    std::copy_if(C.begin(), C.end(), std::inserter(_C, _C.begin()),
                 [](Sealib::hyper_edge_t e) { return e.size() == 3; });
    Sealib::universe_t possibleCores = getUniverse(_C);

    for (const auto &c : possibleCores) {
        Sealib::hyper_graph_t tmp;
        for (const auto &e : _C) {
            if (e.find(c) != e.end()) tmp.insert(e);
        }
        if (tmp.size() > k * k) {
            for (const Sealib::hyper_edge_t &_c : tmp) {
                C.erase(_c);
            }
            C.insert({c});
        }
    }
}

void ThreeHittingSet::r3(Sealib::hyper_graph_t &C, uint64_t k) {
    Sealib::hyper_graph_t _C;
    std::copy_if(C.begin(), C.end(), std::inserter(_C, _C.begin()),
                 [](Sealib::hyper_edge_t e) { return e.size() == 2; });
    Sealib::universe_t possibleCores = getUniverse(_C);

    for (const auto &c : possibleCores) {
        Sealib::hyper_graph_t tmp;
        for (const auto &e : _C) {
            if (e.find(c) != e.end()) tmp.insert(e);
        }
        if (tmp.size() > k) {
            for (const auto &_c : tmp) {
                C.erase(_c);
            }
            C.insert({c});
        }
    }
}

bool ThreeHittingSet::r4(Sealib::hyper_graph_t &C, Sealib::solution_t &H,
                         uint64_t k) {
    for (auto &e : C) {
        if (e.size() == 1) {
            if (k == 0) return false;
            H.insert(*e.begin());
            C.erase(e);
            k--;
        }
    }
    return true;
}

bool ThreeHittingSet::preprocess(Sealib::hyper_graph_t &C,
                                 Sealib::solution_t &H, uint64_t k) {
    r1(C, k);
    r2(C, k);
    r3(C, k);
    return r4(C, H, k);
}

bool Sealib::ThreeHittingSet::fpt(Sealib::hyper_graph_t &C,
                                  Sealib::solution_t &H, uint64_t k,
                                  bool assert) {
    if (assert) ASSERT_INPUT_GRAPH(C);
    if (!preprocess(C, H, k)) return false;
    return bf(C, H, k);
}
