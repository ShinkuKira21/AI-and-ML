#include "tools.h"
#include <iostream>
#include <algorithm>
std::vector<MTools::Vector2D> CTools::Generation::GenerateCluster(const size_t nDataPoints, const MTools::Vector2D rng)
{  
    std::vector<MTools::Vector2D> dataPoints;

    for (size_t i = 0; i < nDataPoints; i++)
    {
        MTools::Vector2D rndPoints({MTools::Randomize(rng), MTools::Randomize(rng)});
        dataPoints.push_back({MTools::Randomize(rng), MTools::Randomize(rng)});

        // check that the random points are unique.
        bool found = false;
        find_if(dataPoints.begin(), dataPoints.end(), [&found, rndPoints](const MTools::Vector2D point)-> bool {
            if(point.x == rndPoints.x && point.y == rndPoints.y) found = true;
            return false;
        });

        if(!found ) dataPoints.push_back(rndPoints);
        else i--;
    }

    return dataPoints;
}

std::vector<MTools::Vector2D> CTools::Generation::GenerateCOG(const size_t kSize, const std::vector<MTools::Vector2D> dataPoints)
{
    const size_t max = dataPoints.size() - 1;
    std::vector<MTools::Vector2D> kPoints;
    for(size_t i = 0; i < kSize; i++)
    {
        // after some extensive research, it was found that a random CoG (or K) does not have to correspond with a dataPoint but can appear in the Median of the dataPoints. Perhaps a method to select a more random selection is having a boolean variable that if random as true (from a probabilty of 5 values out of 10) so that the software favors picking existing dataPoints over selecting random median positions could create more reliable results. For now, the program will only select a random point from the dataPoints vector.
        const MTools::Vector2D rndPoints = dataPoints.at(MTools::Randomize({0, max}));

        // makes sure to get unique kPoints
        bool found = false;
        
        find_if(kPoints.begin(), kPoints.end(), [&found, rndPoints](const MTools::Vector2D point)->bool {
            if(point.x == rndPoints.x && point.y == rndPoints.y) found = true;
            return false;
        });

        if(!found) kPoints.push_back(rndPoints);
        else i--;
    }
    return kPoints;
}