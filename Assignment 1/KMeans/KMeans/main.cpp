#include "ClusterTools/tools.h"
#include "CVSTools/CVSTools.h"
#include "Library/Functions.h"
#include <iostream>
namespace MetadataHandler
{
    void SetMetadata(std::vector<MTools::Vector2D<size_t>>* dataCluster)
    {
        for (size_t i = 0; i < dataCluster->size(); i++)
            dataCluster->at(i).metadata = Functions().TextInput("Enter student number for " + std::to_string(i) + ": ");
    }

    MTools::Vector2D<size_t> SelectCRange()
    {
        // yeah this maybe a cheap way of doing it.
        int val; MTools::Vector2D<size_t> rng;
        bool bRecord = false, bError = false;
		while(!bRecord)
		{
            if(bError) std::cout << "Error: Range is less than zero!\n";
            val = (int)Functions().NumberInput("Enter range X (>=0): ");
            if (val < 0) bError = true;
            else bRecord = !bRecord;
            Functions().ClearSystem();
		}

        rng.x = (size_t)val;
        bRecord = !bRecord; bError = false;
        while(!bRecord)
        {
            if(bError) std::cout << "Error: Range should be more than " << rng.x << "!\n";
            val = (int)Functions().NumberInput("Enter range Y (>" + std::to_string(rng.x) + ") : ");
            if (val <= (int)rng.x) bError = true;
            else bRecord = !bRecord;
            Functions().ClearSystem();
        }

        rng.y = (size_t)val;
        return rng;
    }

    size_t SelectNClusters()
    {
        int val; bool bRecord = false, bError = false;
		while(!bRecord)
		{
            if(bError) std::cout << "Error: Number of clusters has to be higher than zero!" << std::endl;
            val = (int)Functions().NumberInput("Enter Number of Clusters (>0): ");
            if (val <= 0) bError = true;
            else bRecord = !bRecord;
            Functions().ClearSystem();
		}

        return (size_t)val;
    }

    size_t SelectNKClusters(size_t ySize)
    {
        int val; bool bRecord = false, bError = false;
		while(!bRecord)
		{
            if(bError) std::cout << "Error: Number of clusters has to be lower than " << ySize << "!" << std::endl;
            val = (int)Functions().NumberInput("Enter Number of K Clusters (<"+std::to_string(ySize)+"): ");
            if (val >= (int)ySize) bError = true;
            else bRecord = !bRecord;
		}

        return (size_t)val;
    }
}

int main(int argc, char** argv)
{   
    std::vector<std::vector<MTools::Vector2D<size_t>>> dataCluster;
    // constrain to (rng.y * rng.y) / 2
    MTools::Vector2D<size_t> dataRange(MetadataHandler::SelectCRange());
    std::vector<MTools::Vector2D<size_t>> cluster = CTools::Generation::GenerateCluster(MetadataHandler::SelectNClusters(), dataRange);
    MetadataHandler::SetMetadata(&cluster);
    dataCluster.push_back(cluster);

    Functions().ClearSystem();

    std::cout << "Data Cluster: " << std::endl;
	for_each(cluster.begin(), cluster.end(), [](MTools::Vector2D<size_t> obj) -> void { printf("student number: %s x: %li - y: %li\n", obj.metadata.c_str(), obj.x, obj.y); });
    // constrain k to less than cluster size / 2
    std::vector<MTools::Vector2D<float>> cogCluster = CTools::Generation::GenerateCOG(MetadataHandler::SelectNKClusters(dataRange.y), cluster);

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