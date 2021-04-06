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
    delete openList;
    delete path;
    delete neighbors;

    delete nodeLeft;
    delete nodeRight;
    delete nodeUp;
    delete nodeDown;
}

void PathSolver::forwardSearch(Env env)
{
    initializeAlgoVars(env);

    while (!currentNode->isSamePosition(goalNode))
    {

        currentNode = openList->getSmallestEstDistNode(goalNode, nodesExplored);
        pointAllDirections();
        addAllDirections(env);
        nodesExplored->addElement(currentNode);
    }

    goalNode->setDistanceTraveled(currentNode->getDistanceTraveled());
    nodesExplored->addElement(goalNode);
}

NodeList *PathSolver::getPath(Env env)
{
    currentNode = goalNode;

    for (int i = 0; i < goalNode->getDistanceTraveled() + 1; i++)
    {
        path->addElement(currentNode);

        createNeighborsList(env);

        currentNode = nodesExplored->searchPathNeighbors4LeastDist(currentNode, neighbors);
    }

    path->reverseList();
    //Return deep copy
    NodeList *pathCopy = new NodeList(*path);
    return pathCopy;
}

void PathSolver::initializeAlgoVars(Env env)
{
    //Read the locations of start and goal positions
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
    }
    else
    {
        delete nodeLeft;
        nodeLeft = nullptr;
    }
    if (currentNode->getCol() < (cols - 1) && !openList->isIncluded(nodeRight))
    {
        addElementIfEmpty(nodeRight, env);
    }
    else
    {
        delete nodeRight;
        nodeRight = nullptr;
    }
    if (currentNode->getRow() > 0 && !openList->isIncluded(nodeUp))
    {
        addElementIfEmpty(nodeUp, env);
    }
    else
    {
        delete nodeUp;
        nodeUp = nullptr;
    }
    if (currentNode->getRow() < (rows - 1) && !openList->isIncluded(nodeDown))
    {
        addElementIfEmpty(nodeDown, env);
    }
    else
    {
        delete nodeDown;
        nodeDown = nullptr;
    }
}

void PathSolver::addElementIfEmpty(Node *node, Env env)
{
    if (env[node->getRow()][node->getCol()] == SYMBOL_EMPTY || env[node->getRow()][node->getCol()] == SYMBOL_GOAL)
    {
        openList->addElement(node);
    }
}

void PathSolver::createNeighborsList(Env env)
{
    pointAllDirections();
    neighbors = new NodeList(NEIGHBORS_LIST_SIZE);
    addAllDirections2(env);
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
        nodeLeft = nullptr;
    }
    if (currentNode->getCol() < (cols - 1))
    {
        addElementIfEmpty2(nodeRight, env);
    }
    else
    {
        delete nodeRight;
        nodeRight = nullptr;
    }
    if (currentNode->getRow() > 0)
    {
        addElementIfEmpty2(nodeUp, env);
    }
    else
    {
        delete nodeUp;
        nodeUp = nullptr;
    }
    if (currentNode->getRow() < (rows - 1))
    {
        addElementIfEmpty2(nodeDown, env);
    }
    else
    {
        delete nodeDown;
        nodeDown = nullptr;
    }
}

void PathSolver::addElementIfEmpty2(Node *node, Env env)
{
    if (env[node->getRow()][node->getCol()] == SYMBOL_EMPTY || env[node->getRow()][node->getCol()] == SYMBOL_START)
    {
        neighbors->addElement(node);
    }
}

NodeList *PathSolver::getNodesExplored()
{
    NodeList *nodesExploredCopy = new NodeList(*nodesExplored);
    return nodesExploredCopy;
}
//-----------------------------