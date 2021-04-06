#include "NodeList.h"
#include <iostream>
#include <math.h>

NodeList::NodeList()
{
    length = 0;
    nodes = new Node *[maxSize];
}

NodeList::NodeList(int size)
{
    length = 0;
    nodes = new Node *[size];
}

NodeList::~NodeList()
{
    delete[] nodes;
}

NodeList::NodeList(NodeList &other)
{
    nodes = new Node *[maxSize];
    for (int i = 0; i < other.length; i++)
    {
        nodes[i] = other.nodes[i];
    }
    length = other.getLength();
}

int NodeList::getLength()
{
    return length;
}

void NodeList::addElement(Node *newPos)
{
    nodes[length] = newPos;
    length++;
}

Node *NodeList::getNode(int i)
{
    return nodes[i];
}

void NodeList::reverseList()
{
    NodeList *tempList = new NodeList(*this);
    for (int i = 0; i < length; i++)
    {
        nodes[i] = tempList->getNode(length - 1 - i);
    }
    delete tempList;
}

bool NodeList::isIncluded(Node *checkNode)
{
    for (int i = 0; i < length; i++)
    {
        if (nodes[i]->getRow() == checkNode->getRow() && nodes[i]->getCol() == checkNode->getCol())
        {
            return true;
        }
    }
    return false;
}

Node *NodeList::getSmallestEstDistNode(Node *goalNode, NodeList *nodesExplored)
{
    //largest possible estimated distance is if the node and goal are on opposite diagonals
    const int MAX_EST_DIST = pow(pow(cols, 2) + pow(rows, 2), 0.5) + 1;

    int smallestDist2Goal = MAX_EST_DIST;
    Node *returnNode = nullptr;
    for (int i = 0; i < length; i++)
    {
        int currentDist2Goal = nodes[i]->getEstimatedDist2Goal(goalNode);
        if (currentDist2Goal < smallestDist2Goal && !nodesExplored->isIncluded(nodes[i]))
        {
            returnNode = nodes[i];
            smallestDist2Goal = currentDist2Goal;
        }
    }
    return returnNode;
}

Node *NodeList::searchPathNeighbors4LeastDist(Node *currentNode, NodeList *neighbors)
{
    int currentDistTravelled = currentNode->getDistanceTraveled();
    for (int i = 0; i < length; i++)
    {
        if (nodes[i]->getDistanceTraveled() == currentDistTravelled - 1 && neighbors->isIncluded(nodes[i]))
        {
            return nodes[i];
        }
    }
    return currentNode;
}
