#include <iostream>

namespace E1 {
    int FitnessFunction(int* x)
    {
        return (x[0] + x[1]) - (x[2] + x[3]) + x[4] - x[5];
    }

    void RUN_E1()
    {
        int* x = new int[6] {6, 1, 3, 3, 4, 7};
        printf("%i\n", E1::FitnessFunction(x));
        delete[] x;

        x = new int[6] {1, 6, 7, 8, 6, 4};
        printf("%i\n", E1::FitnessFunction(x));
        delete[] x;

        x = new int[6] {3, 2, 5, 6, 6, 7};
        printf("%i\n", E1::FitnessFunction(x));
        delete[] x;

        x = new int[6] {7, 0, 8, 5, 4, 2};
        printf("%i\n", E1::FitnessFunction(x));
        delete[] x;
    }
}

namespace E2 {
    /* THEORY 
        158347 | 921865 | 158921
        921865 | 283745 | 921283
        283745 | 304257 | 283304
    */

    void RUN_E2()
    {
        int* x = new int[6] {1, 5, 8, 9, 2, 1};
        printf("%i\n", E1::FitnessFunction(x));
        delete[] x;

        x = new int[6] {9, 2, 1, 2, 8, 3};
        printf("%i\n", E1::FitnessFunction(x));
        delete[] x;

        x = new int[6] {2, 8, 3, 3, 0, 4};
        printf("%i\n", E1::FitnessFunction(x));
        delete[] x;
    }
}

int main()
{
    E2::RUN_E2();

    return 0;
}