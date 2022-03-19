#include <iostream>
#include <algorithm>
#include "ClusterTools/tools.h"

int main(int argc, char** argv)
{
    // constrain to (rng.y * rng.y) / 2  
    MTools::Vector2D<size_t> dataRange({1, 9});
    std::vector<MTools::Vector2D<size_t>> cluster = CTools::Generation::GenerateCluster(4, dataRange);

    std::cout << "Data Cluster: " << std::endl;
    for_each(cluster.begin(), cluster.end(), [] (MTools::Vector2D<size_t> obj) -> void { printf("x: %li - y: %li\n", obj.x, obj.y); });

    // constrain k to less than 
    std::vector<MTools::Vector2D<float>> cogCluster = CTools::Generation::GenerateCOG(2, cluster);

    std::cout << "COG Clusters: " << std::endl;
    for_each(cogCluster.begin(), cogCluster.end(), [] (MTools::Vector2D<float> obj) -> void { printf("x: %.2f - y: %.2f\n", obj.x, obj.y); });

    std::cout << std::endl;

    return 0;
}