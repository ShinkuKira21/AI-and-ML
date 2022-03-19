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
	// !!! WHEN IT GETS TO B I NEED TO SOMEHOW RESET THE DIRECTIONAL AGAIN (fixed) 

	// enter m1.txt
	std::string filename = (Functions().TextInput("Enter filename: "));

	// If running outside of Visual Studio then the compiler may not understand that m1.txt exists in the content directory.
	// Therefore, using an argument fixes this problem.

	// Add 1 to the argument if "Unable to open file" error message raises and the file is located inside the content directory
	bool previousDirectory;
	argc > 0 && std::string(argv[argc-1]) == "1" ? previousDirectory = true : previousDirectory = false;

	FileManager::Config config = FileManager::OpenFile(FileManager::FileSelector(filename.c_str(), previousDirectory).c_str());

	Manager::Manager manager;
	Manager::DisplayBoard(config);
	
	manager.positions = StackController::InitialiseStack();

	// Once the start path is found, now find the next objects
	manager.direction = DepthFirstSearch::ELeft;
	AddToStack(&manager.positions, FindStartObject(config, manager.direction));


 	if(manager.positions.top().node == 83)
		while (!manager.positions.empty())
		{
			printf("N: %c X: %li | Y: %li | Last Direction Enum: %i | Current Direction Enum: %i\n", manager.positions.top().node, manager.positions.top().x, manager.positions.top().y, manager.positions.top().pLastDirection, manager.direction);

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