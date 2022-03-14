#include "FileManager.h"
#include "DFS.h"

namespace Manager
{
	struct Manager
	{
		std::stack<StackController::Coordinates> positions;
		DepthFirstSearch::Directions direction;
	};

	void DisplayBoard(FileManager::Config config)
	{
		DepthFirstSearch::DisplayContent(config);
		//DepthFirstSearch::AllPathways(config);
	}
}

int main(int argc, char **argv)
{
	// !!! WHEN IT GETS TO B I NEED TO SOMEHOW RESET THE DIRECTIONAL AGAIN

	FileManager::Config config = FileManager::OpenFile(FileManager::FileSelector("m1.txt").c_str());

	Manager::Manager manager;
	Manager::DisplayBoard(config);
	
	manager.positions = StackController::InitialiseStack();

	// Once the start path is found, now find the next objects
	manager.direction = DepthFirstSearch::ELeft;
	AddToStack(&manager.positions, FindStartObject(config, manager.direction));


 	if(manager.positions.top().node == 83)
		while (!manager.positions.empty())
		{
			printf("N: %c X: %i | Y: %i | Last Direction Enum: %i | Current Direction Enum: %i\n", manager.positions.top().node, manager.positions.top().x, manager.positions.top().y, manager.positions.top().pLastDirection, manager.direction);

			if (manager.positions.top().node == 70) break;

			StackController::Coordinates searchPosition;

			// Ascii to Text | 42 -> *
			if ((searchPosition = NextCurrentObject(config, manager.positions.top(), &manager.direction)).node != '\0') AddToStack(&manager.positions, searchPosition);
			else RemoveFromStack(&manager.positions);
		}

	EmptyStack(&manager.positions);


    // Memory Handler
    DisposeConfig(config);

    return 0;
}