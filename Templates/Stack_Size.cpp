#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

// Run with larger stack size
// Useful for: deep recursion (DFS on long chains, tree DP with deep trees)

void main_() {
    // Your code here that needs deep recursion
}

static void run_with_stack_size(void (*func)(void), size_t stsize) {
    char *stack, *send;
    stack = (char *)malloc(stsize);
    send = stack + stsize - 16;
    send = (char *)((uintptr_t)send / 16 * 16);
    asm volatile(
        "mov %%rsp, (%0)\n"
        "mov %0, %%rsp\n"
        :
        : "r"(send));
    func();
    asm volatile("mov (%0), %%rsp\n" : : "r"(send));
    free(stack);
}

int main() {
    run_with_stack_size(main_, 256 * 1024 * 1024); // 256 MB
    return 0;
}

/*
    Alternative via command line:
    Linux:   ulimit -s unlimited && g++ -std=c++17 file.cpp -o file
    Windows: g++ -Wl,-stack=268435456 -std=c++17 file.cpp -o file
*/
