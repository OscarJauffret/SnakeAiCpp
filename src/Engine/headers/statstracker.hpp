//
// Created by oscar on 17/07/2024.
//

#ifndef SNAKEAI_STATSTRACKER_HPP
#define SNAKEAI_STATSTRACKER_HPP

#include "snakepart.hpp"
#include "../../config.hpp"
#include <utility>
#include <vector>

using namespace std;

struct StatsTracker {
    float fitness;
    vector<GameOverType> deathReasons;
    duration_t trainingTime;

    StatsTracker() : fitness(0), deathReasons(), trainingTime(0) {}

    void setFitness(float fit) {
        this->fitness = fit;
    }

    void setDeathReasons(vector<GameOverType> reasons) {
        this->deathReasons = std::move(reasons);
    }

    void setTrainingTime(duration_t time) {
        this->trainingTime = time;
    }
};
#endif //SNAKEAI_STATSTRACKER_HPP
