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

// ~find comment 1.0 for this to make sense | comment 3.0 - remove manager->positions.pop() | add depth to argument :) and move depth into the comment 2.0 area |
CVSTools::CVSHandler* CreateMatlabCVS()
{
	CVSTools::CVSProperties* properties = new CVSTools::CVSProperties();
	properties->col = 4;
	properties->headings = new std::string[4]{ "D",  "N", "X", "Y" };

	return new CVSTools::CVSHandler(properties, { "../DFSMatlab/cvs/", "DFS" });
}

void MatlabRows(Manager::Manager* manager, CVSTools::CVSHandler* cvs, size_t depth)
{
	// comment 1.0 problem with this is that when this stage begins after the results are fetched ~find comment 2.0
	//size_t depth = manager->positions.size() - 1;
	//while(!manager->positions.empty())
	//{
		cvs->CVSParser(0, std::to_string(depth).c_str());
		cvs->CVSParser(1, manager->positions.top().node);
		cvs->CVSParser(2, std::to_string(manager->positions.top().x).c_str());
		cvs->CVSParser(3, std::to_string(manager->positions.top().y).c_str());
		//manager->positions.pop();
		//depth--;
	//}
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

	// Initialise CVS
	CVSTools::CVSHandler* cvs = CreateMatlabCVS();
	manager.positions = StackController::InitialiseStack();

	// Once the start path is found, now find the next objects
	manager.direction = DepthFirstSearch::ELeft;
	AddToStack(&manager.positions, FindStartObject(config, manager.direction));

	size_t depth = 1;
 	if(manager.positions.top().node == 83)
		while (!manager.positions.empty())
		{
			// comment 2.0
			printf("N: %c X: %zi | Y: %zi | Last Direction Enum: %i | Current Direction Enum: %i\n", manager.positions.top().node, manager.positions.top().x, manager.positions.top().y, manager.positions.top().pLastDirection, manager.direction);
			// move the CreateMatlabCVS here, ~find comment 3.0
			// creates a CVS file for Matlab
			MatlabRows(&manager, cvs, depth);
			if (nodeToFind == manager.positions.top().node) break;
			if (manager.positions.top().node == 70) break;

			StackController::Coordinates searchPosition;
			// Ascii to Text | 42 -> *
			if ((searchPosition = NextCurrentObject(config, manager.positions.top(), &manager.direction)).node != '\0') AddToStack(&manager.positions, searchPosition);
			else RemoveFromStack(&manager.positions);
			depth++;
		}

	cvs->CVSStart();
	delete cvs;
	std::cout << "Generated Necessary Data Files for Matlab:" << std::endl << "Go to the DFSMatlab folder and open DFS Matlab application";

	EmptyStack(&manager.positions);

    // Memory Handler
    DisposeConfig(config);

    return 0;
}