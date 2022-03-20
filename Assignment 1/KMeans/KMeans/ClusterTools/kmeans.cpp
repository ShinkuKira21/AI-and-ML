#include "tools.h"
#include <iostream>
bool CTools::KMeans::KMeans(std::vector<std::vector<MTools::Vector2D<size_t>>>* clusterPoints, std::vector<MTools::Vector2D<float>>* kClusterPoints)
{
	// clusterPoints should be zero first time through.

	/* Whilst a condition is true - loop til change
		// assign dataPoints to clusterPoints (spreadsheet)
		// Calculate 
	*/
	std::vector<std::vector<MTools::Vector2D<size_t>>> memory(*clusterPoints);

	// Clear memory from clusterPoints (initiating kClusterPoints structure and size)
	clusterPoints->clear();
	clusterPoints->resize(kClusterPoints->size());

	for(size_t i = 0; i < memory.size(); i++)
	{
		for(size_t j = 0; j < memory.at(i).size(); j++)
		{
			int sel = Assignment(memory.at(i).at(j), *kClusterPoints);
			
			// safety check
			if(sel == -1) return false;
			
			clusterPoints->at(sel).push_back(memory.at(i).at(j));
		}
	}

	if(!(CheckChange(memory, *clusterPoints))) return false;

	// Recalculate k cluster points
	Recalculate(*clusterPoints, *kClusterPoints);

	return true;
}

int CTools::KMeans::Assignment(MTools::Vector2D<size_t> point, std::vector<MTools::Vector2D<float>> kClusterPoints)
{
	// find the best cluster point
	/* TODO:
	 * loop through each point and find the lowest cluster point
	*/
	// point check with all points
	std::vector<float> comparisons;

	// fix the race conditions
	for_each(kClusterPoints.begin(), kClusterPoints.end(), [&comparisons, point](MTools::Vector2D<float> kPoint) {
		comparisons.push_back(VectorDistance(kPoint, point));
	});

	// returns as soon as it finds the first less than.
	// revised: checks all paths to find the closest k cluster
	size_t bestIndex;
	float smallestFloat = 256;
	for(size_t i = 0; i < comparisons.size(); i++)
	{ 
		for(size_t j = 0; j < comparisons.size(); j++)
		{
			if(comparisons.at(i) < smallestFloat && comparisons.at(i) < comparisons.at(j))
			{
				std::cout << "Comparisons: \n";
				printf("i: %li | j: %li | %.2f < %.2f: \n", i, j, comparisons.at(i), comparisons.at(j));
				bestIndex = i;
				smallestFloat = comparisons.at(i);
			}
				
		}
	}

	return bestIndex;
}

std::vector<MTools::Vector2D<float>> CTools::KMeans::Recalculate(const std::vector<std::vector<MTools::Vector2D<size_t>>> clusterPoints, const std::vector<MTools::Vector2D<float>> kClusterPoints)
{
	for(size_t i = 0; i < clusterPoints.size(); i++)
	{
		std::cout << "I: " << i << " | ";
		for(size_t j = 0; j < clusterPoints[i].size(); j++)
		{
			printf("New CP X: %li, Y: %li\t", clusterPoints.at(i).at(j).x, clusterPoints.at(i).at(j).y);
		}

		std::cout << std::endl;
	}


	std::cout << "Recalculate Cluster Points:\n";
	for(size_t i = 0; i < kClusterPoints.size(); i++)
	{
		MTools::Vector2D<float> test = VMean(clusterPoints.at(i), kClusterPoints.at(i));

		printf("X: %.2f, Y: %.2f\n", test.x, test.y);
	}

	return kClusterPoints;
}

bool CTools::KMeans::CheckChange(std::vector<std::vector<MTools::Vector2D<size_t>>> memory, std::vector<std::vector<MTools::Vector2D<size_t>>> newClusters)
{
	// first check if sizes don't match (remember the first memory has no sorting and is registered with index 0)
	if(memory.size() != newClusters.size()) return true;

	// second check if memory is the same as newClusters
	// memory outer size should be same as newClusters size at this point

	bool bChanged = false;
	for(size_t i = 0; i < memory.size(); i++)
		for(size_t j = 0; j < memory.at(i).size(); j++)
			for(size_t k = 0; k < newClusters.at(i).size(); k++)
				if(&memory[i][j] == &newClusters[i][j]) return false;

	return bChanged;
}