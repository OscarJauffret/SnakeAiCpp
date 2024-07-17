//
// Created by oscar on 13/07/2024.
//

#ifndef MINESWEEPERAI_ACTIVATION_HPP
#define MINESWEEPERAI_ACTIVATION_HPP
#include <cmath>

using ActivationPtr = double (*)(double);

enum class Activation {
    None,
    Relu,
    Sigmoid,
    Tanh,
};

struct ActivationFunction {

    static ActivationPtr getFunction(Activation activation) {
        switch (activation) {
            case Activation::None:
                return none;
            case Activation::Relu:
                return relu;
            case Activation::Sigmoid:
                return sigmoid;
            case Activation::Tanh:
                return tanh;
            default:
                return none;
        }
    }

    static double none(double x) {
        return x;
    }

    static double relu(double x) {
        return (x + std::abs(x)) / 2;
    }

    static double sigmoid(double x) {
        return 1 / (1 + std::exp(-x));
    }

    static double tanh(double x) {
        return std::tanh(x);
    }
};

#endif //MINESWEEPERAI_ACTIVATION_HPP
