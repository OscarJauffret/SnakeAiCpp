//
// Created by oscar on 13/07/2024.
//

#ifndef SNAKEAI_CONFIG_HPP
#define SNAKEAI_CONFIG_HPP

#include <SFML/Graphics.hpp>
#include <thread>

#define M_PI 3.14159265358979323846f
#define M_PHI 1.618033988749895f

using namespace sf;
using namespace std;

using duration_t = unsigned long long int;

enum class Mode {
    Manual,
    Ai
};

namespace config {
    namespace window {
        constexpr unsigned int width = 1920;
        constexpr unsigned int height = 1080;
        constexpr unsigned int fps = 60;
        const string title = "Snake AI";
        constexpr int style = sf::Style::Fullscreen;
    }

    namespace assets {
        const string fontPath = "../src/assets/Roboto-Regular.ttf";
    }

    namespace layout {
        namespace net {
            constexpr float width = 500.0f;
            constexpr float height = 500.0f;
            constexpr float originX = 10.0f;
            constexpr float originY = window::height - height - 10.0f;
        }

        namespace snake {
            constexpr int width = 800;
            constexpr int height = 500;
            constexpr int originX = window::width / 2 - width / 2;
            constexpr int originY = 10;
        }

        namespace stats {
            constexpr float width = 500.0f;
            constexpr float height = 300.0f;
            constexpr float originX = net::originX + net::width + 10.0f;
            constexpr float originY = window::height - height - 10.0f;
        }

        namespace traininginfo {
            constexpr float width = 150.0f;
            constexpr float height = 100.0f;
            constexpr float originX = 10.0f;
            constexpr float originY = 10.0f;
            constexpr int generationTextSize = 20;
            constexpr int timeTextSize = 10;
        }
    }

    namespace netrender {
        constexpr float nodeRadius = 10.0f;
        constexpr float nodeOutlineThickness = 3.0f;
        constexpr float maximumConnectionThickness = 10.0f;
        constexpr float minimumConnectionThickness = 0.0f;
    }

    namespace  game {
        constexpr float accelerationFactor = 50.0f;
        constexpr float maxGames = 10;
        constexpr int maxMovesWithoutFood = 100;
        const Vector2i canvasSize = {layout::snake::width, layout::snake::height};
        constexpr int cellSize = 20;
        const Vector2i gridSize = {canvasSize.x / cellSize, canvasSize.y / cellSize};
        const Vector2i snakeStartPos = {gridSize.x / 2, gridSize.y / 2};
        constexpr int startLength = 3;
    }

    namespace colors {
        const Color bgColor = Color(80, 80, 80);
        const Color darkerBgColor = Color(50, 50, 50);
        const Color snakeColor = Color(0, 255, 0);
        const Color foodColor = Color(255, 0, 0);
        const Color textColor = Color(255, 255, 255);

        namespace buttons {
            const Color normal = Color(66, 108, 245);
            const Color outline = Color(255, 255, 255);
        }

        namespace net {
            const Color nodeColor = Color(24, 49, 79);
            const Color nodeOutlineColor = Color(255, 248, 243);
            const Color connectionColor = Color(255, 248, 243);
        }

        namespace stats {
            const Color starvationColor = Color(50, 168, 149);
            const Color collisionColor = Color(227, 138, 75);
            const Color suicideColor = Color(136, 75, 227);
            const Color wonColor = Color(107, 173, 227);
        }

        namespace traininginfo {
            const Color outlineColor = Color(109, 182, 242);
        }
    }

    namespace genetic {
        const size_t numThreads = thread::hardware_concurrency();
        const size_t populationSize = 1000;
        constexpr float elitismRate = 0.25f;
        constexpr int numberOfGamesPerAgent = 5;

        namespace mut {
            constexpr int numMutations = 4;
            constexpr float newNodeProba = 0.2f;
            constexpr float newConnectionProba = 0.8f;
            constexpr float weightAndBiasMutRate = 0.25f;
            constexpr float weightMutProportion = 0.5f;
            constexpr float newValueProba = 0.2f;
            constexpr float smallWeightRate = 0.01f;
            constexpr float addValueProba = 0.25f;
        }
    }

    namespace net {
        constexpr int inputSize = 11;
        constexpr int outputSize = 3;
    }
}

#endif //SNAKEAI_CONFIG_HPP