#include "tools.h"
#include <iostream>
bool CTools::KMeans::KMeans(std::vector<std::vector<MTools::Vector2D<size_t>>>* clusterPoints, std::vector<MTools::Vector2D<float>>* kClusterPoints)
{
	// clusterPoints should be zero first time through.
	std::vector<std::vector<MTools::Vector2D<size_t>>> cpyClusterPoints(*clusterPoints);

	std::cout << "Size of clusterPoints: " << clusterPoints->size() << std::endl;
	//for(size_t i = 0; i < c)

	std::cout << "New size of clusterPoints: " << clusterPoints->size() << std::endl;
	/* Whilst a condition is true - loop til change
		// assign dataPoints to clusterPoints (spreadsheet)
		// Calculate 
	*/

	return false;
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
	std::ranges::for_each(kClusterPoints.begin(), kClusterPoints.end(), [&comparisons, point](MTools::Vector2D<float> kPoint) {
		comparisons.push_back(VectorDistance(kPoint, point));
	});

	for(size_t i = 0; i < comparisons.size(); i++)
	{
		std::cout << comparisons[i] << std::endl;
	}
	return 1;

}