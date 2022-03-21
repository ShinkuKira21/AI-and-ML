#include "tools.h"
#include <thread>

std::vector<MTools::Vector2D<size_t>> CTools::Generation::GenerateCluster(const size_t nDataPoints, const MTools::Vector2D<size_t> rng)
{  
    std::vector<MTools::Vector2D<size_t>> dataPoints;

    for (size_t i = 0; i < nDataPoints; i++)
    {
        
        size_t points[2];

        // Program runs faster with the threads to do the Randomise
        std::thread* thread[2];

        for (size_t i = 0; i < 2; i++)
        {
            thread[i] = new std::thread([&points, i, rng]()
            { points[i] = Randomise(rng); });
        }

        for(std::thread* th : thread)
        {
            th->join();
            delete th;
        }

        MTools::Vector2D<size_t> rndPoints({points[0], points[1]});

        // check that the random points are unique.
        
        const bool found = find_if(dataPoints.begin(), dataPoints.end(), [rndPoints](const MTools::Vector2D<size_t> point)-> bool {
            if(point.x == rndPoints.x && point.y == rndPoints.y) return true;
            return false;
        }) != dataPoints.end();

        if(!found) dataPoints.push_back(rndPoints);
        else i--;
    }

    return dataPoints;
}

std::vector<MTools::Vector2D<float>> CTools::Generation::GenerateCOG(const size_t kSize, const std::vector<MTools::Vector2D<size_t>> dataPoints)
{
    const size_t max = dataPoints.size() - 1;
    std::vector<MTools::Vector2D<float>> kPoints;
    for(size_t i = 0; i < kSize; i++)
    {
        // This is not neccessary. However, if the K is chosen randomly, then it helps create a more random generation.
        bool bLogicChange = false;
        const size_t chance = MTools::Randomise({10, 20});
        if (chance < 15) bLogicChange = true;

    	MTools::Vector2D<size_t> rndPoints = dataPoints.at(MTools::Randomise({0, max}));

        // makes sure to get unique kPoints
        bool found = find_if(kPoints.begin(), kPoints.end(), [rndPoints](const MTools::Vector2D<float> point)->bool {
            if(point.x == rndPoints.x && point.y == rndPoints.y) return true;
            return false;
        }) != kPoints.end();

        if(!found) {
            if(bLogicChange) {
                MTools::Vector2D<size_t> rndPoints2 = dataPoints.at(MTools::Randomise({ 0, max }));
                kPoints.push_back(VMean(rndPoints, rndPoints2));
            }
            else kPoints.push_back({(float)rndPoints.x, (float)rndPoints.y});
        }
        else i--;
    }
    return kPoints;
}