//
// Created by oscar on 13/07/2024.
//

#ifndef MINESWEEPERAI_GENOME_HPP
#define MINESWEEPERAI_GENOME_HPP
#include "activation.hpp"
#include "../../Engine/headers/rng.hpp"
#include "../../config.hpp"
#include "../../Engine/headers/snakepart.hpp"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct Node {
    int id;
    int layer;
    float value;
    float bias;
    ActivationPtr activation;

    Node() : id(-1), layer(-2), value(0.0), bias(0.0), activation(nullptr) {}
    Node(int id, int layer, float bias, ActivationPtr activation) : id(id), layer(layer), value(0.0), bias(bias), activation(activation) {}
};

struct Connection {
    float weight;
    int from;
    int to;

    Connection(float weight, int from, int to) : weight(weight), from(from), to(to) {}
};

class Genome {
    vector<Node> nodes;
    vector<Connection> connections;
    float fitness;
    duration_t trainingTime = 0;
    vector<GameOverType> gameOvers;
public:
    Genome();
    Genome(int inputSize, int outputSize);

    int getDepth();
    Node &getNode(int id);
    void updateLayersAfter(int layer);
    void removeConnection(int from, int to);
    vector<Node> getNodesExceptLayer(int layer);

    int checkIfLayerIsLast(int layer);
    static bool checkIfRoomForNode(int fromLayer, int toLayer);

    int createNode(float bias, Activation activation, int layer, int id);
    void addConnection(float weight, int from, int to);
    vector<Node> getNodesInLayer(int layer);

    vector<Connection> &getConnections();
    vector<Node> &getNodes();

    int predict(vector<float> &input);
    int forward();

    [[nodiscard]] float getFitness() const;
    void setFitness(float fitness);

    [[nodiscard]] vector<GameOverType> getGameOvers() const;
    void setGameOvers(const vector<GameOverType> &overs);

    [[nodiscard]] duration_t getTrainingTime() const;
    void setTrainingTime(duration_t time);

};


#endif //MINESWEEPERAI_GENOME_HPP
