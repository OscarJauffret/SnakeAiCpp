//
// Created by oscar on 17/07/2024.
//

#ifndef SNAKEAI_TRAININGINFO_HPP
#define SNAKEAI_TRAININGINFO_HPP
#include "../../config.hpp"

/**
 * Struct that contains the information of the training
 * generations: number of generations
 * realTrainingTime: real time spent training
 * virtualTrainingTime: virtual time spent training
 * showBest: if the best snake should be shown
 */
struct TrainingInfo {
    int generations;
    duration_t realTrainingTime;
    duration_t virtualTrainingTime;
    bool showBest;

    TrainingInfo(int generations, duration_t realTrainingTime, duration_t virtualTrainingTime, bool showBest):
    generations(generations), realTrainingTime(realTrainingTime), virtualTrainingTime(virtualTrainingTime), showBest(showBest) {}
};

#endif //SNAKEAI_TRAININGINFO_HPP
