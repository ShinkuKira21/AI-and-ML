#include "coms.h"
#include "../../KMeans/ClusterTools/tools.h"

float XPlusY(float x, float y) {
	return x + y;
}

int RandomNumber()
{
	return (int)MTools::Randomise({ 1, 9 });
}

int XY(A xy)
{
	return xy.x + xy.y;
}