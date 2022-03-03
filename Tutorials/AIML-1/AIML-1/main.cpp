#include <iostream>
#include <stack>

namespace E1
{
	typedef struct {
		int x;
		int y;
	} position;

	std::stack<position> dfsStack;

	void RUN_E1() {
		position current;  //initialise current position
		current.x = 0;
		current.y = 0;
		position startPosition;   //initialise start position
		startPosition.x = 1;
		startPosition.y = 2;
		dfsStack.push(startPosition);  //dfs initialise stack with start position

		for (int i = 0; i < 5; i++)  //push a shed load of positions onto this stack to test it.
			for (int j = 0; j < 5; j++) // not part of the dfs algorithm!!!!!!!!!!!!!!
			{
				current.x = i;
				current.y = j;
				dfsStack.push(current);
				std::cout << "pushing" << std::endl;
			}

		//empties stack
		while (!dfsStack.empty()) 
		{
			current = dfsStack.top();  //top plus pop equals a stack pop operation
			dfsStack.pop();
			std::cout << "Popping (" << current.x << "," << current.y << ")" << std::endl;
		}
	}
}

int main(int argc, char** argv)
{
	E1::RUN_E1();

	return 0;
}