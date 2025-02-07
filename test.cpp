#include <stdio.h>
#include <time.h>

#include <vector>

#include "lib.hpp"


int main() {
    // WARNING: 2GB of RAM will be allocated and freed
    const usize count = (1 << 28) - 1;

    // NoCopyVec
    {
        NoCopyVec<usize> ncv;

        clock_t start_time = clock();
        for (usize i = 0; i < count; i++) {
            ncv.push(i);
        }
        clock_t end_time = clock();
        double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("\x1b[34m⏱\x1b[0m Time taken for NoCopyVec: %f secondes\n", time_taken);

        for (usize i = 0; i < count; i++) {
            if (i != ncv.at(i)) {
                printf("\x1b[31m✖\x1b[0m NoCopyVec test failed at index: %lu (%lu)...\n", i, ncv.at(i));
                return 1;
            }
        }

        printf("\x1b[32m✔\x1b[0m NoCopyVec test passed!\n\n");
    }

    // NoCopyVecPre (pre-allocated)
    {
        NoCopyVecPre<usize> ncvp(28);

        clock_t start_time = clock();
        for (usize i = 0; i < count; i++) {
            ncvp.push(i);
        }
        clock_t end_time = clock();
        double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("\x1b[34m⏱\x1b[0m Time taken for NoCopyVecPre: %f secondes\n", time_taken);

        for (usize i = 0; i < count; i++) {
            if (i != ncvp.at(i)) {
                printf("\x1b[31m✖\x1b[0m NoCopyVecPre test failed at index: %lu (%lu)...\n", i, ncvp.at(i));
                return 1;
            }
        }

        printf("\x1b[32m✔\x1b[0m NoCopyVecPre test passed!\n\n");
    }

    // std::vector
    {
        std::vector<usize> vec;

        clock_t start_time = clock();
        for (usize i = 0; i < count; i++) {
            vec.push_back(i);
        }
        clock_t end_time = clock();
        double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("\x1b[34m⏱\x1b[0m Time taken for std::vector: %f secondes\n", time_taken);
    }
}
