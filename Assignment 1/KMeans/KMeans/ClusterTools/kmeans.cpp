#include "tools.h"

bool KMeans(std::vector<std::vector<MTools::Vector2D<size_t>>>* dataPoints, std::vector<MTools::Vector2D<float>> kClusterPoints)
{
	// loving the for_each function xd
	for_each(dataPoints->begin(), dataPoints->end(), Assignment);
	/* Whilst a condition is true - loop til change
		// assign dataPoints to clusterPoints (spreadsheet)
		// Calculate 
	*/

	return false;
}

int Assignment(MTools::Vector2D<size_t> point, std::vector<MTools::Vector2D<float>> kClusterPoints)
{
	// find the best cluster point

}