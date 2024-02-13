#ifndef GoL_H
#define GoL_H
#include <iostream>
#include <random>
#include <chrono>
#include <sstream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

class GoL{
public:
    GoL(int rows, int cols, int seed);
    GoL(bool** grid);
    ~GoL();
    void nextGen();
    void printGame();
private:
    bool** grid;
    int numRows;
    int numCols;
    int seed;
};
#endif // GoL