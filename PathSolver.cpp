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
    delete nodeLeft;
    delete nodeRight;
    delete openList;
    delete path;
    delete neighbors;
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
        currentNode = nodesExplored->searchPathNeighbors4LeastDist(currentNode, createNeighborsList(env));
    }

    path->reverseList();
    NodeList *pathCopy = new NodeList(*path);
    return pathCopy;
}

void PathSolver::initializeAlgo(Env env)
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

void PathSolver::addAllDirections(Env env)
{
    if (currentNode->getCol() > 0 && !openList->isIncluded(nodeLeft))
    {
        addElementIfEmpty(nodeLeft, env);
    }
    if (currentNode->getCol() < 20 && !openList->isIncluded(nodeRight))
    {
        addElementIfEmpty(nodeRight, env);
    }
    if (currentNode->getRow() > 0 && !openList->isIncluded(nodeUp))
    {
        addElementIfEmpty(nodeUp, env);
    }
    if (currentNode->getRow() < 20 && !openList->isIncluded(nodeDown))
    {
        addElementIfEmpty(nodeDown, env);
    }
}

void PathSolver::addElementIfEmpty(Node *node, Env env)
{
    if (env[node->getRow()][node->getCol()] == SYMBOL_EMPTY || env[node->getRow()][node->getCol()] == SYMBOL_GOAL)
    {
        openList->addElement(node);
    }
}

NodeList *PathSolver::createNeighborsList(Env env)
{
    neighbors = new NodeList();
    pointAllDirections();
    addAllDirections2(env);
    return neighbors;
}

void PathSolver::pointAllDirections()
{
    nodeUp = new Node(currentNode->getRow() - 1, currentNode->getCol(), currentNode->getDistanceTraveled() + 1);
    nodeDown = new Node(currentNode->getRow() + 1, currentNode->getCol(), currentNode->getDistanceTraveled() + 1);
    nodeLeft = new Node(currentNode->getRow(), currentNode->getCol() - 1, currentNode->getDistanceTraveled() + 1);
    nodeRight = new Node(currentNode->getRow(), currentNode->getCol() + 1, currentNode->getDistanceTraveled() + 1);
}

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
    if (currentNode->getCol() < 20)
    {
        addElementIfEmpty2(nodeRight, env);
    }
    if (currentNode->getRow() > 0)
    {
        addElementIfEmpty2(nodeUp, env);
    }
    if (currentNode->getRow() < 20)
    {
        addElementIfEmpty2(nodeDown, env);
    }
}

void PathSolver::addElementIfEmpty2(Node *node, Env env)
{
    if (env[node->getRow()][node->getCol()] == SYMBOL_EMPTY || env[node->getRow()][node->getCol()] == SYMBOL_START)
    {
        neighbors->addElement(node);
    }
}

//-----------------------------``