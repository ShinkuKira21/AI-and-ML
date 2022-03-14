#include "DFS.h"

void DepthFirstSearch::AllPathways(FileManager::Config config)
{
	bool bStart = false;

	for (size_t i = 0; i < config.height; i++)
		for (size_t j = 0; j < config.width; j++)
		{
			if (config.file[config.width * i + j] == 'S')
			{
				std::cout << "Started|";
				bStart = !bStart;
			}

			if (config.file[config.width * i + j] == 'F')
			{
				std::cout << "Finished\n";
				bStart = !bStart;
			}

			if (bStart)
			{
				if (config.file[config.width * i + j] == '*')
					std::cout << "Wall|";

				if (config.file[config.width * i + j] == ' ')
					std::cout << "Corridor|";

				if (config.file[config.width * i + j] > 64 && config.file[config.width * i + j] < 91 && config.file[config.width * i + j] != 83)
					std::cout << "Object|";
			}
		}
}

DepthFirstSearch::Directions DepthFirstSearch::GetDirectional(Directions currentDirection)
{
	switch (currentDirection)
	{
		case ERight :
			return EHorizontal;

		case ELeft :
			return EHorizontal;

		default:
			return EVertical;
	}
}


DepthFirstSearch::Directions DepthFirstSearch::ChangeDirection(Directions currentDirection)
{
	// The order is left first, if wall, then change to right, if right and wall, vertical is triggered.
	switch (currentDirection)
	{
		case ELeft:
			return ERight;

		// Right
		case ERight:
			return EVertical;

		// Left is Default
		default:
			return ELeft;
	}
}

StackController::Coordinates DepthFirstSearch::Search(FileManager::Config config, StackController::Coordinates cPosition, Directions cDirection, bool bSpotCheck)
{
	// There maybe a better way of doing this...
	if(cDirection != EVertical)
	{
		// Left
		size_t i = cPosition.x;
		if (i < config.height && (cDirection == ELeft || cDirection == EHorizontal))
			for (size_t j = cPosition.y - 1; j != std::string::npos; j--)
			{
				// enables the function to check right
				if (config.file[config.width * i + j] == 42)
					break;

				if (config.file[config.width * i + j] != 32)
					return { cDirection, config.file[config.width * i + j], i, j };
			}
				
		// Change Direction
		// Right
		if(i < config.height && (cDirection == ERight || cDirection == EHorizontal))
			for (size_t j = cPosition.y + 1; j < config.width; j++)
			{
				if (config.file[config.width * i + j] == 42)
					break;

				if (config.file[config.width * i + j] != 32)
					return { cDirection, config.file[config.width * i + j], i, j };
			}
	}
	else
	{
		// Change Direction
		// Right

		// Find next way up
		// Change Direction
		// Find next way down

		// Check up and down from left direction
		Directions lastVDirection = EVertical; StackController::Coordinates deepSearch;

		bool bHoldYRowP1 = false, bHoldYRowP2 = false;
		
		if (GetDirectional(cPosition.pLastDirection) != EHorizontal)
		{
			bHoldYRowP1 = !bHoldYRowP1; // P1 != P2
			if (!bSpotCheck) lastVDirection = cPosition.pLastDirection;
			else bHoldYRowP2 = !bHoldYRowP2;
		}
		
		size_t i = cPosition.x;
		if (i < config.height)
			for (size_t j = cPosition.y, k = 0; j != std::string::npos && k < 1; j--)
			{
				// shows last direction vertically
				//
				// locks the y-axis loop.
				if (lastVDirection != EVertical && bHoldYRowP1 == bHoldYRowP2)
				{ j++; k++; }
				else if (config.file[config.width * i + j] == 42) {
					if (lastVDirection == EUp) return {};
					break;
				}

				// check top
				if ((lastVDirection != EDown) && i > 0 && config.file[config.width * (i - 1) + j] == 32)
				{
					k = 0;
					if ((cPosition = Search(config, { lastVDirection, 32, i - 1, j }, EHorizontal)).node != '\0')
					{
						cPosition.pLastDirection = lastVDirection;
						return cPosition;
					}
						

					if (i - 1 != std::string::npos && config.file[config.width * (i - 1) + j] != 42)
					{
						i--;
						if (bHoldYRowP1 != bHoldYRowP2) bHoldYRowP2 = !bHoldYRowP2;
						if (config.file[config.width * (i - 1) + j] == 42)
							if ((deepSearch = Search(config, { lastVDirection, 32, i, j }, EVertical)).node != 32) return deepSearch;
							
					}
					lastVDirection = EUp;
				}

				// check bottom
				if (lastVDirection != EUp && i + 1 < config.height && config.file[config.width * (i + 1) + j] == 32)
				{
					k = 0;
					if ((cPosition = Search(config, { lastVDirection, 32, i + 1, j }, EHorizontal)).node != '\0')
					{
						cPosition.pLastDirection = lastVDirection;
						return cPosition;
					}
						

					if (i + 1 < config.height && config.file[config.width * (i + 1) + j] != 42)
					{
						i++;
						if(bHoldYRowP1 != bHoldYRowP2) bHoldYRowP2 = !bHoldYRowP2;
						if (config.file[config.width * (i + 1) + j] == 42)
							if ((deepSearch = Search(config, { lastVDirection, 32, i, j }, EVertical)).node != 32) return deepSearch;
					}
					lastVDirection = EDown;
					
				}

				if (lastVDirection == EUp && config.file[config.width * (i - 1) + j] != 42 && config.file[config.width * (i - 1) + j] != 32)
					return { lastVDirection, config.file[config.width * (i - 1) + j], i - 1, j };
				if (lastVDirection == EDown && config.file[config.width * (i + 1) + j] != 42 && config.file[config.width * (i + 1) + j] != 32) return { lastVDirection, config.file[config.width * (i + 1) + j], i + 1, j };
			}

		// Check up and down from right direction
		lastVDirection = EVertical;
		if (GetDirectional(cPosition.pLastDirection) != EHorizontal)
			lastVDirection = cPosition.pLastDirection; // this should help

		i = cPosition.x;

		if (i < config.height)
			for (size_t j = cPosition.y, k = 0; j < config.width && k < 1; j++)
			{
				// locks the y-axis loop.
				// this used to be lastVDirection != EVertical
				// However, when lastVDirection is set as cPosition.pLastDirection
				// it will do it too early.
				if (lastVDirection != EVertical && bHoldYRowP1 == bHoldYRowP2) 
				{ j--; k++; }

				// check top
				if (lastVDirection != EDown && i > 0 && config.file[config.width * (i - 1) + j] == 32)
				{
					k = 0;
					if ((cPosition = Search(config, { lastVDirection, 32, i - 1, j }, EHorizontal)).node != '\0')
					{
						cPosition.pLastDirection = lastVDirection;
						return cPosition;
					}
						

					if (i - 1 != std::string::npos && config.file[config.width * (i - 1) + j] != 42)
					{
						i--;
						if (bHoldYRowP1 != bHoldYRowP2) bHoldYRowP2 = !bHoldYRowP2;
						if (config.file[config.width * (i + 1) + j] == 42)
							if ((deepSearch = Search(config, { lastVDirection, 32, i, j }, EVertical)).node != 32) return deepSearch;
					}

					lastVDirection = EUp;
					continue;
				}

				if (lastVDirection == EUp && config.file[config.width * (i + 1) + j] == 42) Search(config, { lastVDirection, 32, i + 1, j }, EUp);

				// check bottom
				if (lastVDirection != EUp && i + 1 < config.height && config.file[config.width * (i + 1) + j] == 32)
				{
					k = 0;
					if ((cPosition = Search(config, { lastVDirection, 32, i + 1, j }, EHorizontal)).node != '\0')
					{
						cPosition.pLastDirection = lastVDirection;
						return cPosition;
					}
						

					if (i + 1 < config.height && config.file[config.width * (i + 1) + j] != 42)
					{
						i++;
						if (bHoldYRowP1 != bHoldYRowP2) bHoldYRowP2 = !bHoldYRowP2;
						if (config.file[config.width * (i + 1) + j] == 42)
							if ((deepSearch = Search(config, { lastVDirection, 32, i, j }, EVertical)).node != 32) return deepSearch;
					}

					lastVDirection = EDown;
					
				}

				// The Great Reset Location
				if (j + 1 == config.width)
				{
					// this will check above or below next value
					if((deepSearch = Search(config, cPosition, EVertical, 1)).node != 42)
						return deepSearch;

					return { EReset, 42, cPosition.x, cPosition.y };
				}
					

				if (lastVDirection == EUp && config.file[config.width * (i - 1) + j] != 42 && config.file[config.width * (i - 1) + j] != 32)
					return { lastVDirection, config.file[config.width * (i - 1) + j], i - 1, j };

				if (lastVDirection == EDown && config.file[config.width * (i + 1) + j] != 42 && config.file[config.width * (i + 1) + j] != 32)
					return { lastVDirection, config.file[config.width * (i + 1) + j], i + 1, j };
			}
	}
	

	return {};
}

StackController::Coordinates DepthFirstSearch::FindStartObject(FileManager::Config config, Directions currentDirection)
{
	// Ascii to Text | 83 -> S
	for (size_t i = 0; i < config.height; i++)
		for (size_t j = 0; j < config.width; j++)
			if (config.file[config.width * i + j] == 83)
				return { currentDirection, 83, i, j };

	// return empty directions
	return {};
}


StackController::Coordinates DepthFirstSearch::NextCurrentObject(FileManager::Config config, StackController::Coordinates cPosition, Directions* cDirection)
{
	// Initialise the Stack - When we find the startPosition from the currentPosition
	// currently goes left, this needs to try left, then right.
	//
	// This will try left, then goes right.

	// As the vertical is dominant in this case, the reset functionality will enable the function to check left and right again now the vertical-left-right check has completed.

	bool bReset = false;
	StackController::Coordinates coordinates = Search(config, cPosition, *cDirection);

	if (coordinates.pLastDirection == EReset) {
		bReset = true;
		*cDirection = ChangeDirection(*cDirection);
		coordinates = NextCurrentObject(config, cPosition, cDirection);
	}
		
	
	if(!bReset && coordinates.node == '\0')
	{
		*cDirection = ChangeDirection(*cDirection);

		if (*cDirection == EVertical)
			return {};

		return Search(config, cPosition, *cDirection);
	}

	return coordinates;
}