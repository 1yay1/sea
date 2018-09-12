#ifndef SEALIB_GRAPHCREATOR_H_
#define SEALIB_GRAPHCREATOR_H_

#include <random>
#include "sealib/basicgraph.h"

namespace Sealib {
/**
 * Static class that serves as a collection of functions to create graph objects
 * from different inputs.
 * @author Johannes Meintrup
 */
class GraphCreator {
 public:
  /**
   * Static function to create a a graph object from an adjacency matrix.
   *
   * example matrix with order 3:
   *
   * n         0       1       2
   *      **************************
   *  0   *    0   *   1   *   1   *
   *      **************************
   *  1   *    1   *   0   *   2   *
   *      **************************
   *  2   *    0   *   2   *   1   *
   *      **************************
   * @param adj_matrix NxN adjacency matrix representation of the graph.
   * @param _order Order of the graph, order equals the number of nodes.
   */
  static Basicgraph *createGraphFromAdjacencyMatrix(unsigned int **adjMatrix,
                                                    unsigned int order);

  /**
   * Create a random graph with a fixed number of neighbours per node.
   * @param order number of nodes the graph should contain
   * @param degreePerNode the degree of each node; the edges will go to any
   * random node
   * @return the resulting graph G (n = order, m = degreePerNode*order)
   * @author Simon Heuser
   */
  static Basicgraph *createRandomFixed(unsigned int order,
                                       unsigned int degreePerNode);
};
}  // namespace Sealib
#endif  // SEALIB_GRAPHCREATOR_H_
