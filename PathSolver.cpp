#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver()
{
    nodesExplored = new NodeList();
}

PathSolver::~PathSolver()
{
    delete nodesExplored;
}

void PathSolver::forwardSearch(Env env)
{
    Node *startNode = new Node();
    Node *goalNode = new Node();
    Node *currentNode = new Node();
    NodeList *openList = new NodeList();
    NodeList *closedList = new NodeList();

    initializeAlgo(startNode, goalNode, currentNode, openList, env);

    while (currentNode->getRow() != goalNode->getRow() && currentNode->getCol() != goalNode->getCol())
    {
        currentNode = openList->getSmallestEstDistNode(goalNode, closedList);

        searchAllDirections(currentNode, env, openList);
    }

    delete openList;
    delete closedList;
}

NodeList *PathSolver::getNodesExplored()
{
    NodeList *nodesExploredCopy = new NodeList(*nodesExplored);
    return nodesExploredCopy;
}

NodeList *PathSolver::getPath(Env env)
{
    // TODO
    return NULL;
}

void PathSolver::initializeAlgo(Node *startNode, Node *goalNode, Node *currentNode, NodeList *openList, Env env)
{
    //Read the locations of start and goal positions
    for (int i = 0; i < pow(ENV_DIM, 2); i++)
    {
        if (env[i / 20][i % 20] == SYMBOL_START)
        {
            startNode = new Node(i / 20, i % 20, 0);
        }
        if (env[i / 20][i % 20] == SYMBOL_GOAL)
        {
            //distance_traveled not relevant for goal node
            goalNode = new Node(i / 20, i % 20, -1);
        }
    }
    //Add the start position to the openList
    openList->addElement(startNode);
    currentNode = startNode;
}
void PathSolver::searchAllDirections(Node *currentNode, Env env, NodeList *openList)
{

    Node *checkNodeUp = new Node(currentNode->getRow() + 1, currentNode->getCol(), currentNode->getDistanceTraveled() + 1);
    Node *checkNodeDown = new Node(currentNode->getRow() - 1, currentNode->getCol(), currentNode->getDistanceTraveled() + 1);
    Node *checkNodeLeft = new Node(currentNode->getRow(), currentNode->getCol() - 1, currentNode->getDistanceTraveled() + 1);
    Node *checkNodeRight = new Node(currentNode->getRow(), currentNode->getCol() + 1, currentNode->getDistanceTraveled() + 1);

    if (currentNode->getRow() > 0 && !openList->isIncluded(checkNodeLeft))
    {
        if (env[checkNodeLeft->getRow()][checkNodeLeft->getCol()] == SYMBOL_EMPTY)
        {
            openList->addElement(checkNodeLeft);
        }
    }

    if (currentNode->getRow() < 20 && !openList->isIncluded(checkNodeRight))
    {
        if (env[checkNodeRight->getRow()][checkNodeRight->getCol()] == SYMBOL_EMPTY)
        {
            openList->addElement(checkNodeRight);
        }
    }

    if (currentNode->getCol() > 0 && !openList->isIncluded(checkNodeUp))
    {
        if (env[checkNodeUp->getRow()][checkNodeUp->getCol()] == SYMBOL_EMPTY)
        {
            openList->addElement(checkNodeUp);
        }
    }

    if (currentNode->getCol() < 20 && !openList->isIncluded(checkNodeDown))
    {
        if (env[checkNodeDown->getRow()][checkNodeDown->getCol()] == SYMBOL_EMPTY)
        {
            openList->addElement(checkNodeDown);
        }
    }
}
//-----------------------------