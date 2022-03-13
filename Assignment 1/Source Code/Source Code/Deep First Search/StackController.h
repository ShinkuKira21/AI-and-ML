#pragma once

#include <stack>

// extends DFS - could be moved to another file but for now it stays!
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
}

namespace StackController
{
	struct Coordinates
	{
		// previous last direction
		DepthFirstSearch::Directions pLastDirection;
		char node;
		size_t x, y;
	};

	std::stack<Coordinates> InitialiseStack();

	// Should get called on starting position
	std::stack<Coordinates> InitialiseStack(Coordinates position);

	// To be honest, I know these features exist within the stack functionality,
	// but it is to give it some meat to the Stack Controller.
	void AddToStack(std::stack<Coordinates>* stack, Coordinates position);
	void RemoveFromStack(std::stack<Coordinates>* stack);

	inline bool EmptyStack(std::stack<Coordinates>* stack)
	{ return stack->empty(); }
}