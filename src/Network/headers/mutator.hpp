//
// Created by oscar on 14/07/2024.
//

#ifndef MINESWEEPERAI_MUTATOR_HPP
#define MINESWEEPERAI_MUTATOR_HPP
#include "genome.hpp"

class Mutator {
private:
    static int calculateNewNodeLayer(Genome &genome, int fromLayer, int toLayer);
    static void initializeNewNodeAndConnections(Genome &genome, int from, int to, int newNodeLayer, float previousWeight);

public:
    static void mutate(Genome &genome);

    static void newNode(Genome &genome);
    static void newConnection(Genome &genome);
    static void mutateWeights(Genome &genome);
    static void mutateBiases(Genome &genome);

    static bool connectionsExists(vector<Connection> &connections, int from, int to);

    static Connection getNewConnectionNodes(Genome &genome, vector<Node> &fromNodes, vector<Node> &toNodes);
};

#endif //MINESWEEPERAI_MUTATOR_HPP
