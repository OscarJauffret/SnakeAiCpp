//
// Created by oscar on 13/07/2024.
//

#ifndef MINESWEEPERAI_RNG_HPP
#define MINESWEEPERAI_RNG_HPP
#include <vector>
#include <random>
using namespace std;

class RNG {
public:
    static float get();
    static float randomFloatBetween(float min, float max);
    static int randomIntBetween(int min, int max);
    static bool proba(float probability);

    template<typename T> static T& pickRandom(std::vector<T> &vec) {
    int const index = randomIntBetween(0, vec.size() - 1);
    return vec[index];
}
};


#endif //MINESWEEPERAI_RNG_HPP
