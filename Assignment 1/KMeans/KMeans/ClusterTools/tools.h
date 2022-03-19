#pragma once
#include <vector>
#include <time.h>
#include <random>

// Math Tools
namespace MTools {
    template <typename T>
    struct Vector2D {
        T x, y;
    };

    // Reference: https://www.cplusplus.com/reference/random/
    inline size_t Randomize(Vector2D<size_t> range)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        const std::uniform_int_distribution distribution(range.x, range.y);
        return distribution(gen);
    }
}

// KMeans - Cluster Tools
namespace CTools::KMeans {
    std::vector<MTools::Vector2D<float>> KMeans();
}

namespace CTools::Generation {
    std::vector<MTools::Vector2D<size_t>> GenerateCluster(const size_t nClusters, const MTools::Vector2D<size_t> range);

    // Slightly different, checks that the CoG is not replacing a point
    std::vector<MTools::Vector2D<float>> GenerateCOG(const size_t kSize, const std::vector<MTools::Vector2D<size_t>> dataPoints);
}