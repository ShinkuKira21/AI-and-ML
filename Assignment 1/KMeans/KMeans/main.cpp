#include <iostream>

#include "ClusterTools/tools.h"

int main(int argc, char** argv)
{
    std::vector<std::vector<MTools::Vector2D<size_t>>> dataCluster;

    // constrain to (rng.y * rng.y) / 2
    MTools::Vector2D<size_t> dataRange({1, 9});
    std::vector<MTools::Vector2D<size_t>> cluster = CTools::Generation::GenerateCluster(5, dataRange);
    dataCluster.push_back(cluster);

    std::cout << "Data Cluster: " << std::endl;
    for_each(cluster.begin(), cluster.end(), [] (MTools::Vector2D<size_t> obj) -> void { printf("x: %li - y: %li\n", obj.x, obj.y); });

    // constrain k to less than cluster size / 2
    std::vector<MTools::Vector2D<float>> cogCluster = CTools::Generation::GenerateCOG(3, cluster);

    std::cout << "COG Clusters: " << std::endl;
    for_each(cogCluster.begin(), cogCluster.end(), [] (MTools::Vector2D<float> obj) -> void { printf("x: %.2f - y: %.2f\n", obj.x, obj.y); });

    // Tested the VectorDistance function - Works
    //std::cout << MTools::VectorDistance(MTools::Vector2D<float>({2.5, 6.0}), {9, 5}) << std::endl;

    while(CTools::KMeans::KMeans(&dataCluster, &cogCluster))
    {
        
    }

    std::cout << std::endl;

    return 0;
}