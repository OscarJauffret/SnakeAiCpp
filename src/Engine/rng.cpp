//
// Created by oscar on 13/07/2024.
//

#include "headers/rng.hpp"

float RNG::get() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<float> dis(0.0, 1.0);
    return dis(gen);
}

float RNG::randomFloatBetween(float min, float max) {
    if (min > max) {
        throw std::invalid_argument("min should not be greater than max");
    } else if (min == max) {
        return min;
    }
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<float> dis(min, max);
    float random = dis(gen);
    return random;
}

int RNG::randomIntBetween(int min, int max) {
    if (min > max) {
        throw std::invalid_argument("min should not be greater than max");
    } else if (min == max) {
        return min;
    }
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dis(min, max);
    int random = dis(gen);
    return random;
}

bool RNG::proba(float probability) {
    return get() < probability;
}