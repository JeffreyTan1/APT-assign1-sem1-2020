/**
 * Description of my approach:
 * In my forward search, the loop relies on 2 methods.
 * 1. pointAllDirections() 
 * which sets pointers to arbitrary nodes up/down/left/right of current node p
 * 2. addAllDirections()
 * which adds those nodes to the openlist if the env has an open space or goal
 * 
 * In my get path, I create a list of 4 elements called neighbors which contains
 * nodes u/d/l/r of the current node if they exist. Then this list is compared with
 * the closed list to find the next node backwards.
 * 
 * Issues encountered:
 * Segmentation faults were plentiful, mainly caused by not giving the correct
 * termination condition in the for loops.
 * On the brightside it made be really good at using GDB
 * 
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin();

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList *solution);

//Implemented for Milestone 4
Env make_env(const int rows, const int cols);
void delete_env(Env env, int rows, int cols);

Env env;

//Variables for the dimensions of input env.
//Are shared to all files through Types.h
int maxSize;
int rows;
int cols;

int main(int argc, char **argv)
{

    // Load Environment
    readEnvStdin();

    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl
    //           << std::endl;

    // Solve using forwardSearch
    PathSolver *pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList *exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    NodeList *solution = pathSolver->getPath(env);

    // Print the maze with the path drawn out
    printEnvStdout(env, solution);

    delete pathSolver;
    delete exploredPositions;
    delete solution;
    delete_env(env, rows, cols);
    return EXIT_SUCCESS;
}

void readEnvStdin()
{
    char c;
    int rowCount = 0;
    int charCount = 0;

    //read input to find the number of rows and columns
    while (!std::cin.eof())
    {
        std::cin.get(c);
        if (c == '\n')
        {
            rowCount++;
        }
        else
        {
            charCount++;
        }
    }
    //last line doesn't end in a \n but is still a row
    rowCount++;
    //at eof we shouldn't add the extra character even though no \n is found
    charCount--;

    rows = rowCount;
    cols = charCount / rowCount;
    maxSize = rows * cols;

    env = make_env(rows, cols);

    //read from the beginning of input again
    std::cin.clear();
    std::cin.seekg(0);

    //read input and set characters to env
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cin >> c;
            env[i][j] = c;
        }
    }
}

void printEnvStdout(Env env, NodeList *solution)
{

    Node *prevNode = solution->getNode(0);
    //Loop through solution list and add appropriate arrow characters
    for (int i = 0; i < solution->getLength() - 1; i++)
    {
        Node *currentNode = solution->getNode(i);
        if (currentNode->isAbove(prevNode))
        {
            env[currentNode->getRow()][currentNode->getCol()] = '^';
        }
        if (currentNode->isBelow(prevNode))
        {
            env[currentNode->getRow()][currentNode->getCol()] = 'v';
        }
        if (currentNode->isToLeft(prevNode))
        {
            env[currentNode->getRow()][currentNode->getCol()] = '<';
        }

        if (currentNode->isToRight(prevNode))
        {
            env[currentNode->getRow()][currentNode->getCol()] = '>';
        }
        prevNode = currentNode;
    }

    //Print env
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << env[i][j];
        }
        if (!(i == rows - 1))
        {
            std::cout << std::endl;
        }
    }
}

Env make_env(const int rows, const int cols)
{
    Env env = nullptr;

    if (rows >= 0 && cols >= 0)
    {
        env = new char *[rows];
        for (int i = 0; i != rows; ++i)
        {
            env[i] = new char[cols];
        }
    }

    return env;
}

void delete_env(Env env, int rows, int cols)
{
    if (rows >= 0 && cols >= 0)
    {
        for (int i = 0; i != rows; ++i)
        {
            delete env[i];
        }
        delete env;
    }

    return;
}

void testNode()
{
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node *node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList()
{
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList *nodeList = new NodeList(maxSize);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node *b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node *b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node *getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}