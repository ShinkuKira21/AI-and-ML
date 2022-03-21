#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <math.h>

// Math Tools
namespace MTools {
    template <typename T>
    struct Vector2D {
        std::string metadata;
        T x, y;

        Vector2D() {}

        Vector2D(T aX, T aY)
        {
            x = aX;
            y = aY;
        }
    };

    // Reference: https://www.cplusplus.com/reference/random/
    inline size_t Randomise(Vector2D<size_t> range)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> distribution(range.x, range.y);
        return distribution(gen);
    }

    template <typename T, typename S>
    Vector2D<float> VMean(std::vector<Vector2D<T>> vecObjA, const Vector2D<S> vecB)
    {
        Vector2D<float> mean = {(float) vecB.x,(float) vecB.y};
       
        for_each(vecObjA.begin(), vecObjA.end(), [&mean](const Vector2D<size_t> item) {
            mean.x += (float)item.x;
            mean.y += (float)item.y;
        });

        mean.x /= vecObjA.size()+1;
        mean.y /= vecObjA.size()+1;

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

    template <typename T, typename S>
    float VectorDistance(Vector2D<T> vecA, Vector2D<S> vecB)
    { return (float)sqrt(pow((float)vecA.x - (float)vecB.x, 2) + pow((float)vecA.y - (float)vecB.y, 2)); }
}

namespace MemoryTools
{
    struct Memory
    {
        std::vector<std::vector<MTools::Vector2D<size_t>>> cPoints;
        std::vector<MTools::Vector2D<float>> kPoints;
    };
}

// KMeans - Cluster Tools
namespace CTools::KMeans {
    bool KMeans(std::vector<std::vector<MTools::Vector2D<size_t>>>* clusterPoints, std::vector<MTools::Vector2D<float>>* kClusterPoints);

    int Assignment(MTools::Vector2D<size_t> point, std::vector<MTools::Vector2D<float>> kClusterPoints);

    void Recalculate(const std::vector<std::vector<MTools::Vector2D<size_t>>> clusterPoints, std::vector<MTools::Vector2D<float>>* kClusterPoints);

    bool CheckChange(const std::vector<std::vector<MTools::Vector2D<size_t>>> memory, const std::vector<std::vector<MTools::Vector2D<size_t>>> newClusters);
}

namespace CTools::Generation {
    std::vector<MTools::Vector2D<size_t>> GenerateCluster(const size_t nClusters, const MTools::Vector2D<size_t> range);
    // Slightly different, checks that the CoG is not replacing a point
    std::vector<MTools::Vector2D<float>> GenerateCOG(const size_t kSize, const std::vector<MTools::Vector2D<size_t>> dataPoints);
}