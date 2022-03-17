#include "StackController.h"

std::stack<StackController::Coordinates> StackController::InitialiseStack()
{ return std::stack<Coordinates>(); }

std::stack<StackController::Coordinates> StackController::InitialiseStack(Coordinates position)
{
	std::stack<Coordinates> stack;

	stack.push(position);

	return stack;
}

void StackController::AddToStack(std::stack<Coordinates>* stack, Coordinates position)
{ stack->push(position); }

void StackController::RemoveFromStack(std::stack<Coordinates>* stack)
{ stack->pop(); }

