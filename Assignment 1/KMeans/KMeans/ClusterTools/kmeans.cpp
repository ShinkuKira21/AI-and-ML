#include "tools.h"
#include <iostream>
bool CTools::KMeans::KMeans(std::vector<std::vector<MTools::Vector2D<size_t>>>* clusterPoints, std::vector<MTools::Vector2D<float>>* kClusterPoints)
{
	// clusterPoints should be zero first time through.
	std::vector<std::vector<MTools::Vector2D<size_t>>> cpyClusterPoints(*clusterPoints);

	std::cout << "Size of clusterPoints: " << clusterPoints->size() << std::endl;
	std::ranges::for_each(cpyClusterPoints.begin(), cpyClusterPoints.end(), [clusterPoints, kClusterPoints] (const std::vector<MTools::Vector2D<size_t>> clusterPoint)
	{
		std::ranges::for_each(clusterPoint.begin(), clusterPoint.end(), [clusterPoints, kClusterPoints](const MTools::Vector2D<size_t> dataPoint)
		{
			int selector = Assignment(dataPoint, *kClusterPoints);

		});
	});

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
	std::vector<std::vector<MTools::Vector2D<float>> comparisons;
	std::ranges::for_each(kClusterPoints.begin(), kClusterPoints.end(), [comparisons](const MTools::Vector2D<float> kPoint))
	{

	});
	return 1;

}