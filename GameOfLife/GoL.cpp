#include "GoL.h"

using std::cout;
using std::endl;
GoL::GoL(int numRows, int cols, int seed)
{
    GoL::numRows = numRows;
    numCols = cols;
    seed = seed;
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, 1);
    grid = new bool *[numRows];
    for (int rowCount = 0; rowCount < numRows; ++rowCount)
    {
        grid[rowCount] = new bool[numCols]{};
    }
    int rand = distribution(generator);
    for (int rowCount = 0; rowCount < numRows; ++rowCount)
    {
        for (int colCount = 0; colCount < numCols; ++colCount)
        {
            if (rand == 1)
            { // Alive
                grid[rowCount][colCount] = true;
            }
            rand = distribution(generator);
        }
    }
}


GoL::~GoL()
{
    if (grid != nullptr)
    {
        for (int rowCount = 0; rowCount < numRows; ++rowCount)
        {
            
            delete[] grid[rowCount];
            
        }
        delete[] grid;
    }
}

void GoL::nextGen()
{
    int count = -1;
    //Create new grid to apply changes to
    bool** newGrid = new bool*[numRows];
    for (int rowCount = 0; rowCount < numRows; ++rowCount)
    {
        newGrid[rowCount] = new bool[numCols]{};
    }
    
    for (int rowCount = 0; rowCount < numRows; ++rowCount)
    {
        for (int colCount = 0; colCount < numCols; ++colCount)
        {
            count = 0;

            if (colCount - 1 >= 0 && grid[rowCount][colCount - 1])
            { // check left
                ++count;
            }

            if (colCount + 1 < numCols && grid[rowCount][colCount + 1])
            { // check right
                ++count;
            }

            if (rowCount - 1 >= 0 && grid[rowCount - 1][colCount])
            { // check up
                ++count;
            }

            if (rowCount + 1 < numRows && grid[rowCount + 1][colCount])
            { // check down
                ++count;
            }

            if ((rowCount - 1 >= 0 && colCount - 1 >= 0) && grid[rowCount - 1][colCount - 1])
            { // check up left
                ++count;
            }

            if ((rowCount - 1 >= 0 && colCount + 1 < numCols) && grid[rowCount - 1][colCount + 1])
            { // check up right
                ++count;
            }

            if ((rowCount + 1 < numRows && colCount - 1 >= 0) && grid[rowCount + 1][colCount - 1])
            { // check down left
                ++count;
            }

            if ((rowCount + 1 < numRows && colCount + 1 < numCols) && grid[rowCount + 1][colCount + 1])
            { // check down right
                ++count;
            }

            // if alive
            if (grid[rowCount][colCount])
            {
                if (count < 2)
                { // underpopulation
                    newGrid[rowCount][colCount] = false;
                }
                else if (count <= 3)
                { // alive
                    newGrid[rowCount][colCount] = true;
                }
                else if (count > 3)
                { // overpopulation
                    newGrid[rowCount][colCount] = false;
                }
            }
            else
            { // if dead
                if (count == 3)
                { // check for revival
                    newGrid[rowCount][colCount] = true;
                }
            }
        }
    }
    //Assign new grid of changes
    for (int rowCount = 0; rowCount < numRows; ++rowCount)
        {
            
            delete[] grid[rowCount];
            
        }
    delete[] grid;
    grid = newGrid;
}

void GoL::printGame()
{
    cout << "x";
    for (int colCount = 0; colCount < numCols; ++colCount)
        cout << "-";
    cout << "x" << endl;
    for (int rowCount = 0; rowCount < numRows; ++rowCount)
    {
        cout << "|";
        for (int colCount = 0; colCount < numCols; ++colCount)
        {
            if (grid[rowCount][colCount])
                cout << '+';
            else
                cout << ' ';
        }
        cout << "|" << endl;
    }
    cout << "x";
    for (int colCount = 0; colCount < numCols; ++colCount)
        cout << "-";
    cout << "x" << endl;
}
int main(int argc, char **argv)
{
    GoL *myGame;
    int seed;
    int rows;
    int cols;
    int generations = -1;
    if (argc == 1)
    {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distribution(3, 10);
        rows = distribution(generator);
        cols = distribution(generator);
    }
    else
    {
        std::stringstream strNum1(argv[1]);
        if (!(strNum1 >> seed))
            seed = std::chrono::system_clock::now().time_since_epoch().count();
        if (argv[2] != 0)
        {
            std::stringstream strNum2(argv[2]);
            if (!(strNum2 >> rows))
            {
                rows = 8;
            }
        }
        if (argv[3] != 0)
        {
            std::stringstream strNum3(argv[3]);
            if (!(strNum3 >> cols))
            {
                cols = 8;
            }
        }
        if (argv[4] != 0)
        {
            std::stringstream strNum4(argv[4]);
            ;
            if (!(strNum4 >> generations))
            {
                generations = -1;
            }
        }
    }

    cout << "Seed: " << seed << endl;
    cout << "Rows: " << rows << endl;
    cout << "Columns: " << cols << endl;
    myGame = new GoL(rows, cols, seed);
    cout << "Initial set: " << endl;
    myGame->printGame();
    int count = 0;
    if (generations < 0)
    {
        cout << "Enter number of generations: ";
        while (std::cin.fail() || generations < 0)
        {
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                cout << endl;
                cout << "Enter nubmers only: ";
            }
            std::cin >> generations;
            if (generations < 0)
            {
                cout << endl;
                cout << "Enter a positive number, or zero: ";
            }
            
        }
    }
    while (count < generations)
    {
        myGame->nextGen();
        sleep(1);
        myGame->printGame();
        ++count;
    }
    
    delete myGame;
    return EXIT_SUCCESS;
}