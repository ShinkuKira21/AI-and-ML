#include "FileManager.h"
#include "DFS.h"
#include "../CVSTools/CVSTools.h"

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

void CreateMatlabCVS(Manager::Manager* manager)
{
	CVSTools::CVSProperties* properties = new CVSTools::CVSProperties();
	properties->col = 4;
	properties->headings = new std::string[4]{ "D",  "N", "X", "Y" };

	CVSTools::CVSHandler* cvs = new CVSTools::CVSHandler(properties, { "../DFSMatlab/cvs/", "DFS" });

	size_t depth = manager->positions.size() - 1;
	while(!manager->positions.empty())
	{
		cvs->CVSParser(0, std::to_string(depth).c_str());
		cvs->CVSParser(1, manager->positions.top().node);
		cvs->CVSParser(2, std::to_string(manager->positions.top().x).c_str());
		cvs->CVSParser(3, std::to_string(manager->positions.top().y).c_str());
		manager->positions.pop();
		depth--;
	}

	cvs->CVSStart();
	delete cvs;

	std::cout << "Generated Necessary Data Files for Matlab:" << std::endl << "Go to the DFSMatlab folder and open DFS Matlab application";
}

int main(int argc, char **argv)
{
	// !!! WHEN IT GETS TO B I NEED TO SOMEHOW RESET THE DIRECTIONAL AGAIN (fixed) 

	// enter m1.txt
	const std::string filename = Functions().TextInput("Enter filename: ");

	// If running outside of Visual Studio then the compiler may not understand that m1.txt exists in the content directory.
	// Therefore, using an argument fixes this problem.

	// Add 1 to the argument if "Unable to open file" error message raises and the file is located inside the content directory
	bool previousDirectory;
	argc > 0 && std::string(argv[argc-1]) == "1" ? previousDirectory = true : previousDirectory = false;

	const FileManager::Config config = FileManager::OpenFile(FileManager::FileSelector(filename.c_str(), previousDirectory).c_str());

	const char nodeToFind = Functions().TextInput("Enter Node to Find (Char): ")[0];
	Manager::Manager manager;
	Manager::DisplayBoard(config);
	
	manager.positions = StackController::InitialiseStack();

	// Once the start path is found, now find the next objects
	manager.direction = DepthFirstSearch::ELeft;
	AddToStack(&manager.positions, FindStartObject(config, manager.direction));


 	if(manager.positions.top().node == 83)
		while (!manager.positions.empty())
		{
			printf("N: %c X: %zi | Y: %zi | Last Direction Enum: %i | Current Direction Enum: %i\n", manager.positions.top().node, manager.positions.top().x, manager.positions.top().y, manager.positions.top().pLastDirection, manager.direction);

			if (nodeToFind == manager.positions.top().node) break;
			if (manager.positions.top().node == 70) break;

			StackController::Coordinates searchPosition;
			// Ascii to Text | 42 -> *
			if ((searchPosition = NextCurrentObject(config, manager.positions.top(), &manager.direction)).node != '\0') AddToStack(&manager.positions, searchPosition);
			else RemoveFromStack(&manager.positions);
		}

	// creates a CVS file for Matlab
	CreateMatlabCVS(&manager);

	EmptyStack(&manager.positions);

    // Memory Handler
    DisposeConfig(config);

    return 0;
}