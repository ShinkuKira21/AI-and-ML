#pragma once
#include <vector>
#include <time.h>
#include <random>

// Math Tools
namespace MTools {
    struct Vector2D {
        size_t x, y;
    };

    // Reference: https://www.cplusplus.com/reference/random/
    inline size_t Randomize(Vector2D range)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> distribution(range.x, range.y);
        return distribution(gen);
    }
}

// KMeans - Cluster Tools
namespace CTools::KMeans {
    std::vector<MTools::Vector2D> KMeans();
}

namespace CTools::Generation {
    std::vector<MTools::Vector2D> GenerateCluster(const size_t nClusters, const MTools::Vector2D range);

    // Slightly different, checks that the CoG is not replacing a point
    std::vector<MTools::Vector2D> GenerateCOG(const size_t kSize, const std::vector<MTools::Vector2D> dataPoints);
}