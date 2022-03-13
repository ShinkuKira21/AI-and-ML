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

DepthFirstSearch::Directions DepthFirstSearch::ChangeDirection(Directions currentDirection)
{
	// The order is left first, if wall, then change to right, if right and wall, vertical is triggered.
	switch (currentDirection)
	{
		case EVertical:
			return ELeft;

		// Right
		case ERight:
			return EVertical;

		// Left is Default
		default:
			return ERight;
	}
}

StackController::Coordinates DepthFirstSearch::Search(FileManager::Config config, StackController::Coordinates cPosition, Directions cDirection)
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
					return { config.file[config.width * i + j], i, j };
			}
				
		// Change Direction
		// Right
		if(i < config.height && (cDirection == ERight || cDirection == EHorizontal))
			for (size_t j = cPosition.y + 1; j < config.width; j++)
			{
				if (config.file[config.width * i + j] == 42)
					break;

				if (config.file[config.width * i + j] != 32)
					return { config.file[config.width * i + j], i, j };
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
		Directions lastVDirection = EVertical;
		size_t i = cPosition.x;
		if (i < config.height)
			for (size_t j = cPosition.y - 1; j != std::string::npos && config.file[config.width * i + j] != 42; j--)
			{
				// shows last direction vertically
				//
				// locks the y-axis loop.
				if (lastVDirection != EVertical) j++;

				// check top
				if (lastVDirection != EDown && i > 0 && config.file[config.width * (i - 1) + j] == 32)
				{
					if ((cPosition = Search(config, { 32, i - 1, j }, EHorizontal)).node != '\0')
					{
						cDirection = ChangeDirection(cDirection);
						return cPosition;
					}

					if (i - 1 != std::string::npos && config.file[config.width * (i - 1) + j] != 42)
					{
						i--;
						if (config.file[config.width * (i + 1) + j] == 42) return Search(config, { 32, i, j }, EVertical);
					}
					lastVDirection = EUp;
					continue;
				}

				if (lastVDirection == EUp && config.file[config.width * (i + 1) + j] == 42) return Search(config, { lastVDirection, 32, i + 1, j }, EUp);

				// check bottom
				if (lastVDirection != EUp && i + 1 < config.height && config.file[config.width * (i + 1) + j] == 32)
				{
					if ((cPosition = Search(config, { 32, i + 1, j }, EHorizontal)).node != '\0') 
					{
						cDirection = ChangeDirection(cDirection);
						return cPosition;
					}
					if (i + 1 < config.height && config.file[config.width * (i + 1) + j] != 42)
					{
						i++;
						if (config.file[config.width * (i + 1) + j] == 42) return Search(config, { lastVDirection, 32, i, j }, EVertical);
					}
					lastVDirection = EDown;
				}

				if (lastVDirection == EDown && config.file[config.width * (i + 1) + j] == 42) Search(config, { lastVDirection, 32, i + 1, j }, EDown);

				if (config.file[config.width * (i + 1) + j] != 42) return { lastVDirection, config.file[config.width * (i + 1) + j], i + 1, j };
			}

		// Check up and down from right direction
		lastVDirection = EVertical;
		i = cPosition.x;
		if (i < config.height)
			for (size_t j = cPosition.y; j < config.width; j++)
			{
				// locks the y-axis loop.
				if (lastVDirection != EVertical) j--;

				// check top
				if (lastVDirection != EDown && i > 0 && config.file[config.width * (i - 1) + j] == 32)
				{
					if ((cPosition = Search(config, { 32, i - 1, j }, EHorizontal)).node != '\0') 
					{
						cDirection = ChangeDirection(cDirection);
						return cPosition;
					}

					if (i - 1 != std::string::npos && config.file[config.width * (i - 1) + j] != 42)
					{
						i--;
						if (config.file[config.width * (i + 1) + j] == 42) return Search(config, { 32, i, j }, EVertical);
					}

					lastVDirection = EUp;
					continue;
				}

				if (lastVDirection == EUp && config.file[config.width * (i + 1) + j] == 42) Search(config, { 32, i + 1, j }, EUp);

				// check bottom
				if (lastVDirection != EUp && i + 1 < config.height && config.file[config.width * (i + 1) + j] == 32)
				{
					if ((cPosition = Search(config, { 32, i + 1, j }, EHorizontal)).node != '\0')
					{
						cDirection = ChangeDirection(cDirection);
						return cPosition;
					}

					if (i + 1 < config.height && config.file[config.width * (i + 1) + j] != 42)
					{
						i++;
						if (config.file[config.width * (i + 1) + j] == 42) return Search(config, { 32, i, j }, EVertical);
					}

					lastVDirection = EDown;
				}

				if (config.file[config.width * (i + 1) + j] != 42 && config.file[config.width * (i + 1) + j] != 32) return { config.file[config.width * (i + 1) + j], i + 1, j };
			}
	}
	

	return {};
}

StackController::Coordinates DepthFirstSearch::FindStartObject(FileManager::Config config)
{
	// Ascii to Text | 83 -> S
	for (size_t i = 0; i < config.height; i++)
		for (size_t j = 0; j < config.width; j++)
			if (config.file[config.width * i + j] == 83)
				return { 83, i, j };

	// return empty directions
	return {};
}


StackController::Coordinates DepthFirstSearch::NextCurrentObject(FileManager::Config config, StackController::Coordinates cPosition, Directions* cDirection)
{
	// Initialise the Stack - When we find the startPosition from the currentPosition
	// currently goes left, this needs to try left, then right.
	//
	// This will try left, then goes right.
	StackController::Coordinates coordinates;
	if((coordinates = Search(config, cPosition, *cDirection)).node == '\0')
	{
		*cDirection = ChangeDirection(*cDirection);

		if (*cDirection == EVertical)
			return {};

		return Search(config, cPosition, *cDirection);
	}

	return coordinates;
}