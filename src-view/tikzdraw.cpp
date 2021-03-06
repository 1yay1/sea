#include "sealibvisual/tikzdraw.h"
#include <vector>

const std::string &SealibVisual::TikzDraw::getOptions() const {
    return options;
}

std::vector<std::string> &SealibVisual::TikzDraw::getPoints() { return points; }

std::vector<std::string> &SealibVisual::TikzDraw::getEdges() { return edges; }

std::ostream &SealibVisual::TikzDraw::out(std::ostream &os) const {
    const std::string defaultEdge = "--";

    os << "\\draw"
       << "[" << options << "]";
    for (uint64_t i = 0; i < points.size(); i++) {
        os << "(" << points[i] << ")";
        if (i < edges.size()) {
            os << " " << edges[i] << " ";
        } else if (i < points.size() - 1) {
            os << " " << defaultEdge << " ";
        }
    }
    os << ";" << std::endl;
    return os;
}
