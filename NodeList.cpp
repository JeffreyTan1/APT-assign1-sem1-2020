#include "NodeList.h"
#include <iostream>

NodeList::NodeList()
{
    length = 0;
    *nodes = new Node[NODE_LIST_ARRAY_MAX_SIZE];
}

NodeList::~NodeList()
{
    //TODO: delete[] nodes; is just not working
}

NodeList::NodeList(NodeList &other)
{
    *nodes = new Node[NODE_LIST_ARRAY_MAX_SIZE];
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        nodes[i] = other.getNode(i);
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

bool NodeList::isIncluded(Node *checkNode)
{
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        if (nodes[i]->getRow() == checkNode->getRow() && nodes[i]->getCol() == checkNode->getCol())
        {
            return true;
        }
    }
    return false;
}

Node *NodeList::getSmallestEstDistNode(Node *goalNode, NodeList *closedList)
{
    int smallestDist2Goal = -1;
    Node *returnNode = new Node();
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        int currentDist2Goal = nodes[i]->getEstimatedDist2Goal(goalNode);
        if (currentDist2Goal > smallestDist2Goal && !closedList->isIncluded(nodes[i]))
        {
            returnNode = nodes[i];
            smallestDist2Goal = currentDist2Goal;
        }
    }

    if (returnNode == nullptr)
    {
        throw new std::exception_ptr;
    }

    return returnNode;
}