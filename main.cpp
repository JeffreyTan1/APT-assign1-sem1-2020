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
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList *solution);

int main(int argc, char **argv)
{

    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl
    //           << std::endl;

    // Load Environment
    Env env;
    readEnvStdin(env);

    // Solve using forwardSearch
    PathSolver *pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);
    std::cout << "forward search done in main now" << std::endl;

    NodeList *exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();
    std::cout << "explored positions done" << std::endl;

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList *solution = pathSolver->getPath(env);
    std::cout << "solution assigned" << std::endl;

    printEnvStdout(env, solution);

    delete pathSolver;
    delete exploredPositions;
    delete solution;
}

void readEnvStdin(Env env)
{
    char c;
    for (int i = 0; i < pow(ENV_DIM, 2); i++)
    {
        std::cin >> c;
        env[i / 20][i % 20] = c;
    }
}

void printEnvStdout(Env env, NodeList *solution)
{

    Node *prevNode = solution->getNode(0);

    for (int i = 1; i < solution->getLength() - 1; i++)
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

    for (int i = 0; i < ENV_DIM; i++)
    {
        for (int j = 0; j < ENV_DIM; j++)
        {
            std::cout << env[i][j] << " ";
        }
        std::cout << std::endl;
    }
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
    NodeList *nodeList = new NodeList();
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