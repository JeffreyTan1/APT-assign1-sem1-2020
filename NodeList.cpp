#include "NodeList.h"
#include <iostream>
#define MAX_EST_DIST 1000000

NodeList::NodeList()
{
    length = 0;
}
NodeList::NodeList(int maxSize) : maxSize(maxSize)
{
    length = 0;
    nodes = new Node *[maxSize];
}

NodeList::~NodeList()
{
    //delete[] nodes;
}

NodeList::NodeList(NodeList &other)
{
    for (int i = 0; i < other.length; i++)
    {
        nodes[i] = other.getNode(i);
    }
    maxSize = other.maxSize;
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

//Called on the openList to find node with smallest manhattan
Node *NodeList::getSmallestEstDistNode(Node *goalNode, NodeList *nodesExplored)

{
    //TODO: create const for this max i.e 20root2
    //printList();
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
    neighbors->printList();
    int currentDistTravelled = currentNode->getDistanceTraveled();
    for (int i = 0; i < length; i++)
    {
        if (nodes[i]->getDistanceTraveled() == currentDistTravelled - 1 && neighbors->isIncluded(nodes[i]))
        {
            // std::cout << "Next node to add" << nodes[i]->to_string() << std::endl;
            // std::cout << std::endl;
            return nodes[i];
        }
    }
    // std::cout << "You goofed" << std::endl;
    return currentNode;
}

void NodeList::printList()
{
    for (int i = 0; i < length; i++)
    {
        std::cout << nodes[i]->to_string() << "|";
    }
    std::cout << "Print done" << std::endl;
}

void NodeList::printList(NodeList *nodesExplored)
{
    for (int i = 0; i < length; i++)
    {
        if (!nodesExplored->isIncluded(nodes[i]))
        {
            std::cout << nodes[i]->to_string() << "|";
        }
    }
    std::cout << "Print done" << std::endl;
}
