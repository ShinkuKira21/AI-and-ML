#pragma once
#include <stack>

namespace StackController
{
	struct Coordinates
	{
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