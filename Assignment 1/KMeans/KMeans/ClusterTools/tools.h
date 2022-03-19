#pragma once
#include <vector>
#include <time.h>
#include <random>
#include <iostream>
#include <algorithm>
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
        std::uniform_int_distribution<size_t> distribution(range.x, range.y);
        return distribution(gen);
    }

    template <typename T>
    Vector2D<float> VMean(std::vector<Vector2D<T>> vecObjA, const Vector2D<T> vecB)
    {
        Vector2D<float> mean = {(float) vecB,(float) vecB};
        vecObjA.push_back(vecB);
        for_each(vecObjA.begin(), vecObjA.end(), [&mean](const Vector2D<size_t> item) {
            mean.x += (float)item.x;
            mean.y += (float)item.y;
        });

        mean.x /= 2;
        mean.y /= 2;

        return mean;
    }

    template <typename T>
	Vector2D<float> VMean(Vector2D<T> vecA, const Vector2D<T> vecB)
    {
        Vector2D<float> mean;
        mean.x = ((float)vecA.x + (float)vecB.x) / 2;
        mean.y = ((float)vecA.y + (float)vecB.y) / 2;

        return mean;
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