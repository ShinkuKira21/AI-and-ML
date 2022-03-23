#include "ClusterTools/tools.h"
#include "CVSTools/CVSTools.h"
#include "Library/Functions.h"

namespace MetadataHandler
{
    void SetMetadata(std::vector<MTools::Vector2D<size_t>>* dataCluster)
    {
        for (size_t i = 0; i < dataCluster->size(); i++)
            dataCluster->at(i).metadata = Functions().TextInput("Enter student number for " + std::to_string(i) + ": ");
    }

    MTools::Vector2D<size_t> SelectRange(bool bConstraint = false)
    {
        // yeah this maybe a cheap way of doing it.
        if(bConstraint == true)
            std::cout << "Error: Range is less than zero, please try again.\n"; 

        int rng = (int)Functions().NumberInput("Enter range (0 => N): ");
        if(rng < 0) rng = SelectRange(true).x;
        if(bConstraint) return {(size_t)rng, 0};
        return {(size_t)rng, SelectRange().y};
    }
}

int main(int argc, char** argv)
{
    MTools::Vector2D<size_t> v2d = MetadataHandler::SelectRange();
    std::cout << v2d.x << "<XY>" << v2d.y << std::endl;
    std::vector<std::vector<MTools::Vector2D<size_t>>> dataCluster;
    
    // constrain to (rng.y * rng.y) / 2
    MTools::Vector2D<size_t> dataRange({1, 9});
    std::vector<MTools::Vector2D<size_t>> cluster = CTools::Generation::GenerateCluster(2, dataRange);
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

    // Matlab Data Visualisation //
    // Create CVS for COGs
    CVSTools::CVSProperties* properties = new CVSTools::CVSProperties();
    properties->col = 4;
    properties->headings = new std::string[4] {"D", "K", "X", "Y"};
    CVSTools::CVSHandler* cvs = new CVSTools::CVSHandler(properties, {"../KMeansMatlab/cvs/", "KCluster"});
    
    for(size_t i = 0; i < memory.size(); i++) 
        for(size_t j = 0; j < memory[i].cPoints.size(); j++)
        {
            cvs->CVSParser(0, std::to_string(i).c_str());
            cvs->CVSParser(1, std::to_string(j).c_str());
            cvs->CVSParser(2, std::to_string(memory[i].kPoints[j].x).c_str());
            cvs->CVSParser(3, std::to_string(memory[i].kPoints[j].y).c_str());
        }
    cvs->CVSStart();
    delete cvs;
    std::cout << "Generating KCluster Data Files for Matlab..." << std::endl;

    // Create CVS for ClusterPoints
    properties = new CVSTools::CVSProperties();
    properties->col = 4;
    properties->headings = new std::string[4] {"C", "Student Number", "X", "Y"};

    cvs = new CVSTools::CVSHandler(properties, {"../KMeansMatlab/cvs/", "Cluster"});
    
    for(size_t i = 0; i < memory.size(); i++) 
        for(size_t j = 0; j < memory[i].cPoints.size(); j++)
        {
            for(size_t k = 0; k < memory[i].cPoints[j].size(); k++)
            {
                cvs->CVSParser(0, std::to_string(j).c_str());
                cvs->CVSParser(1, memory[i].cPoints[j][k].metadata.c_str());
                cvs->CVSParser(2, std::to_string(memory[i].cPoints[j][k].x).c_str());
                cvs->CVSParser(3, std::to_string(memory[i].cPoints[j][k].y).c_str());
            }
            
        }
    cvs->CVSStart();
    delete cvs;
    std::cout << "Generated Necessary Data Files for Matlab:" << std::endl << "Go to the KMeansMatlab folder and open KMeans Matlab application";

    std::cout << std::endl;

    return 0;
}