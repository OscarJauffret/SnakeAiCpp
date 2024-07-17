//
// Created by oscar on 13/07/2024.
//

#include "headers/genome.hpp"

Genome::Genome() {
    fitness = 0.0f;
}

Genome::Genome(int inputSize, int outputSize): fitness(0.0f) {
    for (int i = 0; i < inputSize; i++) {
        createNode(0.0f, Activation::None, 0, -1);
    }
    for (int i = 0; i < outputSize; i++) {
        createNode(0.0f, Activation::Sigmoid, -1, -1);
    }

    for (Node &inputNode : getNodesInLayer(0)) {
        for (Node &outputNode : getNodesInLayer(-1)) {
            addConnection(RNG::randomFloatBetween(-1.0f, 1.0f), inputNode.id, outputNode.id);
        }
    }
}

int Genome::createNode(float bias, Activation activation, int layer, int id) {
    if (id == -1) {
        id = (int) nodes.size();
    }
    nodes.emplace_back(id, layer, bias, ActivationFunction::getFunction(activation));
    return nodes.back().id;
}

void Genome::addConnection(float weight, int from, int to) {
    connections.emplace_back(weight, from, to);
}

vector<Node> Genome::getNodesInLayer(int layer) {
    if (layer == getDepth() - 1) {
        layer = -1;
    }
    vector<Node> nodesInLayer;
    for (Node &node : nodes) {
        if (node.layer == layer) {
            nodesInLayer.push_back(node);
        }
    }
    return nodesInLayer;
}

int Genome::predict(vector<float> &input) {
    for (int i = 0; i < input.size(); i++) {
        nodes[i].value = input[i];
    }
    return forward();
}

int Genome::forward() {
    int depth = getDepth();
    for (int i = 0; i < depth; i++) {                                       // Pour chaque couche
        for (Node& node : nodes) {                                          // Pour chaque nœud
            if (node.layer == i || (i == depth - 1 && node.layer == -1)) {  // Si le nœud est dans la couche actuelle
                double sum = 0;
                for (const Connection& connection : connections) {          // Pour chaque connexion
                    if (connection.to == node.id) {                         // Si la connexion est vers le nœud actuel
                        sum += connection.weight * getNode(connection.from).value;
                    }
                }
                node.value = node.activation(sum + node.bias + node.value);              // Appliquer la fonction d'activation et le biais
            }
        }
    }
    float maxValue = 0;
    int maxIndex = 0;
    vector<Node> outputNodes = getNodesInLayer(-1);
    for (int i = 0; i < outputNodes.size(); i++) {
        if (outputNodes[i].value > maxValue) {
            maxValue = outputNodes[i].value;
            maxIndex = i;
        }
    }
    return maxIndex;
}

int Genome::getDepth() {
    int maxDepth = 0;
    for (Node node : nodes) {
        if (node.layer > maxDepth) {
            maxDepth = node.layer;
        }
    }
    return maxDepth + 2;    // +1 for output layer, +1 for input layer, because output layer has a layer of -1
}

Node & Genome::getNode(int id) {
    for (Node& node : nodes) {
        if (node.id == id) {
            return node;
        }
    }
    throw std::invalid_argument("Node with id " + std::to_string(id) + " not found");
}

float Genome::getFitness() const {
    return fitness;
}

void Genome::setFitness(float fitness) {
    this->fitness = fitness;
}

vector<Connection> &Genome::getConnections() {
    return connections;
}

vector<Node> &Genome::getNodes() {
    return nodes;
}

int Genome::checkIfLayerIsLast(int layer) {
    if (layer == - 1) {
        return getDepth() - 1;
    }
    return layer;
}

bool Genome::checkIfRoomForNode(int fromLayer, int toLayer) {
    if (fromLayer == toLayer) {
        return false;
    }
    if (fromLayer + 1 == toLayer) {
        return false;
    }
    return true;
}

void Genome::updateLayersAfter(int layer) {
    for (Node& node : nodes) {
        if (node.layer >= layer) {
            node.layer++;
        }
    }
}

void Genome::removeConnection(int from, int to) {
    for (int i = 0; i < connections.size(); i++) {
        if (connections[i].from == from && connections[i].to == to) {
            connections.erase(connections.begin() + i);
            return;
        }
    }
}

vector<Node> Genome::getNodesExceptLayer(int layer) {
    vector<Node> n;
    for (Node& node : nodes) {
        if (node.layer != layer) {
            n.push_back(node);
        }
    }
    return n;
}

vector<GameOverType> Genome::getGameOvers() const {
    return gameOvers;
}

void Genome::setGameOvers(const vector<GameOverType> &overs) {
    Genome::gameOvers = overs;
}

duration_t Genome::getTrainingTime() const {
    return trainingTime;
}

void Genome::setTrainingTime(duration_t time) {
    trainingTime = time;
}
