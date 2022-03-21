#include <iostream>
#include "ClusterTools/tools.h";
#include "Library/Functions.h"

namespace MetadataHandler
{
    void SetMetadata(std::vector<MTools::Vector2D<size_t>>* dataCluster)
    {
        for (size_t i = 0; i < dataCluster->size(); i++)
            dataCluster->at(i).metadata = Functions().TextInput("Enter student number for " + std::to_string(i) + ": ");
    }
}

int main(int argc, char** argv)
{
    std::vector<std::vector<MTools::Vector2D<size_t>>> dataCluster;

    // constrain to (rng.y * rng.y) / 2
    MTools::Vector2D<size_t> dataRange({1, 9});
    std::vector<MTools::Vector2D<size_t>> cluster = CTools::Generation::GenerateCluster(10, dataRange);
    MetadataHandler::SetMetadata(&cluster);
    dataCluster.push_back(cluster);

    Functions().ClearSystem();

    std::cout << "Data Cluster: " << std::endl;
	for_each(cluster.begin(), cluster.end(), [](MTools::Vector2D<size_t> obj) -> void { printf("student number: %s x: %li - y: %li\n", obj.metadata.c_str(), obj.x, obj.y); });

    // constrain k to less than cluster size / 2
    std::vector<MTools::Vector2D<float>> cogCluster = CTools::Generation::GenerateCOG(2, cluster);

    std::cout << std::endl << "COG Clusters: " << std::endl;
    for_each(cogCluster.begin(), cogCluster.end(), [] (MTools::Vector2D<float> obj) -> void { printf("x: %.2f - y: %.2f\n", obj.x, obj.y); });

    // Tested the VectorDistance function - Works
    //std::cout << MTools::VectorDistance(MTools::Vector2D<float>({2.5, 6.0}), {9, 5}) << std::endl;

    std::vector<MemoryTools::Memory> memory;
    bool bIncomplete = true;
    while(bIncomplete)
    {
        memory.push_back({ dataCluster, cogCluster });
        bIncomplete = CTools::KMeans::KMeans(&dataCluster, &cogCluster);
    }

    std::cout << "Memory: " << std::endl;
    for_each(memory.begin(), memory.end(), [] (const MemoryTools::Memory memoryItem) {
        for(size_t i = 0; i < memoryItem.cPoints.size(); i++)
        {
            printf("\t\tK: %li | X: %.2f | Y: %.2f\n", i, memoryItem.kPoints[i].x, memoryItem.kPoints[i].y);
            for(size_t j = 0; j < memoryItem.cPoints[i].size(); j++)
            {
               std::cout << "C: " << j << " | Student Number: " << memoryItem.cPoints[i][j].metadata << " | X: " << memoryItem.cPoints[i][j].x << " | Y: " << memoryItem.cPoints[i][j].y << std::endl;
            }
            std::cout << std::endl;
        }
    });

    std::cout << std::endl;

    return 0;
}