#include "tools.h"

std::vector<MTools::Vector2D<size_t>> CTools::Generation::GenerateCluster(const size_t nDataPoints, const MTools::Vector2D<size_t> rng)
{  
    std::vector<MTools::Vector2D<size_t>> dataPoints;

    for (size_t i = 0; i < nDataPoints; i++)
    {
        MTools::Vector2D<size_t> rndPoints({MTools::Randomize(rng), MTools::Randomize(rng)});
        dataPoints.push_back({MTools::Randomize(rng), MTools::Randomize(rng)});

        // check that the random points are unique.
        bool found = false;
        find_if(dataPoints.begin(), dataPoints.end(), [&found, rndPoints](const MTools::Vector2D<size_t> point)-> bool {
            if(point.x == rndPoints.x && point.y == rndPoints.y) found = true;
            return false;
        });

        if(!found ) dataPoints.push_back(rndPoints);
        else i--;
    }

    return dataPoints;
}

std::vector<MTools::Vector2D<float>> CTools::Generation::GenerateCOG(const size_t kSize, const std::vector<MTools::Vector2D<size_t>> dataPoints)
{
    // This is not neccessary. However, if the K is chosen randomly, then it helps create a more random generation.
    bool bLogicChange = true;
    const size_t chance = MTools::Randomize({10, 20});
    if(chance == 10 || chance == 15 || chance == 20) bLogicChange = true;

    const size_t max = dataPoints.size() - 1;
    std::vector<MTools::Vector2D<float>> kPoints;
    for(size_t i = 0; i < kSize; i++)
    {
        const MTools::Vector2D<size_t> rndPoints = dataPoints.at(MTools::Randomize({0, max}));

        // makes sure to get unique kPoints
        bool found = false;
        
        find_if(kPoints.begin(), kPoints.end(), [&found, rndPoints](const MTools::Vector2D<float> point)->bool {
            if(point.x == rndPoints.x && point.y == rndPoints.y) found = true;
            return false;
        });

        if(!found) {
            if(bLogicChange) {
                kPoints.push_back(MTools::VMean(rndPoints, MTools::Randomize({0, max})));
            }
            else kPoints.push_back({(float)rndPoints.x, (float)rndPoints.y});
        }
        else i--;
    }
    return kPoints;
}