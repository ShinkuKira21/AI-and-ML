#pragma once
#include "FileManager.h"
#include "StackController.h"

// Instead of this managing the pushing/popping, I think if I test pathways and return coordinates then another place can handle Stack Control.

namespace DepthFirstSearch
{
	enum Directions
	{
		ELeft = 0,
		ERight = 1,
		EUp = 2,
		EDown = 3,
		EHorizontal = 4, // Designated for vague horizontal navigation
		EVertical = 5 // Designated for vague vertical navigation
	};

	inline void DisplayContent(FileManager::Config config)
	{
		for (size_t i = 0; i < config.height; i++)
		{
			for (size_t j = 0; j < config.width; j++)
				std::cout << config.file[config.width * i + j];

			std::cout << std::endl;
		}
	}

	// This is reference for now, perhaps may not be essential.
	void AllPathways(FileManager::Config config);

	// so the start logic does not need to obey direction.
	// this makes it different to the NextCurrentObject Function.
	StackController::Coordinates FindStartObject(FileManager::Config config);
	StackController::Coordinates NextCurrentObject(FileManager::Config config, StackController::Coordinates currentPosition, Directions* currentDirection);

	StackController::Coordinates Search(FileManager::Config config, StackController::Coordinates currentPosition, Directions currentDirection);

	Directions ChangeDirection(Directions currentDirection);

}
