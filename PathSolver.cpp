#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver()
{
    nodesExplored = new NodeList();
    openList = new NodeList();
    path = new NodeList();
}

PathSolver::~PathSolver()
{
    delete nodesExplored;
    delete startNode;
    delete goalNode;
    delete nodeUp;
    delete nodeDown;
    //delete nodeLeft;
    //delete nodeRight;
    delete openList;
    delete path;
    //delete neighbors;
}

PathSolver::PathSolver(int maxSize, int rows, int cols) : maxSize(maxSize),
                                                          rows(rows),
                                                          cols(cols)
{
    nodesExplored = new NodeList(maxSize);
    openList = new NodeList(maxSize);
    path = new NodeList(maxSize);
}

void PathSolver::forwardSearch(Env env)
{
    //Initalize class variables
    initializeAlgo(env);

    while (!currentNode->isSamePosition(goalNode))
    {
        currentNode = openList->getSmallestEstDistNode(goalNode, nodesExplored);
        std::cout << currentNode->to_string() << std::endl;
        pointAllDirections();
        addAllDirections(env);
        openList->printList(nodesExplored);
        nodesExplored->addElement(currentNode);
    }

    std::cout << "done" << std::endl;
    goalNode->setDistanceTraveled(currentNode->getDistanceTraveled());
    std::cout << "setDistTravelled for goal node" << std::endl;
    nodesExplored->addElement(goalNode);
    std::cout << "addElement goal node" << std::endl;
}

NodeList *PathSolver::getPath(Env env)
{
    currentNode = goalNode;

    for (int i = 0; i < goalNode->getDistanceTraveled() + 1; i++)
    {
        path->addElement(currentNode);
        pointAllDirections();
        neighbors = new NodeList(4);
        addAllDirections2(env);
        currentNode = nodesExplored->searchPathNeighbors4LeastDist(currentNode, neighbors);
    }

    path->reverseList();
    NodeList *pathCopy = new NodeList(*path);
    return pathCopy;
}

void PathSolver::initializeAlgo(Env env)
{
    //Read the locations of start and goal positions
    // for (int i = 0; i < maxSize; i++)
    // {
    //     if (env[i / rows][i % cols] == SYMBOL_START)
    //     {
    //         startNode = new Node(i / rows, i % cols, 0);
    //     }
    //     if (env[i / rows][i % cols] == SYMBOL_GOAL)
    //     {
    //         //distance_traveled not relevant for goal node
    //         goalNode = new Node(i / rows, i % cols, -1);
    //     }
    // }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (env[i][j] == SYMBOL_START)
            {
                startNode = new Node(i, j, 0);
            }
            if (env[i][j] == SYMBOL_GOAL)
            {
                //distance_traveled not relevant for goal node
                goalNode = new Node(i, j, -1);
            }
        }
    }

    //Add the start position to the openList
    openList->addElement(startNode);
    currentNode = startNode;
}
void PathSolver::pointAllDirections()
{
    nodeUp = new Node(currentNode->getRow() - 1, currentNode->getCol(), currentNode->getDistanceTraveled() + 1);
    nodeDown = new Node(currentNode->getRow() + 1, currentNode->getCol(), currentNode->getDistanceTraveled() + 1);
    nodeLeft = new Node(currentNode->getRow(), currentNode->getCol() - 1, currentNode->getDistanceTraveled() + 1);
    nodeRight = new Node(currentNode->getRow(), currentNode->getCol() + 1, currentNode->getDistanceTraveled() + 1);
}

void PathSolver::addAllDirections(Env env)
{
    if (currentNode->getCol() > 0 && !openList->isIncluded(nodeLeft))
    {
        addElementIfEmpty(nodeLeft, env);
        std::cout << "L";
    }
    else
    {
        delete nodeLeft;
    }
    if (currentNode->getCol() < (cols - 1) && !openList->isIncluded(nodeRight))
    {
        addElementIfEmpty(nodeRight, env);
        std::cout << "R";
    }
    else
    {
        delete nodeRight;
    }
    if (currentNode->getRow() > 0 && !openList->isIncluded(nodeUp))
    {
        addElementIfEmpty(nodeUp, env);
        std::cout << "U";
    }
    else
    {
        delete nodeUp;
    }
    if (currentNode->getRow() < (rows - 1) && !openList->isIncluded(nodeDown))
    {
        addElementIfEmpty(nodeDown, env);
        std::cout << "D";
    }
    else
    {
        delete nodeDown;
    }
}

void PathSolver::addElementIfEmpty(Node *node, Env env)
{
    if (env[node->getRow()][node->getCol()] == SYMBOL_EMPTY || env[node->getRow()][node->getCol()] == SYMBOL_GOAL)
    {
        openList->addElement(node);
    }
}

// NodeList *PathSolver::createNeighborsList(Env env)
// {
//     neighbors = new NodeList(4);
//     pointAllDirections();
//     addAllDirections2(env);
//     return neighbors;
// }

NodeList *PathSolver::getNodesExplored()
{
    NodeList *nodesExploredCopy = new NodeList(*nodesExplored);
    return nodesExploredCopy;
}

void PathSolver::addAllDirections2(Env env)
{
    if (currentNode->getCol() > 0)
    {
        addElementIfEmpty2(nodeLeft, env);
    }
    else
    {
        delete nodeLeft;
    }
    if (currentNode->getCol() < (cols - 1))
    {
        addElementIfEmpty2(nodeRight, env);
    }
    else
    {
        delete nodeRight;
    }
    if (currentNode->getRow() > 0)
    {
        addElementIfEmpty2(nodeUp, env);
    }
    else
    {
        delete nodeUp;
    }
    if (currentNode->getRow() < (rows - 1))
    {
        addElementIfEmpty2(nodeDown, env);
    }
    else
    {
        delete nodeDown;
    }
}

void PathSolver::addElementIfEmpty2(Node *node, Env env)
{
    if (env[node->getRow()][node->getCol()] == SYMBOL_EMPTY || env[node->getRow()][node->getCol()] == SYMBOL_START)
    {
        neighbors->addElement(node);
    }
}

//-----------------------------