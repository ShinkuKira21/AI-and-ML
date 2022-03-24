#include "coms.h"

CMemory CreateData::CreateCMemory(char *name, int size)
{
    CMemory test({name, size});

    return test;
}